// Copyright Gregory Scott Hanna 2018

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	SpringConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring Constraint"));
	SetRootComponent(SpringConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetSimulatePhysics(true);
	Axle->SetupAttachment(SpringConstraint);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetSimulatePhysics(true);
	Wheel->SetupAttachment(Axle);
		
	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Wheel Constraint"));
	AxleWheelConstraint->SetupAttachment(Axle);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
	
	if (GetAttachParentActor())
	{
		UPrimitiveComponent* ActorRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		if (ActorRoot)
		{
			SpringConstraint->SetConstrainedComponents(ActorRoot, NAME_None, Axle, NAME_None);
		}
	}
	AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	Wheel->AddForce(Axle->GetForwardVector() * DriveForce);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DriveForce = 0;
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	DriveForce += ForceMagnitude;
}

