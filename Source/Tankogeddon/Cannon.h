//*\\|*|-PSAIX-|*|//*\\

#pragma once

#include "CoreMinimal.h"
#include "GameStructs.h"
#include "DamageTaker.h"
#include "Projectile.h"
#include "Camera/CameraShakeBase.h"
#include "Components/AudioComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ForceFeedbackEffect.h"
#include "Particles/ParticleSystemComponent.h"
#include "Cannon.generated.h"

class UArrowComponent;

UCLASS()
class TANKOGEDDON_API ACannon : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireRate = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireRange = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireDamage = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		ECannonType Type = ECannonType::FireProjectile;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		TSubclassOf<AProjectile>ProjectileClass;

	// loadedAmmo variable. The amount of ammo in the cannon. If there is no ammo (loadedAmmo <= 0) the cannon can't fire.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int32 loadedAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
		float Damage = 1;

	// ammoPool variable. Ammo in the inventory. If there is no ammo in the inventory, cannon can't be reloaded.
	
	FTimerHandle ReloadTimerHandle;

	// DelayShotHandle timer for the Shot() method cycle.Implemening autorifle fire to the FireSpecial() action.
	FTimerHandle DelayShotHandle;

	bool ReadyToFire = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effect")
		class UParticleSystemComponent* ShootEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effect")
		class UAudioComponent* AudioEffect;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
		UForceFeedbackEffect* ShootForceEffect;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UCameraShakeBase> ShootShake;

	bool Animation = false;


public:	
	ACannon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int32 ammoPool;

	void Fire();

	void FireSpecial();

	void Shot();

	void StopFire();

	void OnReload();

	void Swap();

	bool IsReadyToFire();

	UFUNCTION()
		void Killed();

	FString ActorKilled;

	FString KillerActor;

protected:
	virtual void BeginPlay() override;

	void Reload();
};
