#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/EngineThread.h>
#include <EngineBase/EngineNetHeader.h>
#include <EngineCore/EngineNetWindow.h>
#include <EngineBase/EngineDispatcher.h>
#include "CAGameMode.h"

// ���� :
class AServerTestPlayer;

class AMapUI;
class APlayer;
class UEngineNetWindow;
class AServerPlayer;
class AVillage;
class ASubServerLevel : public ACAGameMode
{
	GENERATED_BODY(ACAGameMode)
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
	std::shared_ptr<AVillage> Village = nullptr;
	//std::shared_ptr<APlayer> MainPlayer = nullptr;
	std::shared_ptr<AServerTestPlayer> MainPlayer = nullptr;
	std::shared_ptr<AMapUI> MapUI = nullptr;
};

