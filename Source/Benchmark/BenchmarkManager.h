// FPSActor.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include "Misc/EngineVersion.h"
#include "BenchmarkManager.generated.h"

UCLASS()
class BENCHMARK_API ABenchmarkManager : public AActor
{
    GENERATED_BODY()
    
public:
    // Sets default values for this actor's properties
    ABenchmarkManager();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    void SaveResultsToDisk();
    void CalculateAvgFPS();
    void OnBenchmarkComplete();
    void GetRendererDetails();
    bool bBenchmarkComplete;
    float CurrentFPS;

    UPROPERTY(BlueprintReadOnly, Category = "Benchmark Data")
    FString RendererName;
    UPROPERTY(BlueprintReadOnly, Category = "Benchmark Data")
    FString GPUName;
    UPROPERTY(BlueprintReadOnly, Category = "Benchmark Data")
    FString Resolution;
    UPROPERTY(BlueprintReadOnly, Category = "Benchmark Data")
    float AverageFPS;
    UFUNCTION(BlueprintCallable, Category = "Benchmark Data")
    float GetAverageFPS() const { return AverageFPS; }
    UFUNCTION(BlueprintCallable, Category = "Benchmark Data")
    FString GetBenchmarkSettings();

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<class UUserWidget> EndScreenWidgetClass;

private:
    TArray<float> FPSHistory;
    void DisplayEndScreenUI();
};
