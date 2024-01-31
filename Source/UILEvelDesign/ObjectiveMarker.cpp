// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveMarker.h"
#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AObjectiveMarker::AObjectiveMarker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("CreatedRoot"));
	SetRootComponent(RootScene);

	// Instantiating componenents
	ObjMarker = CreateDefaultSubobject<UBillboardComponent>(TEXT("ObjMarker"));
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	
	// Setting components into the new root
	ObjMarker->SetupAttachment(RootScene);
	Billboard->SetupAttachment(RootScene);
	BoxCollider->SetupAttachment(RootScene);
}

// Called when the game starts or when spawned
void AObjectiveMarker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjectiveMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

