// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemReplicationProxyInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

AAuraEffectActor::AAuraEffectActor()
{

	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::EndOverlap);
	Sphere->SetupAttachment(GetRootComponent());
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO to apply a gameplay effect. For now, using const_cast as a hack
	if(IAbilitySystemInterface* AScInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
	//	UE_LOG(LogTemp, Warning, TEXT("Yes!"));

		const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AScInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		UAuraAttributeSet* MutableAuraAttributeset = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
		//AuraAttributSet->init
		MutableAuraAttributeset->SetHealth(AuraAttributeSet->GetHealth() + 25.f);

		UE_LOG(LogTemp, Warning, TEXT("Health: %f"), MutableAuraAttributeset->GetHealth());
		
		Destroy();
	}	
}

void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}	

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}
