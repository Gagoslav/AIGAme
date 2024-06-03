// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AIGameFPCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseData/BaseData.h"
#include "Actors/AIGameToy.h"

AAIGameFPCharacter::AAIGameFPCharacter()
{
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(RootComponent);
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 65.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = 1;

	FirstPersonMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	FirstPersonMeshComponent->SetupAttachment(FirstPersonCameraComponent);
	FirstPersonMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -130.0f));
	FirstPersonMeshComponent->CastShadow = 0;
	FirstPersonMeshComponent->bCastDynamicShadow = 0;
	FirstPersonMeshComponent->SetOnlyOwnerSee(true);

	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->bCastHiddenShadow = 1;

	Camera->SetActive(false);
	Camera->SetAutoActivate(false);

	SpringArm->SetActive(false);
	SpringArm->SetAutoActivate(false);

	GetCharacterMovement()->bOrientRotationToMovement = 0;
	bUseControllerRotationYaw = true;
}

void AAIGameFPCharacter::GetObject(EObjectShape InShape)
{
	Super::GetObject(InShape);


	if (GameToy->GetToyState() == EObjectState::IsInPlayerHand)
	{
		GameToy->SetActorRotation(GetActorRotation());

		//reset toy's relative location to 0, as we should attach it to socket
		GameToy->SetActorRelativeLocation(FVector::ZeroVector);

		//We want to attach to socket that is a part of FisrtPersonMeshComponent
		GameToy->AttachToComponent(FirstPersonMeshComponent, FAttachmentTransformRules::KeepRelativeTransform, HandsSocketName);
	}




}




