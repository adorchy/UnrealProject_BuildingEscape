// Copryright Arnaud d'Orchymont 2017

#include "BuildingEscape.h"
#include "OpenDoorActorRef.h"


// Sets default values for this component's properties
UOpenDoorActorRef::UOpenDoorActorRef()
{
	LastDoorOpenTime = 0.0;

	
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoorActorRef::BeginPlay()
{
	Super::BeginPlay();
	if (!ActorThatOpens) {
		UE_LOG(LogTemp, Error, TEXT("Error no actor assigned to OpenDoorActorRef on %s"), *GetOwner()->GetName());
	}

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("Error no pressure plate assigned to OpenDoorActorRef on %s"), *GetOwner()->GetName());
	}
}


// Called every frame
void UOpenDoorActorRef::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ActorThatOpens &&  PressurePlate) {
	// Detect if an actor overlap the Pressure plate
		if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
			OpenDoor();
			LastDoorOpenTime = GetWorld()->GetTimeSeconds();
		}
	// Close the door after a speficied delay, once the actor is no more on the pressure plate
	if (GetWorld()->GetTimeSeconds() >= (LastDoorOpenTime + DoorCloseDelay)) {
		CloseDoor();
		}
	}

}


void UOpenDoorActorRef::OpenDoor() {
	FRotator RotationOpenState;
	RotationOpenState.Pitch = 0.0; // Y axis
	RotationOpenState.Yaw = OpenAngle; // Z axis
	RotationOpenState.Roll = 0.0; // X axis
	GetOwner()->SetActorRotation(RotationOpenState);

}

void UOpenDoorActorRef::CloseDoor() {
	GetOwner()->SetActorRotation(FRotator{ 0.0, CloseAngle, 0.0 });
}

/* // To select the player as opening actor: ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn(); */
