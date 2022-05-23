//*\\|*|-PSAIX-|*|//*\\

#include <mutex>
#include <thread>
#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"


std::mutex delay;


ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon mesh"));
	Mesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawnpoint"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);

	loadedAmmo = 5;
	ammoPool = 25;
}

void ACannon::Fire()
{
	if (loadedAmmo <= 0) { return; }

	loadedAmmo -= 1;

	if (!ReadyToFire) { return; }

	ReadyToFire = false;

	if (Type == ECannonType::FireProjectile)
	{
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
			ProjectileSpawnPoint->GetComponentLocation(),
			ProjectileSpawnPoint->GetComponentRotation());
		if (projectile)
		{
			projectile->Start();
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - trace");
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
	
	// FareRate increased to 10.
	FireRate = 10;

	if (!ReadyToFire)
	{
		return;
	}
	ReadyToFire = false;

	if (Type == ECannonType::FireProjectile)
	{
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
			ProjectileSpawnPoint->GetComponentLocation(),
			ProjectileSpawnPoint->GetComponentRotation());

		if (projectile)
		{
			projectile->Start();
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - trace");
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);

	// FireRate decreased back to 8.
	FireRate = 8;
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

