// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorTimeDilation.h"
#include "Kismet/GameplayStatics.h"
#include "GameJamIdea1GameMode.h"

// Sets default values for this component's properties
UActorTimeDilation::UActorTimeDilation()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UActorTimeDilation::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase *CurrentGameMode = UGameplayStatics::GetGameMode(this);
	if (CurrentGameMode)
	{
		AGameJamIdea1GameMode *GM = Cast<AGameJamIdea1GameMode>(CurrentGameMode);
		if (GM)
		{
			GameMode = GM;
		}
	}

	// ...
}

// Called every frame
void UActorTimeDilation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Interp global
}

void UActorTimeDilation::ChangeTimeDilation(float amount, bool isSelfAffected)
{
	if (!ensure(GameMode)) return;
	if (!isSelfAffected)
	{
		AActor *Owner = this->GetOwner();
		if (!ensure(Owner))
			return;
		Owner->CustomTimeDilation = 1 / amount;
	}
	GameMode -> SetNewTargetGTD(amount);
}

void UActorTimeDilation::ResetTimeDilation()
{
	if (!ensure(GameMode)) return;
	GameMode -> SetNewTargetGTD(1.f);

	AActor *Owner = this->GetOwner();
	if (!ensure(Owner))
		return;
	Owner->CustomTimeDilation = 1;
}
