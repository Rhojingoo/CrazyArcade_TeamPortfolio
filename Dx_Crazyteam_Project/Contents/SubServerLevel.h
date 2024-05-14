#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/EngineThread.h>
#include <EngineBase/EngineNetHeader.h>
#include <EngineCore/EngineNetWindow.h>
#include <EngineBase/EngineDispatcher.h>

// ���� :
class UEngineNetWindow;
class AServerPlayer;

class ASubServerLevel : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	ASubServerLevel(); // ����Ʈ ������
	~ASubServerLevel(); // ����Ʈ �Ҹ���

	// delete Function
	ASubServerLevel(const ASubServerLevel& _Other) = delete; // ����Ʈ ���� ������
	ASubServerLevel(ASubServerLevel&& _Other) noexcept = delete; 
	ASubServerLevel& operator=(const ASubServerLevel& _Other) = delete; // ����Ʈ ���� ������
	ASubServerLevel& operator=(ASubServerLevel&& _Other) noexcept = delete;

	void ServerPacketInit(UEngineDispatcher& Dis);
	void ClientPacketInit(UEngineDispatcher& Dis);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _DeltaTime) override;
	void LevelEnd(ULevel* _DeltaTime) override;
	
private:
	std::shared_ptr<UEngineNetWindow> subNetWindow;
	std::shared_ptr<AServerPlayer> MainPlayer = nullptr;
};

