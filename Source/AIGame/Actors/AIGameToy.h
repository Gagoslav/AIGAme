// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIGameToy.generated.h"

enum class EObjectState : uint8;
enum class EObjectShape : uint8;
class AAIGamePlayerCharacter;

UCLASS()
class AIGAME_API AAIGameToy : public AActor
{
	GENERATED_BODY()

	
public:	
	virtual void BeginPlay() override;
	

	AAIGameToy();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	class UBoxComponent* CollisionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	class UStaticMeshComponent* StaticMeshComponent;

	UFUNCTION(BlueprintCallable)
	inline EObjectState GetToyState() { return ToyState; }

	UFUNCTION(BlueprintCallable)
	inline void SetToyState(EObjectState NewState);

	UFUNCTION(BlueprintImplementableEvent)
	void SetObjectShape(EObjectShape InShape);

	UFUNCTION(BlueprintImplementableEvent)
	void OnComponentOverlap(AActor* OtherActor);

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Shape")
	EObjectShape Shape;

	void EnableOverlapEvents();

protected:


	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
	inline FVector GetHitLocation() const { return HitLocation; }

	UFUNCTION(BlueprintImplementableEvent)
	void CalculateDistance();

private:
	EObjectState ToyState;
	AAIGamePlayerCharacter* InPlayerCharacter;
	bool bIsBeginOverlaped = false;
	FVector HitLocation = FVector::ZeroVector;

};
