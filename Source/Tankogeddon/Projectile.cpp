// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->OnComponentBeginOverlap.AddDynamic(this,&AProjectile::OnMeshOverlapBegin);

	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
}

void AProjectile::Start()
{
	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &AProjectile::Move, MoveRate, true, MoveRate);
}

void AProjectile::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (CanExplode)
		Explode();
	else
	{
		AActor* owner = GetOwner();
		AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;
		if (OtherActor != owner && OtherActor != ownerByOwner)
		{
			DamageDealing(OtherActor);
		}
	}
}

void AProjectile::Move()
{
	FVector nextPosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed * MoveRate;
	SetActorLocation(nextPosition);
}

void AProjectile::Killed()
{
	if (OnKill.IsBound())
	{
		OnKill.Broadcast();
	}
}

void AProjectile::Explode()
{
	CanExplode = false;
	FVector startPos = GetActorLocation();
	FVector endPos = startPos + FVector(0.1f);
	FCollisionShape Shape = FCollisionShape::MakeSphere(ExplodeRadius);
	FCollisionQueryParams params = FCollisionQueryParams::DefaultQueryParam;
	params.AddIgnoredActor(this);
	params.bTraceComplex = true;
	params.TraceTag = "Explode Trace";
	TArray<FHitResult> AttackHit;
	FQuat Rotation = FQuat::Identity;
	bool sweepResult = GetWorld()->SweepMultiByChannel
	(
		AttackHit,
		startPos,
		endPos,
		Rotation,
		ECollisionChannel::ECC_Visibility,
		Shape,
		params
	);
	GetWorld()->DebugDrawTraceTag = "Explode Trace";
	if (sweepResult)
	{
		for (FHitResult hitResult : AttackHit)
		{
			AActor* otherActor = hitResult.GetActor();
			if (!otherActor)
				continue;
			DamageDealing(otherActor);
		}
	}
}

void AProjectile::ReadyToExplode()
{
	CanExplode = true;
}


void AProjectile::DamageDealing(AActor* otherActor)
{
	IDamageTaker* damageTakerActor = Cast<IDamageTaker>(otherActor);
	if (damageTakerActor)
	{
		FDamageData damageData;
		damageData.DamageValue = Damage;
		damageData.Instigator = GetOwner();
		damageData.DamageMaker = this;
		damageTakerActor->TakeDamage(damageData);
	}
	else
	{
		UPrimitiveComponent* mesh = Cast<UPrimitiveComponent>(otherActor->GetRootComponent());
		if (mesh)
		{
			if (mesh->IsSimulatingPhysics())
			{
				FVector forceVector = otherActor->GetActorLocation() - GetActorLocation();
				forceVector.Normalize();
				mesh->AddForce(forceVector * PushForce * mesh->GetMass());
			}
			else
			{
				otherActor->Destroy();
			}
		}
	}
	Destroy();
}





