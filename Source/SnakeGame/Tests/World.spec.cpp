// My game copyright

#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "SnakeGame/Tests/Utils/TestUtils.h"
#include "SnakeGame/World/SG_Grid.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "SnakeGame/Core/Grid.h"
#include "SnakeGame/World/SG_WorldTypes.h"


BEGIN_DEFINE_SPEC(FSnakeWorld, "Snake",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
    UWorld* World;
    Snake::Dimension Dims;
    uint32 CellsSize;
    TSharedPtr<Snake::Grid> ModelGrid;
    UStaticMeshComponent* GridStaticMesh;
    ASG_Grid* GridVisual;
END_DEFINE_SPEC(FSnakeWorld)

void FSnakeWorld::Define()
{
    using namespace LifeExe::Test;

    Describe("WorldGrid", [this]()
    {
        BeforeEach([this]()
        {
            AutomationOpenMap("TestEmptyLevel");
            World = GetTestGameWorld();
            const char* GridBPName = "Blueprint'/Game/World/BP_SnakeGrid.BP_SnakeGrid'";

            Dims = Snake::Dimension{10, 10};
            CellsSize = 20;
            ModelGrid = MakeShared<Snake::Grid>(Dims);

            const FTransform OriginTransform = FTransform::Identity;
            GridVisual = CreateBlueprintDeferred<ASG_Grid>(World, GridBPName, OriginTransform);
            GridVisual->SetModel(ModelGrid, CellsSize);
            GridVisual->FinishSpawning(OriginTransform);

            auto* Comp = GridVisual->GetComponentByClass(UStaticMeshComponent::StaticClass());
            GridStaticMesh = Cast<UStaticMeshComponent>(Comp);
        });
        It("StaticGridMustHaveCorrectTransform", [this]()
        {
            const FBox Box = GridStaticMesh->GetStaticMesh()->GetBoundingBox();
            const auto Size = Box.GetSize();
            const auto WorldWidth = ModelGrid->dimension().width * CellsSize;
            const auto WorldHeight = ModelGrid->dimension().height * CellsSize;
            TestTrueExpr(GridStaticMesh->GetRelativeLocation().Equals(0.5 * FVector(WorldHeight,WorldWidth,-Size.Z)));
            TestTrueExpr(GridStaticMesh->GetRelativeScale3D().Equals(FVector(WorldHeight/Size.X,WorldWidth / Size.Y,1.0)));
        });

        It("ColorsMustBeSetupCorrectly", [this]()
        {
            FSnakeColors Colors;
            Colors.GridBackgroundColor = FLinearColor::Gray;
            Colors.GridLineColor = FLinearColor::Red;
            Colors.GridWallColor = FLinearColor::Green;
            GridVisual->UpdateColors(Colors);

            auto* Material = GridStaticMesh->GetMaterial(0);
            FLinearColor ColorToCheck;

            Material->GetVectorParameterValue(FName("BackgroundColor"), ColorToCheck);
            TestTrueExpr(ColorToCheck.Equals(Colors.GridBackgroundColor));

            Material->GetVectorParameterValue(FName("WallColor"), ColorToCheck);
            TestTrueExpr(ColorToCheck.Equals( Colors.GridWallColor));

            Material->GetVectorParameterValue(FName("LineColor"), ColorToCheck);
            TestTrueExpr(ColorToCheck.Equals(Colors.GridLineColor));

        });
    });

    Describe("WorldGrid", [this]()
    {
        BeforeEach([this]()
        {
            AutomationOpenMap("Level_1");
            World = GetTestGameWorld();
        });
        It("OnlyOneValidGridMustExist", [this]()
        {
            TArray<AActor*> Grids;
            UGameplayStatics::GetAllActorsOfClass(World, ASG_Grid::StaticClass(), Grids);
            TestTrueExpr(Grids.Num() == 1);
            TestNotNull("Grid actor exists", Grids[0]);
        });
    });
}

#endif
