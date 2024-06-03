// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/AIGameCharacterAnimInstance.h"
#include "Characters/AIGameBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"



void UAIGameCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	checkf(TryGetPawnOwner()->IsA<AAIGameBaseCharacter>(), TEXT("Pawn owner should be AAIGameBaseCharacter, otherwise we will have a crash"));
	InPlayerCharacter = StaticCast<AAIGameBaseCharacter*>(TryGetPawnOwner());
}

void UAIGameCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!InPlayerCharacter.IsValid())
	{
		return;
	}
	
	Speed = InPlayerCharacter->GetCharacterMovement()->Velocity.Size();
	
	bIsFalling = InPlayerCharacter->GetCharacterMovement()->IsFalling();
	

	
}