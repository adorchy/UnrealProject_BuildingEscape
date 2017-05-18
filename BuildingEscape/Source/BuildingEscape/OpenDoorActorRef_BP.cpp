// Copryright Arnaud d_Orchymont 2017

#include "BuildingEscape.h"
#include "OpenDoorActorRef_BP.h"


// Sets default values for this component's properties
UOpenDoorActorRef_BP::UOpenDoorActorRef_BP()
{
	InitialRotation = { 0.0,0.0,0.0 };
	LastDoorOpenTime = 0.0;
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoorActorRef_BP::BeginPlay()
{
	Super::BeginPlay();
	InitialRotation = GetOwner()->GetActorRotation();
	if (!ActorThatOpens) {
		UE_LOG(LogTemp, Error, TEXT("Error no actor assigned to OpenDoorActorRef on %s"), *GetOwner()->GetName());
	}

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("Error no pressure plate assigned to OpenDoorActorRef on %s"), *GetOwner()->GetName());
	}

}


// Called every frame
void UOpenDoorActorRef_BP::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ActorThatOpens &&  PressurePlate) {
		// Detect if an actor overlap the Pressure plate
		if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
			OnOpenRequest.Broadcast();
			LastDoorOpenTime = GetWorld()->GetTimeSeconds();
		}
	}

	if (InitialRotation != GetOwner()->GetActorRotation() &&
		LastDoorOpenTime != 0.0 &&
		GetWorld()->GetTimeSeconds()>LastDoorOpenTime) {

		OnCloseRequest.Broadcast();

	}
}

