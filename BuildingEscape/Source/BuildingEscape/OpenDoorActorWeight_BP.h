// Copryright Arnaud d_Orchymont 2017

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoorActorWeight_BP.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEventAlt);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoorActorWeight_BP : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoorActorWeight_BP();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	TArray<AActor*> OverlappingActors;
	float LastDoorOpenTime;
	FRotator InitialRotation;
	//Property

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;

public:

	float GetTotalMassOfActorsOnPlate();

	UPROPERTY(BlueprintAssignable)
		FDoorEventAlt OnOpenRequest;

	UPROPERTY(BlueprintAssignable)
		FDoorEventAlt OnCloseRequest;

};
