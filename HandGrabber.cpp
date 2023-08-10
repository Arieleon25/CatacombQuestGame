// Fill out your copyright notice in the Description page of Project Settings.


#include "HandGrabber.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UHandGrabber::UHandGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHandGrabber::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UHandGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if(PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle -> SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}

}

void UHandGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle == nullptr)
	{
		return;
	}

	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);
	if(HasHit)
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->SetSimulatePhysics(true);
		HitComponent -> WakeAllRigidBodies();
		AActor* HitActor = HitResult.GetActor();
		HitActor->Tags.Add("Grabbed");
		HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		PhysicsHandle -> GrabComponentAtLocationWithRotation(HitComponent, NAME_None, HitResult.ImpactPoint, GetComponentRotation());
	
		
		//Debug Sphere
		//DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Green, false, 5);
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, false, 5);
		//AActor* HitActor = HitResult.GetActor();
		//UE_LOG(LogTemp, Display, TEXT("Hit actor: %s"), *HitActor -> GetActorNameOrLabel());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No actor hit"));
	}
}

void UHandGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle && PhysicsHandle ->GetGrabbedComponent())
	{
		AActor* GrabbedActor = PhysicsHandle -> GetGrabbedComponent() -> GetOwner();
		GrabbedActor->Tags.Remove("Grabbed");
		PhysicsHandle -> ReleaseComponent();
	}
}
UPhysicsHandleComponent* UHandGrabber ::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();
	if(Result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent."));
	}
	return Result;
}

bool UHandGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	//Drawing Debug Line
	FVector Start= GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld() -> SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, Sphere);

}


//float Damage = 0;
//	if(HasDamage(Damage))
//	{
//		PrintDamage(Damage);
//	}


// void UHandGrabber::PrintDamage(const float& Damage)
// {
// 	UE_LOG(LogTemp, Display, TEXT("Your Damage: %f"), Damage);
// }

// bool UHandGrabber::HasDamage(float& OutDamage)
// {
// 	OutDamage = 5;
// 	return true;
// }

	//References
	//float Damage = 0;
	//float& DamageRef = Damage;
	//DamageRef = 5;
	//UE_LOG(LogTemp, Display, TEXT("Your DamageRef is: %f, Damage: %f"), DamageRef, Damage);

	//FRotator MyRotation = GetComponentRotation();
	//FString RotationString = MyRotation.ToCompactString();
	//UE_LOG(LogTemp, Display, TEXT("Grabber Rotation: %s"), *RotationString);

	//float Time = GetWorld() -> TimeSeconds;

	//UE_LOG(LogTemp, Display, TEXT("Current Time Is: %f"), Time);