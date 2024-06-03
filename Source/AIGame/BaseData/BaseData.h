// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseData.generated.h"

UENUM(BlueprintType)
enum class EObjectState : uint8
{
	IsInPlayerHand,
	IsInAir,
	IsTaken
};

UENUM(BlueprintType)
enum class EObjectShape : uint8
{
	Cube,
	Sphere
};

// Name of socket between two hands Should be const
const FName HandsSocketName = FName("SocketHandMiddle");

 

class AIGAME_API BaseData 
{

public:
	
};
