// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGamePlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Actors/AIGameToy.h"
#include "BaseData/BaseData.h"
#include "Components/BoxComponent.h"



AAIGamePlayerCharacter::AAIGamePlayerCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bUsePawnControlRotation = 1;

	Camera = CreateDefaultSubobject <UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = 0;

	GetCharacterMovement()->bOrientRotationToMovement = 1;


}

void AAIGamePlayerCharacter::MoveForward(float Value)
{
	// consider some small inaccuracies
	if (!FMath::IsNearlyZero(Value, 1e-6))
	{
		FRotator YawRotator(0.0f, GetControlRotation().Yaw, 0.0f);
		// to move a character along the mouse direction
		FVector Forward = YawRotator.RotateVector(FVector::ForwardVector);
		AddMovementInput(Forward, Value);
	}

}

void AAIGamePlayerCharacter::MoveRight(float Value)
{
	// consider some small inaccuracies
	if (!FMath::IsNearlyZero(Value, 1e-6))
	{
		FRotator YawRotator(0.0f, GetControlRotation().Yaw, 0.0f);
		// to move a character along the mouse direction
		FVector Right = YawRotator.RotateVector(FVector::RightVector);
		AddMovementInput(Right, Value);
	}

}

void AAIGamePlayerCharacter::Turn(float Value)
{

	AddControllerYawInput(Value);
}

void AAIGamePlayerCharacter::LookUp(float Value)
{

	AddControllerPitchInput(Value);
}

void AAIGamePlayerCharacter::Jump()
{
	Super::Jump();

}

void AAIGamePlayerCharacter::GetObject(EObjectShape InShape)
{
	if (!GetObjectExist())
	{
		SetObjectExist(true);
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		FVector SpawnStart = FVector::ForwardVector * 100;

		// As we set the shape of static mesh in blueprint of Toy we need to spawn it from blueprint class
		UClass* BlueprintToyClass = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Game/Core/Actors/BP_Toy.BP_Toy_C")); // also add suffix _C to specify that's a class

		//Spawn object from blueprint class only if we don't have an equiped object  yet
		if (IsValid(BlueprintToyClass))
		{
			UE_LOG(LogTemp, Warning, TEXT("Blueprint Actor BP_Toy's Path found"));
			GameToy = GetWorld()->SpawnActor<AAIGameToy>(BlueprintToyClass, SpawnStart, GetActorRotation(), SpawnParameters);
			GameToy->SetToyState(EObjectState::IsInPlayerHand);
			GameToy->SetObjectShape(InShape);
			GameToy->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform, FName(NAME_None));
			
		}

		else
		{
			UE_LOG(LogTemp, Error, TEXT("Path is wrong"));

		}



	}

}

void AAIGamePlayerCharacter::ThrowObject()
{
	
	
	if (!GetObjectExist())
	{
		return;
	}

	else
	{
		// Enable physics and throw object
		GameToy->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		GameToy->CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		GameToy->CollisionComponent->SetSimulatePhysics(true);
		GameToy->CollisionComponent->SetMassOverrideInKg(FName(""), 1);
		

		// Get Direction of Joy flight
		
		FRotator PitchRotator = FRotator(GetControlRotation().Pitch, GetControlRotation().Yaw, 0.0f);
		FVector ImpulsVector = PitchRotator.RotateVector(FVector::ForwardVector * CharacterForce * 100);
		//Throw object only if the object is in the player's hands
		switch (GameToy->GetToyState())
		{
		case EObjectState::IsInPlayerHand:
			GameToy->SetToyState(EObjectState::IsInAir);
			GameToy->EnableOverlapEvents();
			GameToy->CollisionComponent->AddImpulse(ImpulsVector);
			break;

		default:
			break;
		}
		
		
	}
}




