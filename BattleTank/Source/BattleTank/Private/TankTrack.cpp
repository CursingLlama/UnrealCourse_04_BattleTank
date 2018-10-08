// Copyright Gregory Scott Hanna 2018

#include "TankTrack.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
}

void UTankTrack::SetThrottle(float Throttle)
{
	DriveTrack(FMath::Clamp<float>(Throttle, -1.5f, 1.5f));
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	float ForceApplied = MaxDrivingForce * CurrentThrottle;
	TArray<ASprungWheel*> Wheels = GetWheels();
	if (Wheels.Num() > 0)
	{
		float ForcePerWheel = ForceApplied / Wheels.Num();
		for (ASprungWheel* Wheel : Wheels)
		{
			Wheel->AddDrivingForce(ForcePerWheel);
		}
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> Wheels;

	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	
	for (USceneComponent* Child : Children)
	{
		USpawnPoint* SpawnPointChild = Cast<USpawnPoint>(Child);
		if (SpawnPointChild)
		{
			ASprungWheel* Wheel = Cast<ASprungWheel>(SpawnPointChild->GetSpawnedActor());
			if (Wheel)
			{
				Wheels.Add(Wheel);
			}
		}
	}
	return Wheels;
}
