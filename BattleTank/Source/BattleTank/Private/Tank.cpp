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

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 Damage = FMath::Clamp<int32>(FPlatformMath::RoundToInt(DamageAmount), 0, CurrentHealth);
	CurrentHealth -= Damage;
	if (CurrentHealth == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] is dead!"), *GetName());
	}
	return Damage;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)MaxHealth;
}
