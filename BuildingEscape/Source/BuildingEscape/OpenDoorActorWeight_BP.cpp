// Copryright Arnaud d_Orchymont 2017

#include "BuildingEscape.h"
#include "OpenDoorActorWeight_BP.h"


// Sets default values for this component's properties
UOpenDoorActorWeight_BP::UOpenDoorActorWeight_BP()
{
	LastDoorOpenTime = 0.0;
	InitialRotation = { 0.0,0.0,0.0 };
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UOpenDoorActorWeight_BP::BeginPlay()
{
	Super::BeginPlay();
	InitialRotation = GetOwner()->GetActorRotation();
	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("Error no pressure plate assigned to OpenDoorActorWeight on %s"), *GetOwner()->GetName());
	}
	
}

// Called every frame
void UOpenDoorActorWeight_BP::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (GetTotalMassOfActorsOnPlate() >= 40.f) 
	{
		OnOpenRequest.Broadcast();
		LastDoorOpenTime= GetWorld()->GetTimeSeconds(); // create to have possibillity to delay the return of the actor to his initial state
	}

	
	if (InitialRotation != GetOwner()->GetActorRotation() && 
		LastDoorOpenTime != 0.0 && // prevent the event to trigger when game start
		GetWorld()->GetTimeSeconds()>LastDoorOpenTime) 
	{	
		OnCloseRequest.Broadcast();
	}

}

/*
Allow to compute the total mass of actor(s) positionned on a trigger box
*/
float UOpenDoorActorWeight_BP::GetTotalMassOfActorsOnPlate() {

	float TotalMass = 0;

	if (PressurePlate) {
		PressurePlate->GetOverlappingActors(OUT OverlappingActors);
		for (auto* Actor : OverlappingActors) { // for each actor in OverlappingActors
			TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	}
	return TotalMass;
}

