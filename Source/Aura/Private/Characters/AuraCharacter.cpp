// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//This is how fast the character rotates when orienting to movement
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	/** Init ability actor info for the server.	
	 */
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//This is for the client
	InitAbilityActorInfo();
	
}

void AAuraCharacter::InitAbilityActorInfo()
{	AAuraPlayerState* AuraPlayerState = Cast<AAuraPlayerState>(GetPlayerState());

	check(AuraPlayerState);
	
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();

	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);
}
