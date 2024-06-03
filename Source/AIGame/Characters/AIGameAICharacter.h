// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AIGameBaseCharacter.h"
#include "AIGameAICharacter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class AIGAME_API AAIGameAICharacter : public AAIGameBaseCharacter
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Score")
	inline int GetScore() const { return Score; }

	UFUNCTION(BlueprintCallable, Category = "Score")
	void SetScore(int InScore) { Score += InScore; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Name")
	FName CharacterName = FName(NAME_None);

private:
	int Score = 0;
	
};
