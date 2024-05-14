#include "PreCompile.h"
#include "SubServerLevel.h"

#include <EngineCore/Image.h>
#include <EngineCore/Camera.h>
#include <EngineBase/EngineSerializer.h>
#include <EngineCore/BlurEffect.h>
#include <EngineCore/EngineEditorGUI.h>

#include "ServerPlayer.h"
#include "Game_Core.h"
#include "Packets.h"
#include "Player.h"
#include "OtherPlayer.h"
#include "Village.h"

ASubServerLevel::ASubServerLevel()
{
	if (nullptr != UGame_Core::Net)
	{
		UGame_Core::Net->End();
		UGame_Core::Net = nullptr;
	}
}

ASubServerLevel::~ASubServerLevel()
{
}

void ASubServerLevel::BeginPlay()
{
	Super::BeginPlay();
	// TestThread.Start();
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	Village = GetWorld()->SpawnActor<AVillage>("Village");
	SetCurMap(Village);

	MainPlayer = GetWorld()->SpawnActor<APlayer>("Player");
	MainPlayer->SetCurGameMode(this);
	SetMainPlayer(MainPlayer);
}

void ASubServerLevel::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ASubServerLevel::LevelStart(ULevel* _DeltaTime)
{
	if (nullptr == subNetWindow)
	{
		subNetWindow = UEngineEditorGUI::CreateEditorWindow<UEngineNetWindow>("subNetWindow");

		subNetWindow->SetServerOpenFunction([&]()
		{
			UGame_Core::Net = std::make_shared<UEngineServer>();
			UGame_Core::Net->ServerOpen(30000, 512);

			// ���⿡�� ���� �÷��̾����� ��ȣ�� �ϳ� �̴ٰϴ�.

			MainPlayer->SetObjectToken(UNetObject::GetNewObjectToken());

			ServerPacketInit(UGame_Core::Net->Dispatcher);
		});

		subNetWindow->SetClientConnectFunction([&](std::string IP, short PORT)
		{
			UGame_Core::Net = std::make_shared<UEngineClient>();
			UGame_Core::Net->Connect(IP, PORT);

			UGame_Core::Net->SetTokenPacketFunction([=](USessionTokenPacket* _Token)
			{
				MainPlayer->SetObjectToken(_Token->GetObjectToken());

			});

			// � ��Ű�� ������ ��� ó���Ұ����� ���ϴ� �� �ؾ��Ѵ�.
			ClientPacketInit(UGame_Core::Net->Dispatcher);
		});
	}
	subNetWindow->On();
}

void ASubServerLevel::ServerPacketInit(UEngineDispatcher& Dis)
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
			}
			OtherPlayer->PushProtocol(_Packet);
			//OtherPlayer->SetActorLocation(_Packet->Pos);
		});


	});
}

void ASubServerLevel::ClientPacketInit(UEngineDispatcher& Dis)
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
			}
			OtherPlayer->PushProtocol(_Packet);
			//OtherPlayer->SetActorLocation(_Packet->Pos);
		});
	});
}

void ASubServerLevel::LevelEnd(ULevel* _DeltaTime)
{
	subNetWindow->Off();
}
