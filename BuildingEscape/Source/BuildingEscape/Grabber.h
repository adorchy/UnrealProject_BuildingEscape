// Copryright Arnaud d'Orchymont 2017

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	FRotator ViewPointRotation;
	FVector ViewPointLocation;
	FVector LineTraceDirection;
	FVector LineTraceEnd;
	float Reach;
	FHitResult HitResult;
	AActor* ActorHit;
	UPhysicsHandleComponent* PhysicHandleComponent;
	UInputComponent* InputComponent;
	UPrimitiveComponent* GrabbedComponent;

public:
	void InitVar();
	void SetupPhysicsHandleComponent();
	void SetupInputComponent();
	void ComputeReachLineEnd();
	void DrawRedDebugLineFromPawn();
	void LineTrace();
	FHitResult GetFirstPhysicsBodyInReach();
	void Grab();
	void Release();

};
