#include "PreCompile.h"
#include "TestGameMode.h"
#include "Village.h"
#include "Camp.h"
#include <EngineCore/EngineEditorGUI.h>
#include "MapDebugGUI.h"
#include "Player.h"
#include "WaterCourse.h"
#include "WaterBomb.h"

ATestGameMode::ATestGameMode()
{
}

ATestGameMode::~ATestGameMode()
{
}

void ATestGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -400.0f));

	std::shared_ptr<ACamp> Camp = GetWorld()->SpawnActor<ACamp>("Camp");
	SetCurMap(Camp);
	Camp->SetCurGameMode(this);
	Camp->AddObjectInit();

	Player1 = GetWorld()->SpawnActor<APlayer>("Player1", 0);
	Player1->SetCurGameMode(this);
	SetMainPlayer(Player1);

#ifdef _DEBUG
	InputOn();
#endif
}

void ATestGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

#ifdef _DEBUG
	FVector MousePos = GetWorld()->GetMainCamera()->ScreenPosToWorldPos(GEngine->EngineWindow.GetScreenMousePos());
	std::string Msgs = std::format("Mouse Position : {}", MousePos.ToString());
	UMapDebugGUI::PushMsg(Msgs);
	Msgs = std::format("y : {}, x : {}", GetCurMap()->PosToPoint(MousePos).y, GetCurMap()->PosToPoint(MousePos).x);
	UMapDebugGUI::PushMsg(Msgs);

	if (true == IsDown('N'))
	{
		GetCurMap()->SpawnWaterBomb(GetPlayer()->GetActorLocation()); // ��ǳ�� ����.
	}
#endif // _DEBUG
}

void ATestGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

#ifdef _DEBUG
	if (nullptr == MapDebugWindow)
	{
		MapDebugWindow = UEngineEditorGUI::CreateEditorWindow<UMapDebugGUI>("MapObject");
	}
	MapDebugWindow->On();
#endif // _DEBUG
}

void ATestGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}
