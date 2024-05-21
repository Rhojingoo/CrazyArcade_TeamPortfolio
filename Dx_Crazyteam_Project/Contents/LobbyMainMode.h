#pragma once
#include <EngineCore/GameMode.h>
class UEngineSoundPlayer;


class APlayLobby;

class ALobbyMainMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	ALobbyMainMode(); // ����Ʈ ������
	~ALobbyMainMode(); // ����Ʈ �Ҹ���

	// delete Function
	ALobbyMainMode(const ALobbyMainMode& _Other) = delete; // ����Ʈ ���� ������
	ALobbyMainMode(ALobbyMainMode&& _Other) noexcept = delete; 
	ALobbyMainMode& operator=(const ALobbyMainMode& _Other) = delete; // ����Ʈ ���� ������
	ALobbyMainMode& operator=(ALobbyMainMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel);
	void LevelStart(ULevel* _PrevLevel);
private:
	UEngineSoundPlayer LobbyBGM;

	std::shared_ptr<APlayLobby> PlayLobby = nullptr;

};

