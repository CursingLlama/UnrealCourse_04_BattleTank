// Copyright Gregory Scott Hanna 2018

#include "Tank.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine/StaticMeshSocket.h"


// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); //Hooks into blueprint BeginPlay
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
