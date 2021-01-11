// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor %s has no PressurePlate on its OpenDoor component!"), *GetOwner()->GetName());
	}

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	if (PressurePlate && !PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		if (GetWorld()->GetTimeSeconds() >= DoorLastOpened + DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	FRotator OpenDoorRotation = GetOwner()->GetActorRotation();
	//OpenDoor.Yaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime*0.5f);
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	OpenDoorRotation.Yaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2);
	GetOwner()->SetActorRotation(OpenDoorRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	FRotator CloseDoorRotation = GetOwner()->GetActorRotation();
	//OpenDoor.Yaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime*0.5f);
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	CloseDoorRotation.Yaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, 2);
	GetOwner()->SetActorRotation(CloseDoorRotation);
}

