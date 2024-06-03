// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AIGameCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class AIGAME_API UAIGameCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Animation")
	float Speed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Animation")
	bool bIsFalling = false;

private:
	// Animation is always loaded when we already have a character
	TWeakObjectPtr<class AAIGameBaseCharacter> InPlayerCharacter;
	
};
