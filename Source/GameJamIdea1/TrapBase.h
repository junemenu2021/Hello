// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrapBase.generated.h"

UCLASS()
class GAMEJAMIDEA1_API ATrapBase : public AActor {
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  ATrapBase();
  UFUNCTION(BlueprintCallable)
  virtual void OnTrigger();
  UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnTrigger"))
  void BP_OnTrigger();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;
};
