#include "PreCompile.h"
#include "MainGameMode.h"

#include <EngineCore/TextWidget.h>
#include <EnginePlatform/TextimeInput.h>

#include "MapUI.h"
#include "Player.h"
#include "OtherPlayer.h"

#include "Village.h"
#include "Camp.h"
#include "Player_Name.h"

#include "ItemBubble.h"
#include "ItemRoller.h"
#include "ItemNiddle.h"
#include "ItemOwl.h"
#include <EngineBase/NetObject.h>
#include "WaterCourse.h"

#include "ServerGameMode.h"
#include "Game_Core.h"


AMainGameMode::AMainGameMode()
{
}

AMainGameMode::~AMainGameMode()
{
}

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetMainCamera()->DepthOn();
	//���̹��� ����� DepthOn

	GameModeActorInit();

	
#ifdef _DEBUG
	InputOn();
#endif
}

void AMainGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	//UTextimeInput::IMEInput();
	std::string Text = UTextimeInput::GetReadText();
	if (Text.size() > 0)
	{
		ShowText->SetText(Text);
	}
	else
	{
		ShowText->SetText(" ");
	}

}

void AMainGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);



	if (AServerGameMode::NetType == ENetType::Server)
	{
			{
				//UGame_Core::Net = std::make_shared<UEngineServer>();
				//UGame_Core::Net->ServerOpen(30000, 512);

				// ���⿡�� ���� �÷��̾����� ��ȣ�� �ϳ� �̴ٰϴ�.
				MainPlayer->SetObjectToken(UNetObject::GetNewObjectToken());

				// Ÿ�� ������
				//MapUI->SetObjectToken(UNetObject::GetNewObjectToken());
				//����ź
				//MainPlayer->WaterBomb_Token = UGame_Core::Net->GetSessionToken() * 1000 + 2;
				//ServerPacketInit(UGame_Core::Net->Dispatcher);
			};
	}
	else if (AServerGameMode::NetType == ENetType::Client)
	{
			{
				//UGame_Core::Net = std::make_shared<UEngineClient>();
				//UGame_Core::Net->Connect(IP, PORT);

				//UGame_Core::Net->SetTokenPacketFunction([=](USessionTokenPacket* _Token)
					//{
					MainPlayer->SetObjectToken(UGame_Core::Net->GetSessionToken() * 1000);

					//	//Ÿ�� ������
					//	MapUI->SetObjectToken(_Token->GetSessionToken() * 1000 + 1);
					//	if (nullptr != MapUI)
					//	{
					//		MapUI->ClientCreate();
					//	}
					//	//����ź
					//	MainPlayer->WaterBomb_Token = _Token->GetSessionToken() * 1000 + 2;
					//});
				// � ��Ű�� ������ ��� ó���Ұ����� ���ϴ� �� �ؾ��Ѵ�.
				//ClientPacketInit(UGame_Core::Net->Dispatcher);
			};
	}




}

void AMainGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}


void AMainGameMode::GameModeActorInit()
{
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(80.0f, 1.0f, -1000.0f));



	/*std::shared_ptr<ACamp> Camp = GetWorld()->SpawnActor<ACamp>("Camp");
	SetCurMap(Camp);
	Camp->SetCurGameMode(this);*/

	std::shared_ptr<AVillage> Village = GetWorld()->SpawnActor<AVillage>("Village");
	SetCurMap(Village);
	Village->SetCurGameMode(this);


	MainPlayer = GetWorld()->SpawnActor<APlayer>("Player1", 0);
	MainPlayer->SetCurGameMode(this);
	SetMainPlayer(MainPlayer);


	{//UI

		std::shared_ptr<AMapUI> MapUI = GetWorld()->SpawnActor<AMapUI>("MapUI");
		MapUI->SetCurGameMode(this);
	}



	{//Text
		ShowText = CreateWidget<UTextWidget>(GetWorld(), "ShowText");
		ShowText->SetFont("���� ���");
		ShowText->SetScale(30.0f);
		ShowText->SetColor(Color8Bit::Black);
		ShowText->SetPosition({ 0.0f ,0.0f });
		ShowText->SetFlag(FW1_LEFT);
		ShowText->AddToViewPort(11);
	}

	////Item - Camp
	//{
	//	Camp->AddMapObject(5, 1, EMapObject::Item, EItemType::ItemBubble);
	//	Camp->AddMapObject(1, 2, EMapObject::Item, EItemType::ItemNiddle);
	//	Camp->AddMapObject(2, 1, EMapObject::Item, EItemType::ItemOwl);
	//	Camp->AddMapObject(2, 2, EMapObject::Item, EItemType::ItemShoes);
	//	Camp->AddMapObject(8, 6, EMapObject::Item, EItemType::ItemRoller);
	//	Camp->AddMapObject(6, 8, EMapObject::Item, EItemType::ItemFluid);
	//}
	////Camp �� Object �״���Ϸ��� �Ʒ��ڵ��
	//{
	//	Camp->AddObjectInit();
	//}


	//Item - Village
	{
		Village->AddMapObject(0, 0, EMapObject::Item, EItemType::ItemBubble);
		Village->AddMapObject(1, 0, EMapObject::Item, EItemType::ItemNiddle);
		Village->AddMapObject(2, 0, EMapObject::Item, EItemType::ItemTurtle);
		Village->AddMapObject(2, 1, EMapObject::Item, EItemType::ItemOwl);
		Village->AddMapObject(2, 2, EMapObject::Item, EItemType::ItemShoes);
		Village->AddMapObject(8, 6, EMapObject::Item, EItemType::ItemRoller);
		Village->AddMapObject(6, 8, EMapObject::Item, EItemType::ItemFluid);
	}
	//Camp �� Object �״���Ϸ��� �Ʒ��ڵ��
	{
		Village->AddObjectInit();
	}



}

