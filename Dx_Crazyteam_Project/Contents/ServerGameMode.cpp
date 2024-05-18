#include "PreCompile.h"
#include "ServerGameMode.h"
#include <EngineBase/EngineProtocol.h>

#include <EngineCore/Image.h>
#include <EngineCore/Camera.h>
#include <EngineBase/EngineSerializer.h>
#include <EngineCore/BlurEffect.h>
#include <EngineCore/EngineEditorGUI.h>


#include "ServerTestOtherPlayer.h"
#include "ServerTestPlayer.h"
#include "Game_Core.h"
#include "Packets.h"
#include "OtherPlayer.h"
#include "Village.h"
#include "Camp.h"
#include "ItemBubble.h"
#include "MapObject.h"

#include "TitleMenu.h"
#include "PlayLobby.h"

#include "TestLobbyMode.h"


AServerGameMode::AServerGameMode() 
{
}

AServerGameMode::~AServerGameMode() 
{
	if (nullptr != UGame_Core::Net)
	{
		UGame_Core::Net->End();
		UGame_Core::Net = nullptr;
	}
}

void AServerGameMode::BeginPlay() 
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));


	Camp = GetWorld()->SpawnActor<ACamp>("Camp");
	Camp->SetCurGameMode(this);
	SetCurMap(Camp);

	std::shared_ptr<APlayer> Player1 = GetWorld()->SpawnActor<AServerTestPlayer>("Player1", 0);
	Player1->SetCurGameMode(this);
	SetMainPlayer(Player1);

}

void AServerGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UNetObject::AllNetObject;
}

void AServerGameMode::LevelStart(ULevel* _PrevLevel)
{

	if (nullptr == NetWindow)
	{
		NetWindow = UEngineEditorGUI::CreateEditorWindow<UEngineNetWindow>("NetWindow");

		NetWindow->SetServerOpenFunction([&]()
			{
				UGame_Core::Net = std::make_shared<UEngineServer>();
				UGame_Core::Net->ServerOpen(30000, 512);

				GetPlayer()->SetObjectToken(UNetObject::GetNewObjectToken());
				

				ServerPacketInit(UGame_Core::Net->Dispatcher);
			});

		NetWindow->SetClientConnectFunction([&](std::string IP, short PORT)
			{
				UGame_Core::Net = std::make_shared<UEngineClient>();
				UGame_Core::Net->Connect(IP, PORT);

				UGame_Core::Net->SetTokenPacketFunction([=](USessionTokenPacket* _Token)
					{
						GetPlayer()->SetObjectToken(_Token->GetObjectToken());
					});

				// � ��Ű�� ������ ��� ó���Ұ����� ���ϴ� �� �ؾ��Ѵ�.
				ClientPacketInit(UGame_Core::Net->Dispatcher);
			});
	}
	NetWindow->On();
}

void AServerGameMode::ServerPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
		{
			// �ٸ� ��������� �� ������Ʈ�� ���ؼ� �˸���
		    UGame_Core::Net->Send(_Packet);

			GetWorld()->PushFunction([=]()
				{
					switch (_Packet->ObjectType)
					{	
					case static_cast<int>(EObjectType::Player):
					{
						AOtherPlayer* OtherPlayer = UNetObject::GetNetObject<AOtherPlayer>(_Packet->GetObjectToken());
						if (nullptr == OtherPlayer)
						{
							OtherPlayer = this->GetWorld()->SpawnActor<AOtherPlayer>("OtherPlayer", 0).get();
							OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
						}
						OtherPlayer->PushProtocol(_Packet);
						break;
					}
					case static_cast<int>(EObjectType::Item):
					{
						if (true == _Packet->IsDestroy)
						{
							break;
						}

						// UActorUpdatePacket���� ������ ������ ������� �� �ڽſ��Ե� Item�� ���̴� ��� ����
						AMapObject* OtherItem = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());
						if (nullptr == OtherItem)
						{
							ABaseMap* CurMap = GetCurMap().get();
							OtherItem = CurMap->AddMapObject(6, 1, EMapObject::Item, EItemType::ItemBubble).get();
							OtherItem->SetObjectToken(_Packet->GetObjectToken());
						}
						break;
					}
					default:
						break;
					}
				});
		});
}

void AServerGameMode::ClientPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
		{
			GetWorld()->PushFunction([=]()
				{
					switch (_Packet->ObjectType)
					{
					case static_cast<int>(EObjectType::Player):
					{
						AOtherPlayer* OtherPlayer = UNetObject::GetNetObject<AOtherPlayer>(_Packet->GetObjectToken());
						if (nullptr == OtherPlayer)
						{
							OtherPlayer = this->GetWorld()->SpawnActor<AOtherPlayer>("OtherPlayer", 0).get();
							OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
						}
						OtherPlayer->PushProtocol(_Packet);
						break;
					}
					case static_cast<int>(EObjectType::Item):
					{
						if (true == _Packet->IsDestroy)
						{
							//GetCurMap()->DestroyMapObject(_Packet->Pos.Y, _Packet->Pos.X);
							break;
						}

						// UActorUpdatePacket���� ������ ������ ������� �� �ڽſ��Ե� Item�� ���̴� ��� ����
						AMapObject* OtherItem = UNetObject::GetNetObject<AMapObject>(_Packet->GetObjectToken());
						if (nullptr == OtherItem)
						{
							ABaseMap* CurMap = GetCurMap().get();
							OtherItem = CurMap->AddMapObject(6, 1, EMapObject::Item, EItemType::ItemBubble).get();
							OtherItem->SetObjectToken(_Packet->GetObjectToken());
						}
						break;
					}
					default:
						break;
					}
				});
		});
}

std::shared_ptr<APlayLobby> AServerGameMode::GetPlayLobby()
{
	return PlayLobby;
}

void AServerGameMode::LevelEnd(ULevel* _NextLevel)
{
	NetWindow->Off();
}

void AServerGameMode::CollectWindowAppear()
{
	NetWindow->On();
}