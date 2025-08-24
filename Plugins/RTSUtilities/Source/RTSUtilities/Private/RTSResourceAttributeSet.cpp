// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#include "RTSResourceAttributeSet.h"
#include "Net/UnrealNetwork.h"

void URTSResourceAttributeSet::OnRep_Wood(const FGameplayAttributeData& OldWood) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URTSResourceAttributeSet, Wood, OldWood);
}

void URTSResourceAttributeSet::OnRep_Food(const FGameplayAttributeData& OldFood) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URTSResourceAttributeSet, Food, OldFood);
}

void URTSResourceAttributeSet::OnRep_Stone(const FGameplayAttributeData& OldStone) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URTSResourceAttributeSet, Stone, OldStone);
}

void URTSResourceAttributeSet::OnRep_Gold(const FGameplayAttributeData& OldGold) 
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URTSResourceAttributeSet, Gold, OldGold);
}

void URTSResourceAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME_CONDITION_NOTIFY(URTSResourceAttributeSet, Wood, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(URTSResourceAttributeSet, Food, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(URTSResourceAttributeSet, Stone, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(URTSResourceAttributeSet, Gold, COND_None, REPNOTIFY_Always);
}