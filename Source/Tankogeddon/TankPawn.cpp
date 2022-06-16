//*\\|*|-PSAIX-|*|//*\\

#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TankPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ArrowComponent.h"


void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	TankController = Cast<ATankPlayerController>(GetController());

	SetupCannon(CannonClass);
}


void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector currentLocation = GetActorLocation();
	FVector forwardVector = GetActorForwardVector();
	FVector movePosition = currentLocation + forwardVector * MoveSpeed * TargetForwardAxisValue * DeltaTime;
	SetActorLocation(movePosition, true);

	CurrentRightAxisValue = FMath::Lerp(CurrentRightAxisValue,
		TargetRightAxisValue, InterpolationKey);

	float yawRotation = RotationSpeed * CurrentRightAxisValue * DeltaTime;
	FRotator currentRotation = GetActorRotation();

	yawRotation = currentRotation.Yaw + yawRotation;

	FRotator newRotation = FRotator(0, yawRotation, 0);
	SetActorRotation(newRotation);

	if (TankController)
	{
		FVector mousePos = TankController->GetMousePos();
		FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mousePos);
		FRotator currRotation = TurretMesh->GetComponentRotation();
		targetRotation.Pitch = currRotation.Pitch;
		targetRotation.Roll = currRotation.Roll;
		TurretMesh->SetWorldRotation(FMath::Lerp(currRotation, targetRotation,
			TurretRotationInterpolationKey));
	}
}

void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void ATankPawn::MoveForward(float AxisValue)
{
	TargetForwardAxisValue = AxisValue;
}

void ATankPawn::RotateRight(float AxisValue)
{
	TargetRightAxisValue = AxisValue;
}

void ATankPawn::SetupCannon(TSubclassOf<ACannon> cannonClass)
{
	if (cannonClass)
	{
		CannonClass = cannonClass;
	}
	if (Cannon)
	{
		Cannon->Destroy();
	}
	FActorSpawnParameters params;
	params.Instigator = this;
	params.Owner = this;

	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, params);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void ATankPawn::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

void ATankPawn::Die()
{
	if (Cannon)
	{
		Cannon->KillerActor = "Turret";
		Cannon->ActorKilled = "You";
		Cannon->Killed();
	}
	Destroy();
}

void ATankPawn::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Tank %s taked damage:%f Health:%f"), *GetName(),DamageValue, HealthComponent->GetHealth());
}


void ATankPawn::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();
	}
}

void ATankPawn::FireSpecial()
{
	if (Cannon)
	{
		Cannon->FireSpecial();
	}
}

void ATankPawn::OnReload()
{
	if (Cannon)
	{
		Cannon->OnReload();
	}
}

void ATankPawn::StopFire()
{
	if (Cannon)
	{
		Cannon->StopFire();
	}
}

void ATankPawn::Swap()
{
	if (Cannon)
	{
		Cannon->Swap();
	}
}
