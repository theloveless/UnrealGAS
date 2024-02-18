// Fill out your copyright notice in the Description page of Project Settings.
#include "Characters/AuraCharacterBase.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Characters/AuraCharacter.h"


AAuraCharacterBase::AAuraCharacterBase()
{

	PrimaryActorTick.bCanEverTick = true;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if(GEngine != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, GetName());
	}

}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


}
