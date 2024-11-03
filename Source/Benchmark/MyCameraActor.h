#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "Camera/CameraActor.h"
#include "BenchmarkManager.h" 
#include "MyCameraActor.generated.h"

/**
 * A custom camera actor class that follows a spline path.
 */
UCLASS()
class BENCHMARK_API AMyCameraActor : public ACameraActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AMyCameraActor();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:

    // The benchmark manager
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Benchmark Manager")
    ABenchmarkManager* BenchmarkMgr;

    // The actor containing the spline
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Path")
    AActor* SplineActor;

    // Speed of the camera along the spline
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Path")
    float CameraSpeed;

    UFUNCTION(BlueprintCallable, Category = "Benchmark Camera")
    void ActivateCamera();

private:
    // Current distance along the spline
    float CurrentDistanceAlongSpline;

    // Spline component reference (not set in the editor, set in code)
    USplineComponent* SplineComponent;
};
