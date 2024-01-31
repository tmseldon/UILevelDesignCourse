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

	// Instantiating Billboards componenents
	ObjMarker = CreateDefaultSubobject<UBillboardComponent>(TEXT("ObjMarker"));
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	
	// Setting components into the new root
	ObjMarker->SetupAttachment(RootScene);
	Billboard->SetupAttachment(RootScene);

	// Box Collider
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(RootScene);

}

// Call every time this Blueprint is being spawned
void AObjectiveMarker::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	ToogleBoxCollider(bUseTrigger);
}


// Helper method to toogle or not the box collider for the marker
void AObjectiveMarker::ToogleBoxCollider(bool bIsActive)
{
	if (BoxCollider == nullptr)
	{
		return;
	}

	BoxCollider->SetActive(bIsActive);
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

