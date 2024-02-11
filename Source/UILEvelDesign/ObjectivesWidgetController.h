// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/MultiLineEditableText.h"
#include "ObjectivesWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class UILEVELDESIGN_API UObjectivesWidgetController : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UMultiLineEditableText* ObjectiveText1;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UMultiLineEditableText* ObjectiveText2;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UMultiLineEditableText* NarrativeMessage;

private:

	void NativeConstruct() override;
};
