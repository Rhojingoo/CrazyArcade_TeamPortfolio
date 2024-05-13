#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/EngineThread.h>
#include <EngineBase/EngineNetHeader.h>
#include <EngineCore/EngineNetWindow.h>
#include <EngineBase/EngineDispatcher.h>

#include "Player.h"

class UMapDebugGUI;
class ATestGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	ATestGameMode(); // ����Ʈ ������
	~ATestGameMode(); // ����Ʈ �Ҹ���

	// delete Function
	ATestGameMode(const ATestGameMode& _Other) = delete; // ����Ʈ ���� ������
	ATestGameMode(ATestGameMode&& _Other) noexcept = delete; 
	ATestGameMode& operator=(const ATestGameMode& _Other) = delete; // ����Ʈ ���� ������
	ATestGameMode& operator=(ATestGameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel);
	void LevelEnd(ULevel* _NextLevel);
private:
	std::shared_ptr<UMapDebugGUI> MapDebugWindow;
	std::shared_ptr<APlayer> Player1 = nullptr;
};

