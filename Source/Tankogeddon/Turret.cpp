// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "TankPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Cannon.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ATurret::ATurret()
{
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret body"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret turret"));
	TurretMesh->AttachToComponent(BodyMesh,FAttachmentTransformRules::KeepRelativeTransform);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
	CannonSetupPoint->AttachToComponent(TurretMesh,FAttachmentTransformRules::KeepRelativeTransform);

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(TurretMesh);

	UStaticMesh * turretMeshTemp = LoadObject<UStaticMesh>(this, *TurretMeshPath);
	if (turretMeshTemp)
		TurretMesh->SetStaticMesh(turretMeshTemp);

	UStaticMesh* bodyMeshTemp = LoadObject<UStaticMesh>(this, *BodyMeshPath);
	if (bodyMeshTemp)
		BodyMesh->SetStaticMesh(bodyMeshTemp);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Healthcomponent"));
	HealthComponent->OnDie.AddUObject(this, &ATurret::Die);
	HealthComponent->OnDamaged.AddUObject(this, &ATurret::DamageTaked);
}

void ATurret::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

void ATurret::Die()
{
	if (Cannon)
	{
		Cannon->KillerActor = "You";
		Cannon->ActorKilled = "the Turret";
		Cannon->Killed();
	}
	Destroy();
}

void ATurret::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Turret %s taked damage:%f Health:%f"), *GetName(),DamageValue, HealthComponent->GetHealth());
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters params;
	params.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, params);
	Cannon->AttachToComponent(CannonSetupPoint,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	FTimerHandle _targetingTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_targetingTimerHandle, this,
		&ATurret::Targeting, TargetingRate, true, TargetingRate);
	
}

void ATurret::Destroyed()
{
	if (Cannon)
		Cannon->Destroy();

}

void ATurret::Targeting()
{
	if (IsPlayerInRange())
	{
		RotateToPlayer();
	}
	if (CanFire() && Cannon && Cannon->IsReadyToFire())
	{
		Fire();
	}

}

void ATurret::RotateToPlayer()
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),PlayerPawn->GetActorLocation());
	FRotator currRotation = TurretMesh->GetComponentRotation();
	targetRotation.Pitch = currRotation.Pitch;
	targetRotation.Roll = currRotation.Roll;
	TurretMesh->SetWorldRotation(FMath::Lerp(currRotation, targetRotation,
		TargetingSpeed));

}

bool ATurret::IsPlayerInRange()
{
	return FVector::Distance(PlayerPawn->GetActorLocation(), GetActorLocation()) <= TargetingRange;
}

bool ATurret::CanFire()
{
	FVector targetingDir = TurretMesh->GetForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
	dirToPlayer.Normalize();
	float aimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDir, dirToPlayer)));
	return aimAngle <= Accurency;
}

void ATurret::Fire()
{
	if (Cannon)
		Cannon->Fire();

}
