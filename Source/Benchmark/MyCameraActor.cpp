#include "MyCameraActor.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMyCameraActor::AMyCameraActor()
{
    PrimaryActorTick.bCanEverTick = true;
    CameraSpeed = 2.f;
    CurrentDistanceAlongSpline = 0.f;
}

// Called when the game starts or when spawned
void AMyCameraActor::BeginPlay()
{
    Super::BeginPlay();

    if (SplineActor)
    {
        // Try to get the SplineComponent from the assigned actor
        SplineComponent = Cast<USplineComponent>(SplineActor->GetComponentByClass(USplineComponent::StaticClass()));

        if (SplineComponent)
        {
            UE_LOG(LogTemp, Log, TEXT("SplineComponent successfully assigned from SplineActor."));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to find SplineComponent on assigned SplineActor."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("SplineActor not assigned in the editor."));
    }

    ActivateCamera();
}


void AMyCameraActor::ActivateCamera()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        PlayerController->SetViewTargetWithBlend(this, 0.0f);
    } else
    {
        UE_LOG(LogTemp, Error, TEXT("Player controller not ready!"));

    }
}

// Called every frame
void AMyCameraActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (SplineComponent)
    {
        // Update the distance along the spline
        CurrentDistanceAlongSpline += CameraSpeed * DeltaTime;

        // Get the spline length to loop back when reaching the end
        float SplineLength = SplineComponent->GetSplineLength();

        if (CurrentDistanceAlongSpline > SplineLength)
        {
            // CurrentDistanceAlongSpline = 0.f; // Reset distance for looping
            CameraSpeed = 0.f;
            if (BenchmarkMgr)  // Check if the reference is valid
            {
                BenchmarkMgr->OnBenchmarkComplete();
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("BenchmarkMgr reference is not set in MyCameraActor!"));
            }
        }

        // Get the location and rotation at the current distance along the spline
        FVector NewLocation = SplineComponent->GetLocationAtDistanceAlongSpline(CurrentDistanceAlongSpline, ESplineCoordinateSpace::World);
        FRotator NewRotation = SplineComponent->GetRotationAtDistanceAlongSpline(CurrentDistanceAlongSpline, ESplineCoordinateSpace::World);

        // Set the actor's location and rotation
        SetActorLocation(NewLocation);
        SetActorRotation(NewRotation);
    }
}