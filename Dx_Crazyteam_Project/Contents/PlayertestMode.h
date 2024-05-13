#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/EngineThread.h>
#include <EngineBase/EngineNetHeader.h>
#include <EngineCore/EngineNetWindow.h>
#include <EngineBase/EngineDispatcher.h>


#include "Village.h"
#include "Player.h"

class APlayerTestMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	APlayerTestMode(); // ����Ʈ ������
	~APlayerTestMode(); // ����Ʈ �Ҹ���

	// delete Function
	APlayerTestMode(const APlayerTestMode& _Other) = delete; // ����Ʈ ���� ������
	APlayerTestMode(APlayerTestMode&& _Other) noexcept = delete; 
	APlayerTestMode& operator=(const APlayerTestMode& _Other) = delete; // ����Ʈ ���� ������
	APlayerTestMode& operator=(APlayerTestMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel);
	void LevelEnd(ULevel* _NextLevel);
private:
	std::shared_ptr<AVillage> Village = nullptr;
	std::shared_ptr<APlayer> Player1 = nullptr;
};

