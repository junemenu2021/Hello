// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorTimeDilation.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEJAMIDEA1_API UActorTimeDilation : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorTimeDilation();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	float TargetActorCustomDilation = 0.f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BLueprintCallable)
	void ChangeTimeDilation(float amount, bool isSelfAffected = false);
	
	UFUNCTION(BLueprintCallable)
	void ResetTimeDilation();

private:
	class AGameJamIdea1GameMode* GameMode;

		
};
