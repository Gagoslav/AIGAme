// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/AIGamePlayerController.h"
#include "Characters/AIGameBaseCharacter.h"
#include "BaseData/BaseData.h"

void AAIGamePlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	// Not to crash if we have invalid type
	InBaseCharacter = Cast<AAIGameBaseCharacter>(InPawn);

}

void AAIGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &AAIGamePlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AAIGamePlayerController::MoveRight);
	InputComponent->BindAxis("Turn", this, &AAIGamePlayerController::Turn);
	InputComponent->BindAxis("LookUp", this, &AAIGamePlayerController::LookUp);
	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AAIGamePlayerController::Jump);
	InputComponent->BindAction("PickCube", EInputEvent::IE_Pressed, this, &AAIGamePlayerController::PickCube);
	InputComponent->BindAction("PickSphere", EInputEvent::IE_Pressed, this, &AAIGamePlayerController::PichSphere);
	InputComponent->BindAction("Throw", EInputEvent::IE_Pressed, this, &AAIGamePlayerController::ThrowObject);

}

void AAIGamePlayerController::MoveForward(float Value)
{
	if (InBaseCharacter.IsValid())
	{
		InBaseCharacter->MoveForward(Value);
	}

}

void AAIGamePlayerController::MoveRight(float Value)
{
	if (InBaseCharacter.IsValid())
	{
		InBaseCharacter->MoveRight(Value);
	}
}

void AAIGamePlayerController::Turn(float Value)
{
	if (InBaseCharacter.IsValid())
	{
		InBaseCharacter->Turn(Value);
	}
}

void AAIGamePlayerController::LookUp(float Value)
{
	if (InBaseCharacter.IsValid())
	{
		InBaseCharacter->LookUp(Value);
	}
}

void AAIGamePlayerController::Jump()
{
	if (InBaseCharacter.IsValid())
	{
		InBaseCharacter->Jump();
	}
}

void AAIGamePlayerController::PickCube()
{
	if (InBaseCharacter.IsValid())
	{
		InBaseCharacter->GetObject(EObjectShape::Cube);
	}
}

void AAIGamePlayerController::PichSphere()
{
	if (InBaseCharacter.IsValid())
	{
		InBaseCharacter->GetObject(EObjectShape::Sphere);
	}
}



void AAIGamePlayerController::ThrowObject()
{
	if (InBaseCharacter.IsValid())
	{
		
		InBaseCharacter->ThrowObject();
	}
}
