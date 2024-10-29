// YourHUD.cpp
#include "FPSHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"
// #include "BenchmarkManager.h"
#include "UObject/ConstructorHelpers.h"


void AFPSHUD::BeginPlay()
{
    Super::BeginPlay();

    // Find the BenchmarkActor in the world
    BenchmarkManagerRef = Cast<ABenchmarkManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ABenchmarkManager::StaticClass()));
}

void AFPSHUD::DrawHUD()
{
    Super::DrawHUD();

    if (BenchmarkManagerRef)
    {

        float LastFPS = BenchmarkManagerRef->CurrentFPS;

        UFont* CustomFont = LoadObject<UFont>(nullptr, TEXT("/Game/Benchmark/Font/RubikWetPaint-Regular_Font.RubikWetPaint-Regular_Font"));
        UFont* CustomFontSmall = LoadObject<UFont>(nullptr, TEXT("/Game/Benchmark/Font/RubikWetPaint-Regular_Font_sm.RubikWetPaint-Regular_Font_sm"));

        // Set up text strings
        FString Line1 = FString::Printf(TEXT("FPS: %.2f"), LastFPS);
        FString Line2 = FString::Printf(TEXT("%s - %s - %s"), *BenchmarkManagerRef->GPUName, *BenchmarkManagerRef->RendererName, *BenchmarkManagerRef->Resolution);

        // Set positions and colors
        FVector2D PositionLine1(50, 50);  // Adjusted positions
        FVector2D PositionLine2(50, 150);

        // Define colors with opacity
        FLinearColor Line1Color = FLinearColor(1.0f, 0.2f, 0.2f, 0.9f);  // Slightly transparent red
        FLinearColor Line2Color = FLinearColor(0.2f, 0.2f, 1.0f, 0.9f);  // Slightly transparent blue

        // Shadow settings
        FVector2D ShadowOffset(2.0f, 2.0f);
        FLinearColor ShadowColor = FLinearColor(0, 0, 0, 0.6f);  // Softer black shadow

        FVector2D TextScale(1.0f, 1.0f);

        // First line setup and drawing
        FCanvasTextItem TextItemLine1(PositionLine1, FText::FromString(Line1), CustomFont ? CustomFont : GEngine->GetLargeFont(), Line1Color);
        TextItemLine1.Scale = TextScale;
        TextItemLine1.EnableShadow(ShadowColor, ShadowOffset);
        Canvas->DrawItem(TextItemLine1);

        // Second line setup and drawing
        FCanvasTextItem TextItemLine2(PositionLine2, FText::FromString(Line2), CustomFontSmall ? CustomFontSmall : GEngine->GetLargeFont(), Line2Color);
        TextItemLine2.Scale = TextScale;
        TextItemLine2.EnableShadow(ShadowColor, ShadowOffset);
        Canvas->DrawItem(TextItemLine2);

    }
}
