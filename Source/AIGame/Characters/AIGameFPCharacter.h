// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AIGamePlayerCharacter.h"
#include "AIGameFPCharacter.generated.h"

enum class EObjectShape : uint8;
/**
 * 
 */
UCLASS()
class AIGAME_API AAIGameFPCharacter : public AAIGamePlayerCharacter
{
	GENERATED_BODY()
public:

	AAIGameFPCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | FirstPerson")
	class USkeletalMeshComponent* FirstPersonMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | FirstPerson")
	class UCameraComponent* FirstPersonCameraComponent;

protected:
	virtual void GetObject(EObjectShape InShape) override;
	
	
};
