// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#include "RTSPlayerState.h"
#include "RTSResourceAttributeSet.h"
#include "AbilitySystemComponent.h"

ARTSPlayerState::ARTSPlayerState() 
{
    ResourceAttributeSet = CreateDefaultSubobject<URTSResourceAttributeSet>(TEXT("ResourceAttributeSet"));

    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}