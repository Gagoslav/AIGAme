// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIGameBaseCharacter.generated.h"

enum class EObjectShape :uint8;


// As this is a base class it should be abstract
UCLASS(Abstract, NotBlueprintable)
class AIGAME_API AAIGameBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAIGameBaseCharacter();

	//declaring pure virtual methods in an abstract base class to implement them in derived classes
	virtual void MoveForward(float Value) {};
	virtual void MoveRight(float Value) {};
	virtual void Turn(float Value) {};
	virtual void LookUp(float Value) {};
	virtual void GetObject(EObjectShape InShape) {};
	virtual void ThrowObject() {};

	UFUNCTION(BlueprintCallable)
	inline bool GetObjectExist() const { return IsObjectEquipped; }

	UFUNCTION(BlueprintCallable)
	inline void SetObjectExist (bool IsEquiped) { IsObjectEquipped = IsEquiped; }
protected:

	


private:
	bool IsObjectEquipped = 0;

};
