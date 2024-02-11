// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtendedHUD.h"
#include "Blueprint/UserWidget.h"

// Called when the game starts or when spawned
void AExtendedHUD::BeginPlay()
{
	Super::BeginPlay();

	CharacterController = this->GetOwningPlayerController();

	if (ObjectivesScreen == nullptr)
	{
		return;
	}

	WidgetSpawned = CreateWidget(CharacterController, ObjectivesScreen, FName(TEXT("ObjectivesDisplay")));

	if (WidgetSpawned != nullptr)
	{
		WidgetSpawned->AddToViewport();
	}
}