// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameJamIdea1GameMode.generated.h"

UCLASS(minimalapi)
class AGameJamIdea1GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameJamIdea1GameMode();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetNewTargetGTD(float Value);

	UPROPERTY(BlueprintReadOnly)
	float TargetGlobalTimeDilation = 1.f;

protected:
	bool bIsInterping = false;
};



