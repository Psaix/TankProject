// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPlayerController.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Cannon.h"
#include "HealthComponent.h"

class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class ATankPlayerController;
class ACannon;

#include "TankFactory.generated.h"

UCLASS()
class TANKOGEDDON_API ATankFactory : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankFactory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* CannonSetupPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Cannon")
		TSubclassOf<ACannon> CannonClass;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UCameraComponent* Camera;

	UPROPERTY()
		ACannon* Cannon;

	UPROPERTY()
		ATankPlayerController* TankController;

	UPROPERTY()
		APawn* PlayerPawn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
