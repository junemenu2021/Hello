// Fill out your copyright notice in the Description page of Project Settings.

#include "AttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "ProjectCharacter.h"
#include "AbilitySystemComponent.h"

UAttributeSetBase::UAttributeSetBase() : Health(100.f), MaxHealth(100.f), Mana(200.f), MaxMana(200.f), AttackDamage(5.f), Strength(1.f), Intelligence(1.f)
{
  Health = MaxHealth;
  Mana = MaxMana;
  PreviousHealth = Health.GetCurrentValue();
}

void UAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)
{
  Super::PostGameplayEffectExecute(Data);

  Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.f, MaxHealth.GetCurrentValue()));
  Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.f, MaxHealth.GetCurrentValue()));
  if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Health)))
  {
    OnHealthChanged.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue(), Health.GetCurrentValue() == MaxHealth.GetCurrentValue(), PreviousHealth, Data.EffectSpec.GetContext().GetInstigator());
    PreviousHealth = Health.GetCurrentValue();
  }
  if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, MaxHealth)))
  {
    OnHealthChanged.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue(), Health.GetCurrentValue() == MaxHealth.GetCurrentValue(), PreviousHealth, Data.EffectSpec.GetContext().GetInstigator());
    PreviousHealth = Health.GetCurrentValue();
  }

  Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.f, MaxMana.GetCurrentValue()));
  Mana.SetBaseValue(FMath::Clamp(Mana.GetBaseValue(), 0.f, MaxMana.GetCurrentValue()));
  if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Mana)))
  {
    OnManaChanged.Broadcast(Mana.GetCurrentValue(), MaxMana.GetCurrentValue());
  }

  if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Strength)) || FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Intelligence)))
  {
    UpdateAllAttributes();
  }
}

float UAttributeSetBase::CalculateBaseAttackDamage() const
{
  return 5 + Strength.GetCurrentValue();
}

AProjectCharacter *UAttributeSetBase::GetOwningProjectCharacter() const
{
  return Cast<AProjectCharacter>(GetOwningActor());
}

void UAttributeSetBase::AddBaseAndCurrentValueOfAttribute(UPARAM(ref) FGameplayAttributeData &Data, float Value)
{
  FGameplayAttributeData NewData;
  NewData.SetBaseValue(Data.GetBaseValue() + Value);
  NewData.SetCurrentValue(Data.GetCurrentValue() + Value);
  Data = NewData;
  // Data.SetBaseValue(Data.GetBaseValue() + Value);
  // Data.SetCurrentValue(Data.GetCurrentValue() + Value);
}

void UAttributeSetBase::SetBaseAndCurrentValueOfAttribute(UPARAM(ref) FGameplayAttributeData &Data, float Value)
{
  FGameplayAttributeData NewData;
  NewData.SetBaseValue(Value);
  NewData.SetCurrentValue(Value);
  Data = NewData;
}

void UAttributeSetBase::UpdateAllAttributes()
{
  OnHealthChanged.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue(), Health.GetCurrentValue() == MaxHealth.GetCurrentValue(), PreviousHealth, GetOwningActor());
  PreviousHealth = Health.GetCurrentValue();

  OnManaChanged.Broadcast(Mana.GetCurrentValue(), MaxMana.GetCurrentValue());

  OnMainAttributeChanged.Broadcast(EAttributeType::Strength, Strength.GetCurrentValue());
  OnMainAttributeChanged.Broadcast(EAttributeType::Intelligence, Intelligence.GetCurrentValue());
}

UAbilitySystemComponent *UAttributeSetBase::GetOwnerASC() const
{
  return GetOwningAbilitySystemComponent();
}

void UAttributeSetBase::OnMainAttributeChangedFunction(EAttributeType Type, float CurrentAttributeValue)
{
  switch (Type)
  {
    case EAttributeType::Strength:
      SetBaseAndCurrentValueOfAttribute(AttackDamage, CalculateBaseAttackDamage());
      break;
  }
}

void UAttributeSetBase::BeginPlay()
{
  OnMainAttributeChanged.AddDynamic(this, &UAttributeSetBase::OnMainAttributeChangedFunction);
}
