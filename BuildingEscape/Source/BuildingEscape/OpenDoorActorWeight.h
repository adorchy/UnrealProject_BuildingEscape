// Copryright Arnaud d_Orchymont 2017

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoorActorWeight.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoorActorWeight : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoorActorWeight();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	float LastDoorOpenTime;
	TArray<AActor*> OverlappingActors;

	//Property
	UPROPERTY(EditAnywhere)
		float OpenAngle = -160.0;

	UPROPERTY(EditAnywhere)
		float CloseAngle = -90;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 0.5;

public:

	float GetTotalMassOfActorsOnPlate();
	void OpenDoor();
	void CloseDoor();
	
};
