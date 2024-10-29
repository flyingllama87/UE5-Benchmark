#include "BenchmarkManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Engine.h"


FTimerHandle DetailsTimer;


// Sets default values
ABenchmarkManager::ABenchmarkManager()
{
    // Set this actor to call Tick() every frame.  
    PrimaryActorTick.bCanEverTick = true;
    bBenchmarkComplete = false;
    RendererName = "";
    GPUName = "";
    Resolution = "";
}

// Called when the game starts or when spawned
void ABenchmarkManager::BeginPlay()
{
    Super::BeginPlay();
    bBenchmarkComplete = false;
    FPSHistory.Empty();
    GetWorld()->GetTimerManager().SetTimer(DetailsTimer, this, &ABenchmarkManager::GetRendererDetails, 0.2f, false);
}

// Called every frame
void ABenchmarkManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Calculate the FPS
    CurrentFPS = 1.0f / DeltaTime;
    if (bBenchmarkComplete == false)
        FPSHistory.Add(CurrentFPS);


    // Log the FPS to the output log
    // UE_LOG(LogTemp, Warning, TEXT("FPS: %.2f"), CurrentFPS);
}


void ABenchmarkManager::CalculateAvgFPS()
{
    AverageFPS = 0.0f;
    float tempFPS = 0.0f;
    for (int i = 0; i < FPSHistory.Num(); ++i)
    {
        tempFPS += FPSHistory[i];
    }
    AverageFPS = tempFPS / FPSHistory.Num();

}

void ABenchmarkManager::SaveResultsToDisk()
{
    FString SaveData = "Time,FPS\n";
    for (int32 i = 0; i < FPSHistory.Num(); ++i)
    {
        SaveData += FString::Printf(TEXT("%d,%.2f\n"), i, FPSHistory[i]);
    }

    FString SaveDataAvgFPS = FString::Printf(TEXT("%.2f\n"), AverageFPS);
    SaveDataAvgFPS += FString::Printf(TEXT("%s - %s - %s"), *GPUName, *RendererName, *Resolution);

    FString ProjectDir = FPaths::ProjectDir();
    FString ParentDir = FPaths::GetPath(ProjectDir.LeftChop(1));
    FString SavePath = ParentDir + "/BenchmarkResultsPerFrame.csv";
    FString SavePathAvgFPS = ParentDir + "/BenchmarkResults.txt";

    FFileHelper::SaveStringToFile(SaveData, *SavePath);
    FFileHelper::SaveStringToFile(SaveDataAvgFPS, *SavePathAvgFPS);
}

void ABenchmarkManager::OnBenchmarkComplete()
{
    bBenchmarkComplete = true;

    // Save results
    CalculateAvgFPS();
    SaveResultsToDisk();

    // Fade to black
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController && PlayerController->PlayerCameraManager)
    {
        PlayerController->bShowMouseCursor = true;

        // Set input mode to UI only
        FInputModeUIOnly InputMode;
        PlayerController->SetInputMode(InputMode);

        // Fade to black over 1 second
        PlayerController->PlayerCameraManager->StartCameraFade(
            0.0f,           // From Alpha (0 = fully visible)
            1.0f,           // To Alpha (1 = fully black)
            1.0f,           // Duration of fade in seconds
            FLinearColor::Black,  // Color to fade to
            false,          // Should fade be held after
            true            // Fade audio
        );
    }

    // Display end benchmark UI
    DisplayEndScreenUI();
}

void ABenchmarkManager::DisplayEndScreenUI()
{
    if (EndScreenWidgetClass)
    {
        UUserWidget* EndScreen = CreateWidget<UUserWidget>(GetWorld(), EndScreenWidgetClass);
        if (EndScreen)
        {
            EndScreen->AddToViewport();
        }
        else {
            UE_LOG(LogTemp, Warning, TEXT("No reference to EndScreenWidget!"));
        }
    }
}

void ABenchmarkManager::GetRendererDetails()
{
    if (GRHIAdapterName.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("No GPU adapter name available."));
    }
    else
    {
        GPUName = *GRHIAdapterName;
        RendererName = GDynamicRHI->GetName();
        FIntPoint ScreenResolution = GEngine->GameViewport->Viewport->GetSizeXY();
        int32 Width = ScreenResolution.X;
        int32 Height = ScreenResolution.Y;
        Resolution = FString::Printf(TEXT("%dx%d"), Width, Height);
    }
}

FString ABenchmarkManager::GetBenchmarkSettings()
{
    return FString::Printf(TEXT("%s - %s - %s"), *GPUName, *RendererName, *Resolution);
}