// Copyright Gregory Scott Hanna 2018

#include "TankTrack.h"
#include "Components/PrimitiveComponent.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float StrafeSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity()); ///Figure out how much sideways speed there is
	FVector CorrectingAcceleration = -StrafeSpeed / DeltaTime * GetRightVector(); ///Caculate amount of needed Acceleration to nullify strafe speed
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector CorrectingForce = TankRoot->GetMass() * CorrectingAcceleration / 2;  ///F = M * A (divide by two to split over both tracks)
	TankRoot->AddForce(CorrectingForce);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Track Hit Event"));
}

void UTankTrack::SetThrottle(float Throttle)
{
	Throttle = FMath::Clamp<float>(Throttle, -1, 1);
		FVector ForceApplied = GetForwardVector() * MaxDrivingForce * Throttle;
	UPrimitiveComponent* TrackRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TrackRoot->AddForceAtLocation(ForceApplied, GetComponentLocation());
}
