// Copryright Arnaud d'Orchymont 2017

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoorActorRef.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoorActorRef : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoorActorRef();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	float LastDoorOpenTime;

	//Property
	UPROPERTY(EditAnywhere)
		float OpenAngle = -70.0;

	UPROPERTY(EditAnywhere)
		float CloseAngle = 0.0;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
		AActor* ActorThatOpens;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 0.5;

public:

	void OpenDoor();
	void CloseDoor();
};
