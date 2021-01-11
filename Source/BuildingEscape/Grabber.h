// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

	public:	
		// Sets default values for this component's properties
		UGrabber();

		// Member functions
		void Grab();
		void Release();
		void FindPhysicsHandle();
		void SetupInputComponent();
		FHitResult GetFirstPhysicsBodyInReach() const;

		// Called every frame
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	protected:
		// Called when the game starts
		virtual void BeginPlay() override;

	private:
		// Member variables
		float Reach = 200.f;
		UPhysicsHandleComponent* PhysicsHandle = nullptr;
		UInputComponent* InputComponent = nullptr;
		FVector PlayerViewpointLocation;
		FRotator PlayerViewpointRotation;
};
