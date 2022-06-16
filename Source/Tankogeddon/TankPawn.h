//*\\|*|-PSAIX-|*|//*\\

#pragma once

#include "Cannon.h"
#include "CoreMinimal.h"
#include "DamageTaker.h"
#include "HealthComponent.h"
#include "Components/BoxComponent.h"
#include "TankPlayerController.h"
#include "GameFramework/Pawn.h"
#include "TankFactory.h"

#include "TankPawn.generated.h"


class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class ATankPlayerController;
class ACannon;


UCLASS()
class TANKOGEDDON_API ATankPawn : public ATankFactory, public IDamageTaker
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveSpeed = 230;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float RotationSpeed = 180;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float InterpolationKey = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Speed")
		float TurretRotationInterpolationKey = 0.5f;


	float TargetForwardAxisValue;
	float TargetRightAxisValue;
	float CurrentRightAxisValue;

public:
	ATankPawn()
	{
		PrimaryActorTick.bCanEverTick = true;

		BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank body"));
		RootComponent = BodyMesh;

		TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank turret"));
		TurretMesh->SetupAttachment(BodyMesh);

		CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
		CannonSetupPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepRelativeTransform);

		SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
		SpringArm->SetupAttachment(BodyMesh);
		SpringArm->bDoCollisionTest = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bInheritRoll = false;
		Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
		Camera->SetupAttachment(SpringArm);

		HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Healthcomponent"));
		HealthComponent->OnDie.AddUObject(this, &ATankPawn::Die);
		HealthComponent->OnDamaged.AddUObject(this, &ATankPawn::DamageTaked);
		HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
		HitCollider->SetupAttachment(BodyMesh);
	}

	UFUNCTION()
		void BeginPlay();

	void Tick(float DeltaTime);
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);
	void MoveForward(float AxisValue);
	void RotateRight(float AxisValue);

	UFUNCTION()
		void Fire();
	void FireSpecial();
	void OnReload();
	void StopFire();
	void Swap();

public:

	void SetupCannon(TSubclassOf<ACannon> cannonClass);

	UFUNCTION()
		void TakeDamage(FDamageData DamageData);

protected:

	UFUNCTION()
		void Die();

	UFUNCTION()
		void DamageTaked(float DamageValue);

};
