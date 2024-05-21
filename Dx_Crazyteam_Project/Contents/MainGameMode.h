#pragma once
#include "CAGameMode.h"
#include <EngineBase/EngineThread.h>
#include <EngineBase/EngineNetHeader.h>
#include <EngineCore/EngineNetWindow.h>
#include <EngineBase/EngineDispatcher.h>


class APlayer;
class AVillage;
class ACamp;
class UTextWidget;
class AMapUI;

class AMainGameMode : public ACAGameMode
{
	GENERATED_BODY(ACAGameMode)
public:
	// constrcuter destructer
	AMainGameMode(); // ����Ʈ ������
	~AMainGameMode(); // ����Ʈ �Ҹ���

	// delete Function
	AMainGameMode(const AMainGameMode& _Other) = delete; // ����Ʈ ���� ������
	AMainGameMode(AMainGameMode&& _Other) noexcept = delete; 
	AMainGameMode& operator=(const AMainGameMode& _Other) = delete; // ����Ʈ ���� ������
	AMainGameMode& operator=(AMainGameMode&& _Other) noexcept = delete;

	std::shared_ptr<APlayer> GetPlayer()
	{
		return Player1;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel);
	void LevelEnd(ULevel* _NextLevel);

	void GameModeActorInit();
private:
	UTextWidget* ShowText = nullptr;
	std::shared_ptr<AVillage> Village = nullptr;
	std::shared_ptr<APlayer> Player1 = nullptr;

};

