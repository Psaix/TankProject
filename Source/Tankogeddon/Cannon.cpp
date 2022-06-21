//*\\|*|-PSAIX-|*|//*\\


#include "Cannon.h"
#include "DrawDebugHelpers.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"


ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon mesh"));
	Mesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawnpoint"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);

	ShootEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShootEffect"));
	ShootEffect->SetupAttachment(ProjectileSpawnPoint);

	AudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioEffect"));

	loadedAmmo = 5;
	ammoPool = 25;
}

void ACannon::Fire()
{

	if (loadedAmmo <= 0) { return; }

	loadedAmmo -= 1;

	if (!ReadyToFire) { return; }

	ReadyToFire = false;

	if (GetOwner() && GetOwner() == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		if (ShootForceEffect)
		{
			FForceFeedbackParameters shootForceEffectParams;
			shootForceEffectParams.bLooping = false;
			shootForceEffectParams.Tag = "shootForceEffectParams";
			GetWorld()->GetFirstPlayerController()->ClientPlayForceFeedback(ShootForceEffect,
				shootForceEffectParams);
		}
		if (ShootShake)
		{
			GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(ShootShake);
		}
	}

	if (Type == ECannonType::FireProjectile)
	{
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
			ProjectileSpawnPoint->GetComponentLocation(),
			ProjectileSpawnPoint->GetComponentRotation());
		if (projectile)
		{
			projectile->OnKill.AddUObject(this, &ACannon::Killed);
			projectile->Start();
			ShootEffect->ActivateSystem();
			AudioEffect->Play();
		}
	}

	else
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - trace");
		FHitResult hitResult;
		FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
		traceParams.bTraceComplex = true;
		traceParams.bReturnPhysicalMaterial = false;

		FVector start = ProjectileSpawnPoint->GetComponentLocation();
		FVector end = ProjectileSpawnPoint->GetForwardVector() * FireRange + start;
		if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, traceParams))
		{
			DrawDebugLine(GetWorld(), start, hitResult.Location, FColor::Red, false,0.5f, 0, 5);
			AActor* owner = GetOwner();
			AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;
			if (hitResult.Actor.Get() != owner && hitResult.Actor.Get() != ownerByOwner)
			{
				IDamageTaker* damageTakerActor = Cast<IDamageTaker>(hitResult.Actor.Get());
				if (damageTakerActor)
				{
					FDamageData damageData;
					damageData.DamageValue = Damage;
					damageData.Instigator = owner;
					damageData.DamageMaker = this;
					damageTakerActor->TakeDamage(damageData);
				}
				else
				{
					hitResult.Actor.Get()->Destroy();
				}
			}
		}
		else
		{
		DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 0.5f, 0, 5);
		}

	}
	
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
}


void ACannon::FireSpecial()
{
	// Evety time FireSpecial() is called we lose 1 ammo.
	if (loadedAmmo <= 0) { return; }

	loadedAmmo -= 1;

	// While right mouse button is pressed the DelayShotHandle timer cycle is "true" and we call Shot() method with "0.06" milliseconds delay between them.
	GetWorld()->GetTimerManager().SetTimer(DelayShotHandle, this, &ACannon::Shot, 0.06f, true);

}

void ACannon::Shot()
{
	// Same as Fire() method.

	if (!ReadyToFire)
	{
		return;
	}
	ReadyToFire = false;

	if (GetOwner() && GetOwner() == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		if (ShootForceEffect)
		{
			FForceFeedbackParameters shootForceEffectParams;
			shootForceEffectParams.bLooping = false;
			shootForceEffectParams.Tag = "shootForceEffectParams";
			GetWorld()->GetFirstPlayerController()->ClientPlayForceFeedback(ShootForceEffect,
				shootForceEffectParams);
		}
		if (ShootShake)
		{
			GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(ShootShake);
		}
	}

	if (Type == ECannonType::FireProjectile)
	{
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
			ProjectileSpawnPoint->GetComponentLocation(),
			ProjectileSpawnPoint->GetComponentRotation());

		if (projectile)
		{
			projectile->OnKill.AddUObject(this, &ACannon::Killed);
			projectile->Start();
			ShootEffect->ActivateSystem();
			AudioEffect->Play();
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - trace");
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);

}

void ACannon::StopFire()
{
	if(DelayShotHandle.IsValid())
		GetWorld()->GetTimerManager().ClearTimer(DelayShotHandle);
}

void ACannon::OnReload()
{
	// If the inventory is empty or the cannon is full - do nothing.
	if (ammoPool <= 0 || loadedAmmo >= 5) { return; }

	// If inventory is not empty - we reload the cannon.
	if (ammoPool >= 5)
	{
		ammoPool = ammoPool - (5 - loadedAmmo);
		loadedAmmo = 5;
		
	}
}

void ACannon::Swap()
{
	if (Type == ECannonType::FireProjectile)
	{
		Type = ECannonType::FireTrace;
	}
	else
	{
		Type = ECannonType::FireProjectile;
	}
}


bool ACannon::IsReadyToFire()
{
	return ReadyToFire;
}

void ACannon::Reload()
{
	ReadyToFire = true;
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	Reload();

}

void ACannon::Killed()
{
	UE_LOG(LogTemp, Warning, TEXT("%s destroyed %s"), *KillerActor, *ActorKilled);
}

