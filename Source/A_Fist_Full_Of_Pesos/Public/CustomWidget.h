// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomWidget.generated.h"

UCLASS()
class A_FIST_FULL_OF_PESOS_API UCustomWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
        int Variable1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
        int Variable2;
};