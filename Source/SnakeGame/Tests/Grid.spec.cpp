// My game copyright

#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "SnakeGame/Core/Grid.h"

DEFINE_SPEC(FSnakeGrid, "Snake", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)


void FSnakeGrid::Define()
{
    using namespace Snake;
    Describe("CoreGrid", [this]() { It("DimsMightIncludeWalls", [this]()
        {
            const Grid grid(Dimension{12,10});
        TestTrueExpr(grid.dimension().width==14);
        TestTrueExpr(grid.dimension().height==12);
        
        }); });
}

#endif
