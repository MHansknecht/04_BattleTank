// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimComponent.h"
#include "Tank.h"
#include "BattleTank.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) {return; }
		
	
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim towards the player
	auto AimComponent = ControlledTank->FindComponentByClass<UTankAimComponent>();
	AimComponent->AimAt(PlayerTank->GetActorLocation());


	if (AimComponent->GetFiringState() == EFiringState::Locked)
	{
		AimComponent->Fire();
	}
	
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		//  subscribe our local method to tank's death.
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
	}
}


void ATankAIController::OnPossedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Received!"))
}