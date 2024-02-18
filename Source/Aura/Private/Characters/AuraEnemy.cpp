// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AuraEnemy.h"

#include "Aura.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraEnemy::AAuraEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	
	if(GetMesh() != nullptr)
	{
		GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}

	if(Weapon != nullptr)
	{
		Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}

	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::HighlightActor()
{

	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
}

void AAuraEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AAuraEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AAuraCharacter* Character = Cast<AAuraCharacter>(this);
	FColor MessageColor = FColor::Red;

	if(Character != nullptr)
	{
		MessageColor = FColor::Blue;
	}
	

	// if(GEngine != nullptr)
	// {
	
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, GetName());
	//}
	
	if(AbilitySystemComponent != nullptr)
	{
		if(const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AbilitySystemComponent->GetAttributeSet(UAuraAttributeSet::StaticClass())))
		{
			if(GEngine != nullptr)
			{
				FString Message = GetName() + " " + FString::SanitizeFloat(AuraAttributeSet->GetHealth());
				GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, Message);
			}
		}
	}
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();

	if(AbilitySystemComponent != nullptr)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}
