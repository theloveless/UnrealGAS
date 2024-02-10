// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AuraCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:

	AAuraEnemy();

	/** Begin Enemy interface */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/** End Enemy interface */


	
protected:
	
	virtual void BeginPlay() override;
};
