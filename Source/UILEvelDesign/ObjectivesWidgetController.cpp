// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectivesWidgetController.h"

void UObjectivesWidgetController::NativeConstruct()
{
	Super::NativeConstruct();

	if (ObjectiveText1 != nullptr)
	{
		ObjectiveText1->SetText(FText::FromString(TEXT("Working it seems")));
	}
	if (ObjectiveText2 != nullptr)
	{
		ObjectiveText2->SetText(FText::FromString(TEXT("Working it seems numer 2")));
	}
	if (NarrativeMessage != nullptr)
	{
		NarrativeMessage->SetText(FText::FromString(TEXT("HolAAAAaaaaaaaa !! Working it seems narrative")));
	}
	
}

void UObjectivesWidgetController::TestingMethod()
{
	UE_LOG(LogTemp, Warning, TEXT("Testing method Wiorking"));
}