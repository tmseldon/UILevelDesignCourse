// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveMarker.h"
#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AObjectiveMarker::AObjectiveMarker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	if (bIsActive)
	{
		BoxCollider->SetCollisionProfileName(FName(TEXT("OverlapAllDynamic")));
	}
	else
	{
		BoxCollider->SetCollisionProfileName(FName(TEXT("NoCollision")));
	}
}

// Called when the game starts or when spawned
void AObjectiveMarker::BeginPlay()
{
	Super::BeginPlay();
	
	if (BoxCollider != nullptr)
	{
		BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AObjectiveMarker::ManageMarkerTrigger);
	}
	
}


// Signature method for the OnComponentBeginOverlap event
void AObjectiveMarker::ManageMarkerTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Collider detecting"));
	if (bEnable && bIsFirstCheck)
	{
		bIsFirstCheck = false;
		OnReachedToMarker.ExecuteIfBound();

		if (bDisabledOnReach)
		{
			EnableObjectiveMarker(false, false);
			if (NextMarker)
			{
				NextMarker->EnableObjectiveMarker(true, false);
			}
		}
	}
}

void AObjectiveMarker::EnableObjectiveMarker(bool bChangeEnable, bool bChangeDisabledOnReach)
{
	bEnable = bChangeEnable;
	bDisabledOnReach = bChangeDisabledOnReach;
	bIsFirstCheck = true;
}

// Called every frame
void AObjectiveMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

