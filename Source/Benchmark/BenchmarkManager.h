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
    ABenchmarkManager();

protected:
    virtual void BeginPlay() override;

public:
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
