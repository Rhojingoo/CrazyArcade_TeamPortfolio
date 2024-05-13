#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/EngineThread.h>
#include <EngineBase/EngineNetHeader.h>
#include <EngineCore/EngineNetWindow.h>
#include <EngineBase/EngineDispatcher.h>

#include "Player.h"

class APlayertestMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	APlayertestMode(); // ����Ʈ ������
	~APlayertestMode(); // ����Ʈ �Ҹ���

	// delete Function
	APlayertestMode(const APlayertestMode& _Other) = delete; // ����Ʈ ���� ������
	APlayertestMode(APlayertestMode&& _Other) noexcept = delete; 
	APlayertestMode& operator=(const APlayertestMode& _Other) = delete; // ����Ʈ ���� ������
	APlayertestMode& operator=(APlayertestMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel);
	void LevelEnd(ULevel* _NextLevel);
private:
	std::shared_ptr<APlayer> Player1 = nullptr;
};

