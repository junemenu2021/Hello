// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameJamIdea1HUD.generated.h"

UCLASS()
class AGameJamIdea1HUD : public AHUD
{
	GENERATED_BODY()

public:
	AGameJamIdea1HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

