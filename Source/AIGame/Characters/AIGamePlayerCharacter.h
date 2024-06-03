// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AIGameBaseCharacter.h"
#include "AIGamePlayerCharacter.generated.h"

class AAIGameToy;

UCLASS(Blueprintable)
class AIGAME_API AAIGamePlayerCharacter : public AAIGameBaseCharacter
{
	GENERATED_BODY()
public:

	AAIGamePlayerCharacter();
	// Create implementations of pure virtual functions of base class
	virtual void MoveForward(float Value) override;
	virtual void MoveRight(float Value) override;
	virtual void Turn(float Value) override;
	virtual void LookUp(float Value) override;
	virtual void Jump() override;
	virtual void GetObject(EObjectShape InShape) override;
	virtual void ThrowObject()override;

	

	//Add Camera and spring arm components in editor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Camera")
	class UCameraComponent* Camera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Parameters")
	float CharacterForce = 0;


protected:

	TSoftObjectPtr <AAIGameToy> GameToy;
	

	
};
