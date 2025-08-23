// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#pragma once

UENUM(BlueprintType)
enum class EResourceTypes : uint8
{
    Wood UMETA(DisplayName = "Wood"),
    Food UMETA(DisplayName = "Food"),
    Gold UMETA(DisplayName = "Gold"),
    Stone UMETA(DisplayName = "Stone"),
    Population UMETA(DisplayName = "Population")
};

UENUM(BlueprintType)
enum class EActorType : uint8
{
    Villager UMETA(DisplayName = "Villager"),
    Knight UMETA(DisplayName = "Knight"),
    Paladin UMETA(DisplayName = "Paladin"),

    House UMETA(DisplayName = "House")
};