// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AIGameToy.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Characters/AIGamePlayerCharacter.h"
#include "Characters/AIGameAICharacter.h"
#include "BaseData/BaseData.h"

void AAIGameToy::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner()->IsA<AAIGamePlayerCharacter>())
	{
		InPlayerCharacter = StaticCast<AAIGamePlayerCharacter*>(GetOwner());
		
		
	}


}


AAIGameToy::AAIGameToy()
{
	bReplicates = true;
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));	
	RootComponent = CollisionComponent;
	CollisionComponent->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	CollisionComponent->SetCollisionProfileName(FName("OverlapOnlyPawn"), true);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CollisionComponent->SetCanEverAffectNavigation(0);
	
	

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(CollisionComponent);
	StaticMeshComponent->SetCollisionProfileName(FName("NoCollision"));
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	
}

inline void AAIGameToy::SetToyState(EObjectState NewState)
{
	ToyState = NewState;
}

void AAIGameToy::EnableOverlapEvents()
{
	if (IsValid(CollisionComponent))
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AAIGameToy::OnComponentBeginOverlap);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AAIGameToy::OnComponentEndOverlap);
	CollisionComponent->OnComponentHit.AddDynamic(this, &AAIGameToy::OnComponentHit);
	
}


void AAIGameToy::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->IsA<AAIGameAICharacter>() && ToyState != EObjectState::IsInPlayerHand)
	{
		bIsBeginOverlaped = true;

		AAIGameAICharacter* TakerAI = StaticCast<AAIGameAICharacter*>(OtherActor);
		CollisionComponent->SetSimulatePhysics(false);
		switch (Shape)
		{
		case EObjectShape::Sphere:
			TakerAI->SetScore(3);
			break;
		case EObjectShape::Cube:
			TakerAI->SetScore(1);
			break;
		}
		OnComponentOverlap(OtherActor);
		ToyState = EObjectState::IsTaken;
		InPlayerCharacter->SetObjectExist(false);
		this->Destroy();

	}

}

void AAIGameToy::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA<AAIGameAICharacter>() && ToyState != EObjectState::IsInPlayerHand && !bIsBeginOverlaped)
	{

		
		AAIGameAICharacter* TakerAI = StaticCast<AAIGameAICharacter*>(OtherActor);
		CollisionComponent->SetSimulatePhysics(false);
		switch (Shape)
		{
		case EObjectShape::Sphere:
			TakerAI->SetScore(3);
			break;
		case EObjectShape::Cube:
			TakerAI->SetScore(1);
			break;
		}
		ToyState = EObjectState::IsTaken;

		OnComponentOverlap(OtherActor);
		InPlayerCharacter->SetObjectExist(false);
		this->Destroy();
	}
}

void AAIGameToy::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ToyState != EObjectState::IsInPlayerHand)
	{
		
		HitLocation = Hit.Location;
		CalculateDistance();
	}
	
}




