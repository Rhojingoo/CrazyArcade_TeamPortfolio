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
#include "Packets.h"
#include "OtherUI.h"
#include "ServerTestPlayer.h"


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

	ACAGameMode::OtherPlayers.clear();
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

				MainPlayer = GetWorld()->SpawnActor<AServerTestPlayer>("Player1", 0);
				MainPlayer->SetCurGameMode(this);
				SetMainPlayer(MainPlayer);

				FVector InitPos = GetCurMap()->PointToPos(ConstValue::VillageStartPos[UGame_Core::Net->GetSessionToken()]);
				MainPlayer->SetActorLocation(InitPos);

				// ���⿡�� ���� �÷��̾����� ��ȣ�� �ϳ� �̴ٰϴ�.
				MainPlayer->SetObjectToken(UNetObject::GetNewObjectToken());


				// Ÿ�� ������
				MapUI = GetWorld()->SpawnActor<AMapUI>("MapUI");
				MapUI->SetCurGameMode(this);
				MapUI->SetObjectToken(UNetObject::GetNewObjectToken());

				//����ź
				MainPlayer->WaterBomb_Token = UGame_Core::Net->GetSessionToken() * 1000 + 2;
				ServerPacketInit(UGame_Core::Net->Dispatcher);
			};

			MapUI->MapTimeLogic = [=](AMapUI* _Lobby)
				{										
		/*			std::shared_ptr<UUIUpdatePacket> TimeCreate= std::make_shared<UUIUpdatePacket>();
					TimeCreate->SerVerSend = true;
					TimeCreate->Second_Tens = MapUI->GetCreateTime();
					UGame_Core::Net->Send(TimeCreate);*/
				};


	}
	else if (AServerGameMode::NetType == ENetType::Client)
	{
			{
				//UGame_Core::Net = std::make_shared<UEngineClient>();
				//UGame_Core::Net->Connect(IP, PORT);

				//UGame_Core::Net->SetTokenPacketFunction([=](USessionTokenPacket* _Token)
					//{

				MainPlayer = GetWorld()->SpawnActor<AServerTestPlayer>("Player1", 0);
				MainPlayer->SetCurGameMode(this);
				SetMainPlayer(MainPlayer);

				FVector InitPos = GetCurMap()->PointToPos(ConstValue::VillageStartPos[UGame_Core::Net->GetSessionToken()]);
				MainPlayer->SetActorLocation(InitPos);

				MainPlayer->SetObjectToken(UGame_Core::Net->GetSessionToken() * 1000);

				//Ÿ�� ������

				MapUI = GetWorld()->SpawnActor<AMapUI>("MapUI");
				MapUI->SetCurGameMode(this);
				MapUI->SetObjectToken(UGame_Core::Net->GetSessionToken() * 1000 + 1);
	
				//����ź
				MainPlayer->WaterBomb_Token = UGame_Core::Net->GetSessionToken() * 1000 + 2;
					//});
				// � ��Ű�� ������ ��� ó���Ұ����� ���ϴ� �� �ؾ��Ѵ�
				ClientPacketInit(UGame_Core::Net->Dispatcher);
			};

			MapUI->MapTimeLogic = [=](AMapUI* _Lobby)
			{
				std::shared_ptr<UUIUpdatePacket> TimeCreate = std::make_shared<UUIUpdatePacket>();
				TimeCreate->ClientCreate = true;
				int a = UGame_Core::Net->GetSessionToken();
				TimeCreate->SetSessionToken(UGame_Core::Net->GetSessionToken());
				TimeCreate->SetObjectToken(MapUI->GetObjectToken());
				UGame_Core::Net->Send(TimeCreate);	
			};
	}
}

void AMainGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}


void AMainGameMode::ServerPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
	{
		// �ٸ� ��������� �� ������Ʈ�� ���ؼ� �˸���
		UGame_Core::Net->Send(_Packet);

		GetWorld()->PushFunction([=]()
			{
				AOtherPlayer* OtherPlayer = UNetObject::GetNetObject<AOtherPlayer>(_Packet->GetObjectToken());
				if (nullptr == OtherPlayer)
				{
					OtherPlayer = this->GetWorld()->SpawnActor<AOtherPlayer>("OtherPlayer", 0).get();
					OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
					ACAGameMode::OtherPlayers.push_back(OtherPlayer);
				}
				OtherPlayer->PushProtocol(_Packet);
			});
	});

	Dis.AddHandler<UMapObjectUpdatePacket>([=](std::shared_ptr<UMapObjectUpdatePacket> _Packet)
	{
		UGame_Core::Net->Send(_Packet);

		GetWorld()->PushFunction([=]()
			{
				// Other ������Ʈ ������
				if (true == _Packet->IsDestroy)
				{
					AMapObject* OtherItem = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());
					if (nullptr != OtherItem)
					{
						POINT Pos = _Packet->Pos;
						GetCurMap()->DestroyMapObject(Pos.y, Pos.x);
					}
					return;
				}

				// Other ������Ʈ �̵�
				if (true == _Packet->IsMove)
				{
					AMapObject* OtherBlock = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());
					if (nullptr != OtherBlock)
					{
						OtherBlock->SetActorLocation(_Packet->MovePos);
					}
					return;
				}

				// Other ������Ʈ �̵� ����
				if (true == _Packet->IsMoveEnd)
				{
					AMapObject* OtherBlock = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());
					if (nullptr != OtherBlock)
					{
						GetCurMap()->MoveMapObject(OtherBlock->shared_from_this(), _Packet->MoveEndPos.y, _Packet->MoveEndPos.x, _Packet->MoveBeginPos.y, _Packet->MoveBeginPos.x);
					}
					return;
				}

				// ��ǳ�� ���� ������Ʈ ���� ����
				EMapObject ObjType = static_cast<EMapObject>(_Packet->ObjectType);

				switch (ObjType)
				{
				case EMapObject::WaterBomb:
				{
					AMapObject* OtherObject = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());

					if (nullptr == OtherObject)
					{
						ABaseMap* CurMap = GetCurMap().get();
						POINT PosValue = _Packet->Pos;

						OtherObject = CurMap->SpawnWaterBomb(PosValue.x, PosValue.y, _Packet->WaterPower).get();

						OtherObject->SetObjectToken(_Packet->GetObjectToken());
					}
					break;
				}
				default:
					MsgBoxAssert("Server�� �ƴ� ������ MapObject�� �����Ϸ� �߽��ϴ�.");
					return;
				}
			});
	});

	Dis.AddHandler<UUIUpdatePacket>([=](std::shared_ptr<UUIUpdatePacket> _Packet)
	{
		// �ٸ� ��������� �� ������Ʈ�� ���ؼ� �˸���
		//UGame_Core::Net->Send(_Packet);

		GetWorld()->PushFunction([=]()
		{
				int Test = _Packet->GetObjectToken();
				AMapUI* Time = UNetObject::GetNetObject<AMapUI>(_Packet->GetObjectToken());
				if (nullptr == Time)
				{
					int a = 0;
					//Time = this->GetWorld()->SpawnActor<AOtherUI>("UI", 0).get();
					//Time->SetObjectToken(_Packet->GetObjectToken());
				}
				else
				{
					if (_Packet->ClientCreate == true)
					{
						std::shared_ptr<UUIUpdatePacket> TimeCreate = std::make_shared<UUIUpdatePacket>();
						TimeCreate->SerVerSend = true;
						TimeCreate->Time_Second = MapUI->GetCreateTime();
						TimeCreate->SetSessionToken(UGame_Core::Net->GetSessionToken());
						TimeCreate->SetObjectToken(MapUI->GetObjectToken());

						UGame_Core::Net->Send(TimeCreate);
					}
				}//Time->PushProtocol(_Packet);					
		});
	});
}

void AMainGameMode::ClientPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
		{
			GetWorld()->PushFunction([=]()
				{
					AOtherPlayer* OtherPlayer = UNetObject::GetNetObject<AOtherPlayer>(_Packet->GetObjectToken());
					if (nullptr == OtherPlayer)
					{
						OtherPlayer = this->GetWorld()->SpawnActor<AOtherPlayer>("OtherPlayer", 0).get();
						OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
						ACAGameMode::OtherPlayers.push_back(OtherPlayer);
					}
					OtherPlayer->PushProtocol(_Packet);
				});

	});

	Dis.AddHandler<UMapObjectUpdatePacket>([=](std::shared_ptr<UMapObjectUpdatePacket> _Packet)
		{
			GetWorld()->PushFunction([=]()
				{
					// Other ������Ʈ �Ҹ� ����
					if (true == _Packet->IsDestroy)
					{
						AMapObject* OtherItem = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());
						if (nullptr != OtherItem)
						{
							POINT Pos = _Packet->Pos;
							GetCurMap()->DestroyMapObject(Pos.y, Pos.x);
						}
						return;
					}

					// Other ������Ʈ �̵�
					if (true == _Packet->IsMove)
					{
						AMapObject* OtherBlock = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());
						if (nullptr != OtherBlock)
						{
							OtherBlock->SetActorLocation(_Packet->MovePos);
						}
						return;
					}

					// Other ������Ʈ �̵� ����
					if (true == _Packet->IsMoveEnd)
					{
						AMapObject* OtherBlock = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());
						if (nullptr != OtherBlock)
						{
							GetCurMap()->MoveMapObject(OtherBlock->shared_from_this(), _Packet->MoveEndPos.y, _Packet->MoveEndPos.x, _Packet->MoveBeginPos.y, _Packet->MoveBeginPos.x);
						}
						return;
					}

					// Other ������Ʈ ���� ����
					EMapObject ObjType = static_cast<EMapObject>(_Packet->ObjectType);

					switch (ObjType)
					{
					case EMapObject::WaterBomb:
					{
						AMapObject* OtherObject = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());

						if (nullptr == OtherObject)
						{
							ABaseMap* CurMap = GetCurMap().get();
							POINT PosValue = _Packet->Pos;

							OtherObject = CurMap->SpawnWaterBomb(PosValue.x, PosValue.y, _Packet->WaterPower).get();

							OtherObject->SetObjectToken(_Packet->GetObjectToken());
						}
						break;
					}
					case EMapObject::TownBush:
					case EMapObject::DummyBlock:
					case EMapObject::NormalBlock:
					case EMapObject::CampBlock1:
					case EMapObject::CampBlock2:
					case EMapObject::CampBlock3:
					case EMapObject::CampBlock4:
					case EMapObject::CampMoveBlock1:
					case EMapObject::CampMoveBlock2:
					case EMapObject::CampHPBlock:
					case EMapObject::VillageBlock1:
					case EMapObject::VillageBlock2:
					case EMapObject::VillageMoveBlock:
					case EMapObject::VillageTree:
					case EMapObject::VillageBlueHouse:
					case EMapObject::VillageRedHouse:
					case EMapObject::VillageYellowHouse:
					{
						AMapObject* OtherObject = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());

						if (nullptr == OtherObject)
						{
							ABaseMap* CurMap = GetCurMap().get();
							POINT PosValue = _Packet->Pos;

							OtherObject = CurMap->AddMapObject(PosValue.x, PosValue.y, ObjType).get();

							EItemType ItemType = static_cast<EItemType>(_Packet->ItemType);

							if (EItemType::None != ItemType)
							{
								OtherObject->SetPossessItem(ItemType);
							}

							OtherObject->SetObjectToken(_Packet->GetObjectToken());
						}
						break;
					}
					case EMapObject::Item:
					{
						EItemType ItemType = static_cast<EItemType>(_Packet->ItemType);

						if (EItemType::None == ItemType)
						{
							MsgBoxAssert("������ Ÿ���� �������� �ʾҽ��ϴ�. �������ּ���.");
							return;
						}

						// UActorUpdatePacket���� ������ ������ ������� �� �ڽſ��Ե� Item�� ���̴� ��� ����
						AMapObject* OtherItem = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());

						if (nullptr == OtherItem)
						{
							ABaseMap* CurMap = GetCurMap().get();
							POINT PosValue = _Packet->Pos;

							switch (ItemType)
							{
							case EItemType::ItemBubble:
							case EItemType::ItemFluid:
							case EItemType::ItemRoller:
							case EItemType::ItemOwl:
							case EItemType::ItemTurtle:
							case EItemType::ItemNiddle:
							case EItemType::ItemShoes:
								OtherItem = CurMap->AddMapObject(PosValue.x, PosValue.y, EMapObject::Item, ItemType).get();
								break;
							default:
								MsgBoxAssert("�������� ���� Ÿ���Դϴ�. ������ Ÿ���� Ȯ���ϼ���.");
								return;
							}
							OtherItem->SetObjectToken(_Packet->GetObjectToken());
						}
						break;
					}
					default:
						MsgBoxAssert("Type�� DefaultŸ���̰ų� �������� ���� Ÿ���Դϴ�.");
						return;
					}
				});
		});

	Dis.AddHandler<UUIUpdatePacket>([=](std::shared_ptr<UUIUpdatePacket> _Packet)
	{
		// �ٸ� ��������� �� ������Ʈ�� ���ؼ� �˸���
		GetWorld()->PushFunction([=]()
		{
				int Test = _Packet->GetObjectToken();
				AMapUI* Time = UNetObject::GetNetObject<AMapUI>(_Packet->GetObjectToken());
				if (nullptr == Time)
				{
					int a = 0;
				}
				else
				{
					if (_Packet->ClientCreate == true)
					{			
						Time->ServerGetTime(_Packet->Time_Second);	
					}
				}
				Time->PushProtocol(_Packet);
		});
	});
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


	//MainPlayer = GetWorld()->SpawnActor<APlayer>("Player1", 0);
	//MainPlayer->SetCurGameMode(this);
	//SetMainPlayer(MainPlayer);


	{//UI

		//MapUI = GetWorld()->SpawnActor<AMapUI>("MapUI");
		//MapUI->SetCurGameMode(this);
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


	////Item - Village
	//{
	//	Village->AddMapObject(0, 0, EMapObject::Item, EItemType::ItemBubble);
	//	Village->AddMapObject(1, 0, EMapObject::Item, EItemType::ItemNiddle);
	//	Village->AddMapObject(2, 0, EMapObject::Item, EItemType::ItemTurtle);
	//	Village->AddMapObject(2, 1, EMapObject::Item, EItemType::ItemOwl);
	//	Village->AddMapObject(2, 2, EMapObject::Item, EItemType::ItemShoes);
	//	Village->AddMapObject(8, 6, EMapObject::Item, EItemType::ItemRoller);
	//	Village->AddMapObject(6, 8, EMapObject::Item, EItemType::ItemFluid);
	//}
	////Camp �� Object �״���Ϸ��� �Ʒ��ڵ��
	//{
	//	Village->AddObjectInit();
	//}



}