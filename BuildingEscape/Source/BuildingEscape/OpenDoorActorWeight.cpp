// Copryright Arnaud d_Orchymont 2017

#include "BuildingEscape.h"
#include "OpenDoorActorWeight.h"


// Sets default values for this component's properties
UOpenDoorActorWeight::UOpenDoorActorWeight()
{
	LastDoorOpenTime = 0.0;
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoorActorWeight::BeginPlay()
{
	Super::BeginPlay();
	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("Error no pressure plate assigned to OpenDoorActorWeight on %s"), *GetOwner()->GetName());
	}
}


// Called every frame
void UOpenDoorActorWeight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (GetTotalMassOfActorsOnPlate() >= 40.f) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() >= (LastDoorOpenTime + DoorCloseDelay)) {
		CloseDoor();
	}

}

float UOpenDoorActorWeight::GetTotalMassOfActorsOnPlate() {

	float TotalMass = 0;

	if (PressurePlate) {
		PressurePlate->GetOverlappingActors(OUT OverlappingActors);
		for (auto* Actor : OverlappingActors) { // for each actor in OverlappingActors
			TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	}
	return TotalMass;
}


void UOpenDoorActorWeight::OpenDoor() {
	GetOwner()->SetActorRotation(FRotator{ 0.0, OpenAngle, 0.0 });
}

void UOpenDoorActorWeight::CloseDoor() {
	GetOwner()->SetActorRotation(FRotator{ 0.0, CloseAngle, 0.0 });
}

