// Fill out your copyright notice in the Description page of Project Settings.


#include "TankSpawnFactory.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATankSpawnFactory::ATankSpawnFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceneComp;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->SetupAttachment(sceneComp);

	TankSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setuppoint"));
	TankSpawnPoint->AttachToComponent(sceneComp,FAttachmentTransformRules::KeepRelativeTransform);

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(sceneComp);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Healthcomponent"));
	HealthComponent->OnDie.AddUObject(this, &ATankSpawnFactory::Die);
	HealthComponent->OnDamaged.AddUObject(this, &ATankSpawnFactory::DamageTaked);

	TShootEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShootEffect"));
	TShootEffect->SetupAttachment(TankSpawnPoint);

	TAudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioEffect"));

	DShootEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShootEffect2"));
	DShootEffect->SetupAttachment(BuildingMesh);

	DAudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioEffect2"));
}

void ATankSpawnFactory::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

// Called when the game starts or when spawned
void ATankSpawnFactory::BeginPlay()
{
	Super::BeginPlay();
	if (LinkedMapLoader)
		LinkedMapLoader->SetIsActivated(false);

	FTimerHandle _targetingTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_targetingTimerHandle, this,&ATankSpawnFactory::SpawnNewTank, SpawnTankRate, true, SpawnTankRate);

	
}

void ATankSpawnFactory::SpawnNewTank()
{
	TShootEffect->ActivateSystem();
	TAudioEffect->Play();
	FTransform spawnTransform(TankSpawnPoint->GetComponentRotation(),TankSpawnPoint->GetComponentLocation(), FVector(1));
	ATankPawn* newTank = GetWorld()->SpawnActorDeferred<ATankPawn>(SpawnTankClass,spawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	//
	newTank->SetPatrollingPoints(TankWayPoints);
	//
	UGameplayStatics::FinishSpawningActor(newTank, spawnTransform);
}

void ATankSpawnFactory::Die()
{
	if (LinkedMapLoader)
		LinkedMapLoader->SetIsActivated(true);
	DShootEffect->ActivateSystem();
	DAudioEffect->Play();
	GetWorld()->GetTimerManager().SetTimer(DelayDeathHandle, this, &ATankSpawnFactory::Death, 0.4, false);
}

void ATankSpawnFactory::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Factory %s taked damage:%f Health:%f"),*GetName(), DamageValue, HealthComponent->GetHealth());
}

void ATankSpawnFactory::Death()
{
	Destroy();
}
