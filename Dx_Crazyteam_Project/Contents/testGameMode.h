#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/EngineThread.h>
#include <EngineBase/EngineNetHeader.h>
#include <EngineCore/EngineNetWindow.h>
#include <EngineBase/EngineDispatcher.h>

class AtestGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	AtestGameMode(); // ����Ʈ ������
	~AtestGameMode(); // ����Ʈ �Ҹ���

	// delete Function
	AtestGameMode(const AtestGameMode& _Other) = delete; // ����Ʈ ���� ������
	AtestGameMode(AtestGameMode&& _Other) noexcept = delete; 
	AtestGameMode& operator=(const AtestGameMode& _Other) = delete; // ����Ʈ ���� ������
	AtestGameMode& operator=(AtestGameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel);
	void LevelEnd(ULevel* _NextLevel);
private:
};

