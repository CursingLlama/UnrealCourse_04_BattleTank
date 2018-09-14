// Copyright Gregory Scott Hanna 2018

#include "TankTrack.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	CounteractSidewaysForce();
	DriveTrack();
	CurrentThrottle = 0;
}

void UTankTrack::CounteractSidewaysForce()
{
	float StrafeSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity()); ///Figure out how much sideways speed there is
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector CorrectingAcceleration = -StrafeSpeed / DeltaTime * GetRightVector(); ///Caculate amount of needed Acceleration to nullify strafe speed
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector CorrectingForce = TankRoot->GetMass() * CorrectingAcceleration / 2;  ///F = M * A (divide by two to split over both tracks)
	TankRoot->AddForce(CorrectingForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.5f, 1.5f);
}

void UTankTrack::DriveTrack()
{
	FVector ForceApplied = GetForwardVector() * MaxDrivingForce * CurrentThrottle;
	UPrimitiveComponent* TrackRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TrackRoot->AddForceAtLocation(ForceApplied, GetComponentLocation());
}
