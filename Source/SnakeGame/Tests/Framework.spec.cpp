// My game copyright

#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "SnakeGame/Tests/Utils/TestUtils.h"
#include "SnakeGame/Framework/SG_GameMode.h"
#include "SnakeGame/Framework/SG_Pawn.h"

BEGIN_DEFINE_SPEC(FSnakeFramework, "Snake",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
    UWorld* World;
END_DEFINE_SPEC(FSnakeFramework)

void FSnakeFramework::Define()
{
    using namespace LifeExe::Test;
    Describe("Framework", [this]()
       {
           It("GameMapMightExist", [this]()
           {
               const TArray<FString> SnakeGameMaps = {"Level_1"};
               TArray<FString> AllProjectMaps;
               IFileManager::Get().FindFilesRecursive(AllProjectMaps,*FPaths::ProjectContentDir(),TEXT("*.umap"),true,false);

               for(const auto& SnakeGameMap: SnakeGameMaps)
               {
                   const bool SnakeMapExists =  AllProjectMaps.ContainsByPredicate([&](const FString& ProjectMap)
                   {
                       FStringView OutPath, OutName, OutExit;
                       FPathViews::Split(FStringView(ProjectMap), OutPath, OutName, OutExit);
                       return SnakeGameMap.Equals(FString(OutName));
                   });
                   TestTrueExpr(SnakeMapExists);
               }
           });
       });
    
    Describe("Framework", [this]()
    {
        BeforeEach([this]()
        {
            AutomationOpenMap("Level_1");
            World = GetTestGameWorld();
        });
        It("ClassMightBeSetupCorrectly", [this]()
        {
            TestNotNull("Snake game mode set up", Cast<ASG_GameMode>(World->GetAuthGameMode()));
            TestNotNull("Snake pawn mode set up", Cast<ASG_Pawn>(World->GetFirstPlayerController()->GetPawn()));
        });
        xIt("PawnLocationMustBeAdjustCorrectly", [this]() { unimplemented() });
    });
}

#endif
