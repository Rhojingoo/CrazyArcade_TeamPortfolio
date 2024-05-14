#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/EngineThread.h>
#include <EngineBase/EngineNetHeader.h>
#include <EngineCore/EngineNetWindow.h>
#include <EngineBase/EngineDispatcher.h>

class AIntro;
class APlayLobby;
class AMapUI;
class AUitestMonde : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	AUitestMonde(); // ����Ʈ ������
	~AUitestMonde(); // ����Ʈ �Ҹ���

	// delete Function
	AUitestMonde(const AUitestMonde& _Other) = delete; // ����Ʈ ���� ������
	AUitestMonde(AUitestMonde&& _Other) noexcept = delete; 
	AUitestMonde& operator=(const AUitestMonde& _Other) = delete; // ����Ʈ ���� ������
	AUitestMonde& operator=(AUitestMonde&& _Other) noexcept = delete;

	std::shared_ptr<APlayLobby> GetPlayLobby()
	{
		return PlayLobby;
	}

	std::shared_ptr<AMapUI> GetMapUI()
	{
		return MapUI;
	}



protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel);
	void LevelEnd(ULevel* _NextLevel);

private:
	std::shared_ptr<APlayLobby> PlayLobby = nullptr;
	std::shared_ptr<AMapUI> MapUI = nullptr;
	std::shared_ptr<AIntro> Intro = nullptr;
};

