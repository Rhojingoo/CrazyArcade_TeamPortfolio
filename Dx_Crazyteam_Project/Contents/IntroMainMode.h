#pragma once
#include <EngineCore/GameMode.h>

class AIntro;
class ATitleMenu;
class UEngineSoundPlayer;

class AIntroMainMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	AIntroMainMode(); // ����Ʈ ������
	~AIntroMainMode(); // ����Ʈ �Ҹ���

	// delete Function
	AIntroMainMode(const AIntroMainMode& _Other) = delete; // ����Ʈ ���� ������
	AIntroMainMode(AIntroMainMode&& _Other) noexcept = delete; 
	AIntroMainMode& operator=(const AIntroMainMode& _Other) = delete; // ����Ʈ ���� ������
	AIntroMainMode& operator=(AIntroMainMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel);
	void LevelStart(ULevel* _PrevLevel);
private:
	UEngineSoundPlayer BGM;
	std::shared_ptr<AIntro> Intro = nullptr;
};

