// Copyright Gregory Scott Hanna 2018

#include "SpawnPoint.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	if (SpawnClass)
	{
		SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());
		if (SpawnedActor)
		{
			SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
			SpawnedActor->FinishSpawning(GetComponentTransform());
		}
	}
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor* USpawnPoint::GetSpawnedActor() const
{
	return SpawnedActor;
}

