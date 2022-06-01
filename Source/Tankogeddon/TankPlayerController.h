//*\\|*|-PSAIX-|*|//*\\

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATankPawn;

/**
 * 
 */
UCLASS()
class TANKOGEDDON_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	ATankPawn* TankPawn;
	UPROPERTY()
		FVector MousePos;

public:
	ATankPlayerController();
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;
	FVector GetMousePos() { return MousePos; };

protected:
	virtual void BeginPlay() override;
	void MoveForward(float AxisValue);
	void RotateRight(float AxisValue);
	void Fire();
	void FireSpecial();
	void StopFire();
	void OnReload();
	void Swap();
};
