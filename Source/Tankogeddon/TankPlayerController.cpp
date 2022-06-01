//*\\|*|-PSAIX-|*|//*\\

#include "TankPawn.h"
#include "DrawDebugHelpers.h"
#include "TankPlayerController.h"

ATankPlayerController::ATankPlayerController()
{
	bShowMouseCursor = true;
}

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &ATankPlayerController::MoveForward);
	InputComponent->BindAxis("RotateRight", this, &ATankPlayerController::RotateRight);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ATankPlayerController::Fire);

	// Alternative fire input.
	// Both actions are bind to the right mouse button.
	// FireSpecial() method works on pressed right mouse button.
	InputComponent->BindAction("FireSpecial", IE_Pressed, this, &ATankPlayerController::FireSpecial);
	
	//  StopFire() method works on released right mouse bbutton.
	InputComponent->BindAction("FireSpecial", IE_Released, this, &ATankPlayerController::StopFire);

	// OnReload() method reloads cannon ammo. Works pressed "R" button.
	InputComponent->BindAction("OnReload", IE_Pressed, this, &ATankPlayerController::OnReload);

	InputComponent->BindAction("Swap", IE_Pressed, this, &ATankPlayerController::Swap);
}
void ATankPlayerController::Tick(float DeltaTime)
{
	FVector mouseDirection;
	DeprojectMousePositionToWorld(MousePos, mouseDirection);
	FVector pawnPos = TankPawn->GetActorLocation();
	MousePos.Z = pawnPos.Z;
	FVector dir = MousePos - pawnPos;
	dir.Normalize();
	MousePos = pawnPos + dir * 1000;
	DrawDebugLine(GetWorld(), pawnPos, MousePos, FColor::Green, false, 0.1f, 0, 5);
}
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	TankPawn = Cast<ATankPawn>(GetPawn());
}
void ATankPlayerController::MoveForward(float AxisValue)
{
	TankPawn->MoveForward(AxisValue);
}

void ATankPlayerController::RotateRight(float AxisValue)
{
	TankPawn->RotateRight(AxisValue);
}

void ATankPlayerController::Fire()
{
	TankPawn->Fire();
}

void ATankPlayerController::FireSpecial()
{
	TankPawn->FireSpecial();
}

void ATankPlayerController::StopFire()
{
	TankPawn->StopFire();
}


void ATankPlayerController::OnReload()
{
	TankPawn->OnReload();
}

void ATankPlayerController::Swap()
{
	TankPawn->Swap();
}

