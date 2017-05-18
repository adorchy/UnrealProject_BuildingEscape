// Copryright Arnaud d'Orchymont 2017

#include "BuildingEscape.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	ViewPointRotation = { 0.0, 0.0, 0.0 };
	ViewPointLocation = { 0.0, 0.0, 0.0 };
	LineTraceEnd = { 0.0, 0.0, 0.0 };
	Reach = 100.0;
	ActorHit = nullptr;
	PhysicHandleComponent = nullptr;
	InputComponent = nullptr;
	GrabbedComponent = nullptr;

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FString ObjectName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s reporting for duty !"), *ObjectName);

	SetupPhysicsHandleComponent();
	SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Move grabbed object according player point of view
	if (PhysicHandleComponent) {
		if (PhysicHandleComponent->GrabbedComponent) { // If player has grabbed something
			ComputeReachLineEnd();
			PhysicHandleComponent->SetTargetLocation(LineTraceEnd); 
		}
	}

	/* Debug Tool
	ComputeReachLineEnd();
	DrawRedDebugLineFromPawn();
	*/
}

void UGrabber::SetupPhysicsHandleComponent() {
	PhysicHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}
void UGrabber::SetupInputComponent() {
	// look for attached Input Component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("%s has input component !"), *GetOwner()->GetName());
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

//Compute Vectors ViewPointLocation, ViewPointRotation and LineTraceEnd
//Used by LineTrace procedure
void UGrabber::ComputeReachLineEnd() {
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT ViewPointLocation, OUT ViewPointRotation);
	LineTraceEnd = ViewPointLocation + ViewPointRotation.Vector()*Reach;
}

//Debug tool to check ComputeReachLineEnd()
void UGrabber::DrawRedDebugLineFromPawn() {
	DrawDebugLine(GetWorld(), ViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.0, 0.0, 10.0);
}

//Line-trace (aka ray-cast) from pawn out to reach distance
void UGrabber::LineTrace() {
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		ViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);
}

//Return hit for firt physics body in reach
FHitResult UGrabber::GetFirstPhysicsBodyInReach() {
	ComputeReachLineEnd();
	LineTrace();
	return HitResult;
}

// Ray-cast and grab what's in reach
void UGrabber::Grab() {
	ActorHit = GetFirstPhysicsBodyInReach().GetActor();

	if (!PhysicHandleComponent) {
		UE_LOG(LogTemp, Error, TEXT("No Physic HandleComponent attached to pawn"));
	}

	//If we Hit something then attach a physic handle to it 
	//return actor name colliding with Line
	if (PhysicHandleComponent && ActorHit) {
		GrabbedComponent = GetFirstPhysicsBodyInReach().GetComponent();
		UE_LOG(LogTemp, Warning, TEXT("Your are grabbing %s"), *(ActorHit->GetName()));
		//Attach physics handle
		PhysicHandleComponent->GrabComponent(
			GrabbedComponent,
			NAME_None,
			GrabbedComponent->GetOwner()->GetActorLocation(),
			true // allow rotation
		);
	}
}

// Release a grabbed object
void UGrabber::Release() {
	if (PhysicHandleComponent && PhysicHandleComponent->GrabbedComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Your are releasing %s"), *(ActorHit->GetName()));
		PhysicHandleComponent->ReleaseComponent();
	}
}