// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AIGameBaseCharacter.h"

AAIGameBaseCharacter::AAIGameBaseCharacter()
{
	GetMesh()->CastShadow = 1;
	GetMesh()->bCastDynamicShadow = 1;
}
