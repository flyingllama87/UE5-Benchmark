// FPSHUD.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BenchmarkManager.h" 
#include "FPSHUD.generated.h"

UCLASS()
class BENCHMARK_API AFPSHUD : public AHUD
{
    GENERATED_BODY()

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    virtual void DrawHUD() override;

private:
    ABenchmarkManager* BenchmarkManagerRef;
};
