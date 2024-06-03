// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AIGamePlayerController.generated.h"


class AAIGameBaseCharacter;

UCLASS()
class AIGAME_API AAIGamePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	//Override base method of AController to set it responsible for the new pawn (InBaseCharacter)
	virtual void SetPawn(APawn* InPawn) override;

protected:

	//Implement player input 
	virtual void SetupInputComponent() override;

private:
	//Declaring our InBaseCharacter as Soft object pointer as we may need to refer it before it's created
	TSoftObjectPtr<AAIGameBaseCharacter>InBaseCharacter;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void Jump();
	void PickCube();
	void PichSphere();
	void ThrowObject();

	
	
};
	

