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
	//if (NarrativeMessage != nullptr)
	//{
	//	OnDisplayNarrative(false, FText::GetEmpty(), 0);
	//}

	HudReference = Cast<AExtendedHUD>(GetOwningPlayer()->GetHUD());
	HudReference->OnSetNewObjectiveText.BindDynamic(this, &UObjectivesWidgetController::SetObjectiveStatus);
	HudReference->OnDisplayNarrativeTrigger.BindDynamic(this, &UObjectivesWidgetController::OnDisplayNarrative);

	// Just for testing if we are getting the HUD reference
	//if (HudReference)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Got Hud reference %s"), *HudReference->GetName());
	//}

	// Testing setting the text for the objective lines
	//SetObjectiveStatus(FText::FromString(TEXT("Working it seems")), 0);
	//SetObjectiveStatus(FText::FromString(TEXT("Working it seems numer 2")), 1);

	// Reset the Objectives Lines
	for (int Index = 0; Index < ListOfObjectivesLines.Num(); ++Index)
	{
		ToggleObjective(Index, true, true);
	}
}

void UObjectivesWidgetController::TestingMethod()
{
	UE_LOG(LogTemp, Warning, TEXT("Testing method Wiorking"));
	//OnDisplayNarrative(false, FText::GetEmpty(), 2);
	//OnDisplayNarrative(true, FText::FromString(TEXT("Changing the narrative")), 4);
}

void UObjectivesWidgetController::OnDisplayNarrative(bool bShow, FText NewText, float Duration)
{
	if (NarrativeMessage == nullptr)
	{
		return;
	}

	if (bShow)
	{
		NarrativeMessage->SetText(NewText);
		PlayAnimationForward(NarrativeFadeAnim, 1.5f);
		
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindLambda([&]
			{
				PlayAnimationReverse(NarrativeFadeAnim, 1.5f);
			});

		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, Duration, false);
	}
	else
	{
		PlayAnimationReverse(NarrativeFadeAnim, 1.5f);
	}
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
	if (!bIsObjectiveComplete)
	{
		ToggleObjective(ObjectiveIndex, false, false);
	}
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

void UObjectivesWidgetController::ToggleObjective(int ObjectiveIndex, bool bHide, bool bClearOnHide)
{
	// Guard if ObjectiveIndex is not valid
	if (ObjectiveIndex < 0 || ObjectiveIndex >= ListOfObjectivesLines.Num())
	{
		return;
	}
	
	if (bHide && bClearOnHide)
	{
		ClearObjectives();
		return;
	}

	if (bHide)
	{
		ListOfObjectivesLines[ObjectiveIndex]->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		ListOfObjectivesLines[ObjectiveIndex]->SetVisibility(ESlateVisibility::Visible);
	}
}