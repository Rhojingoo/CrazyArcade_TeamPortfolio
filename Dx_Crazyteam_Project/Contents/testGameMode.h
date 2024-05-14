#pragma once
#include "CAGameMode.h"

class UMapDebugGUI;
class ATestGameMode : public ACAGameMode
{
	GENERATED_BODY(ACAGameMode)
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
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;
private:
	std::shared_ptr<UMapDebugGUI> MapDebugWindow;
	std::shared_ptr<APlayer> Player1 = nullptr;
};

