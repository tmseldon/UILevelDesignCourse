// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectivesWidgetController.h"
#include "ExtendedHUD.h"
#include "Animation/WidgetAnimation.h"
#include "Components/MultiLineEditableText.h"

void UObjectivesWidgetController::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ObjectiveText1 != nullptr)
	{
		ListOfObjectivesLines.Emplace(ObjectiveText1);
	}
	if (ObjectiveText2 != nullptr)
	{
		ListOfObjectivesLines.Emplace(ObjectiveText2);
	}
	if (NarrativeMessage != nullptr)
	{
		NarrativeMessage->SetText(FText::FromString(TEXT("HolAAAAaaaaaaaa !! Working it seems narrative")));
	}

	HudReference = Cast<AExtendedHUD>(GetOwningPlayer()->GetHUD());

	// Just for testing if we are getting the HUD reference
	//if (HudReference)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Got Hud reference %s"), *HudReference->GetName());
	//}

	SetObjectiveStatus(FText::FromString(TEXT("Working it seems")), 0);
	SetObjectiveStatus(FText::FromString(TEXT("Working it seems numer 2")), 1);
}

void UObjectivesWidgetController::TestingMethod()
{
	UE_LOG(LogTemp, Warning, TEXT("Testing method Wiorking"));
}

void UObjectivesWidgetController::OnDisplayNarrative(bool bShow, FText NewText, float Duration)
{

}

UMultiLineEditableText* UObjectivesWidgetController::GetObjectiveLinePointer(int IndexNumber) const
{
	if (ListOfObjectivesLines.Num() == 0)
	{
		return nullptr;
	}

	// By default we return just the first element if the list has only one element
	if (ListOfObjectivesLines.Num() == 1)
	{
		return ListOfObjectivesLines[0];
	}

	return ListOfObjectivesLines[IndexNumber];
}

// Set New or Complete status for an objective
void UObjectivesWidgetController::SetObjectiveStatus(FText ObjectivePhrase, int ObjectiveIndex, bool bIsObjectiveComplete)
{
	UMultiLineEditableText* ObjectiveReference = GetObjectiveLinePointer(ObjectiveIndex);

	if (ObjectiveReference == nullptr)
	{
		return;
	}

	ObjectiveReference->SetText(ObjectivePhrase);
	SetStyleObjective(ObjectiveReference, bIsObjectiveComplete);
}

// Set Text Style based on if it is complete or not through bIsComplete
void UObjectivesWidgetController::SetStyleObjective(UMultiLineEditableText* Objective, bool bIsComplete)
{
	if (Objective == nullptr)
	{
		return;
	}

	FSlateColor ColorStyle = bIsComplete ? FSlateColor(FLinearColor::Green) : FSlateColor(FLinearColor::White);
	Objective->WidgetStyle.SetColorAndOpacity(ColorStyle);
	//Objective->SetWidgetStyle(FTextBlockStyle().SetColorAndOpacity(ColorStyle));
}

void UObjectivesWidgetController::ClearObjectives()
{
	if (ListOfObjectivesLines.IsEmpty())
	{
		return;
	}

	int NumberObjectiveTexts = ListOfObjectivesLines.Num();

	for (int Index = 0; Index < NumberObjectiveTexts; ++Index)
	{
		SetObjectiveStatus(FText::GetEmpty(), Index);
	}
}