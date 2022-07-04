// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageTaker.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKOGEDDON_API AProjectile : public AActor
{
	GENERATED_BODY()

		DECLARE_EVENT(AProjectile, FOnDestroyed)

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveSpeed = 800;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveRate = 0.005f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
		float Damage = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
		float PushForce = 100000;

	FTimerHandle MovementTimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Trajectory")
		float ExplodeRadius = 50.0f;

public:
	AProjectile();

	virtual void Start();

protected:
	UFUNCTION()
		void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor*
			OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool
			bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void Move();

	void Killed();

	UFUNCTION()
		void DamageDealing(AActor* otherActor);

	bool CanExplode = false;

public:

	FOnDestroyed OnKill;

	UFUNCTION()
		void Explode();

	UFUNCTION()
		void ReadyToExplode();
};
