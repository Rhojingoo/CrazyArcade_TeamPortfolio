#include "PreCompile.h"
#include "SubServerLevel.h"

#include <EngineCore/Image.h>
#include <EngineCore/Camera.h>
#include <EngineBase/EngineSerializer.h>
#include <EngineCore/BlurEffect.h>
#include <EngineCore/EngineEditorGUI.h>
#include <EnginePlatform/EngineInput.h>

#include "ServerPlayer.h"
#include "Game_Core.h"
#include "Packets.h"
#include "Player.h"
#include "OtherPlayer.h"
#include "Village.h"
#include "Camp.h"
#include "WaterBomb.h"
#include "OtherBomb.h"
#include "OtherUI.h"
#include "OtherWaterCourse.h"
#include "CAGameMode.h"
#include "BaseMap.h"
#include "MapUI.h"
#include <EngineBase/NetObject.h>

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
	//Camera->SetActorLocation(FVector(90.0f, 0.0f, -400.0f));
	Camera->SetActorLocation(FVector(80.0f, 1.0f, -1000.0f));

	//Village = GetWorld()->SpawnActor<AVillage>("Village");
	//SetCurMap(Village);

	std::shared_ptr<ACamp> Camp = GetWorld()->SpawnActor<ACamp>("Camp");
	SetCurMap(Camp);
	Camp->SetCurGameMode(this);


	MapUI = GetWorld()->SpawnActor<AMapUI>("MapUI");
	MapUI->SetCurGameMode(this);
	SetUI(MapUI);
	FVector Pos = MapUI->GetActorLocation();
	Pos.Z = 100.f;
	MapUI->SetActorLocation(Pos);


	MainPlayer = GetWorld()->SpawnActor<APlayer>("Player");
	MainPlayer->SetCurGameMode(this);
	SetMainPlayer(MainPlayer);



}

void ASubServerLevel::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UNetObject::AllNetObject;
	int a = 0;
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
				MainPlayer->SetObjectToken(_Token->GetSessionToken() * 1000);
				MainPlayer->WaterBomb_Token = _Token->GetSessionToken() * 1000 + 1;
				MainPlayer->WaterCourse_Token = _Token->GetSessionToken() * 10000 + 1;
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
			});
	});

	Dis.AddHandler<UWaterBombUpdatePacket>([=](std::shared_ptr<UWaterBombUpdatePacket> _Packet)
	{
		// �ٸ� ��������� �� ������Ʈ�� ���ؼ� �˸���
		UGame_Core::Net->Send(_Packet);

		GetWorld()->PushFunction([=]()
			{
				AOtherBomb* Bomb = UNetObject::GetNetObject<AOtherBomb>(_Packet->GetObjectToken());
				if (nullptr == Bomb)
				{
					Bomb = this->GetWorld()->SpawnActor<AOtherBomb>("Bomb", 0).get();
					Bomb->SetObjectToken(_Packet->GetObjectToken());
					Bomb->SetCurGameMode(this);
					Bomb->CreateWaterBomb();
				}
				Bomb->PushProtocol(_Packet);
			});
	});

	Dis.AddHandler<UWaterCourseUpdatePacket>([=](std::shared_ptr<UWaterCourseUpdatePacket> _Packet)
		{
			// �ٸ� ��������� �� ������Ʈ�� ���ؼ� �˸���
			UGame_Core::Net->Send(_Packet);

			GetWorld()->PushFunction([=]()
				{
					AOtherWaterCourse* Bomb = UNetObject::GetNetObject<AOtherWaterCourse>(_Packet->GetObjectToken());
					if (nullptr == Bomb)
					{
						Bomb = this->GetWorld()->SpawnActor<AOtherWaterCourse>("WATER", 0).get();
						Bomb->SetObjectToken(_Packet->GetObjectToken());
						Bomb->SetCurGameMode(this);
						Bomb->CreateWaterCenter();					
					}
					Bomb->PushProtocol(_Packet);
				});
		});	

	//Dis.AddHandler<UUIUpdatePacket>([=](std::shared_ptr<UUIUpdatePacket> _Packet)
	//	{
	//		// �ٸ� ��������� �� ������Ʈ�� ���ؼ� �˸���
	//		UGame_Core::Net->Send(_Packet);

	//		GetWorld()->PushFunction([=]()
	//			{
	//				AOtherUI* Time = UNetObject::GetNetObject<AOtherUI>(_Packet->GetObjectToken());
	//				if (nullptr == Time)
	//				{
	//					Time = this->GetWorld()->SpawnActor<AOtherUI>("UI", 0).get();
	//					Time->SetObjectToken(_Packet->GetObjectToken());
	//				}
	//				Time->PushProtocol(_Packet);
	//			});
	//	});

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
		});
	});

	Dis.AddHandler<UWaterBombUpdatePacket>([=](std::shared_ptr<UWaterBombUpdatePacket> _Packet)
	{
		// �ٸ� ��������� �� ������Ʈ�� ���ؼ� �˸���
		GetWorld()->PushFunction([=]()
		{
			int Test = _Packet->GetObjectToken();

			AOtherBomb* Bomb = UNetObject::GetNetObject<AOtherBomb>(_Packet->GetObjectToken());
			if (nullptr == Bomb)
			{
				Bomb = this->GetWorld()->SpawnActor<AOtherBomb>("Bomb", 0).get();
				Bomb->SetObjectToken(_Packet->GetObjectToken());
				Bomb->SetCurGameMode(this);
				Bomb->CreateWaterBomb();
			}
			Bomb->PushProtocol(_Packet);

		});
	});

	Dis.AddHandler<UWaterCourseUpdatePacket>([=](std::shared_ptr<UWaterCourseUpdatePacket> _Packet)
		{
			// �ٸ� ��������� �� ������Ʈ�� ���ؼ� �˸���
			GetWorld()->PushFunction([=]()
				{
					int Test = _Packet->GetObjectToken();

					AOtherWaterCourse* Bomb = UNetObject::GetNetObject<AOtherWaterCourse>(_Packet->GetObjectToken());
					if (nullptr == Bomb)
					{
						Bomb = this->GetWorld()->SpawnActor<AOtherWaterCourse>("WATER", 0).get();
						Bomb->SetObjectToken(_Packet->GetObjectToken());
						Bomb->SetCurGameMode(this);
						Bomb->CreateWaterCenter();
					}
					Bomb->PushProtocol(_Packet);
				});
		});


	//Dis.AddHandler<UUIUpdatePacket>([=](std::shared_ptr<UUIUpdatePacket> _Packet)
	//	{
	//		// �ٸ� ��������� �� ������Ʈ�� ���ؼ� �˸���
	//		GetWorld()->PushFunction([=]()
	//			{
	//				int Test = _Packet->GetObjectToken();

	//				AOtherUI* Time = UNetObject::GetNetObject<AOtherUI>(_Packet->GetObjectToken());
	//				if (nullptr == Time)
	//				{
	//					Time = this->GetWorld()->SpawnActor<AOtherUI>("UI", 0).get();
	//					Time->SetObjectToken(_Packet->GetObjectToken());
	//				}
	//				Time->PushProtocol(_Packet);

	//			});
	//	});	
}

void ASubServerLevel::LevelEnd(ULevel* _DeltaTime)
{
	subNetWindow->Off();
}
