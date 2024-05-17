#pragma once
#include "Player.h"

// ���� :
class AServerTestPlayer : public APlayer
{
	GENERATED_BODY(APlayer)
public:
	// constrcuter destructer
	AServerTestPlayer();
	~AServerTestPlayer();

	// delete Function
	AServerTestPlayer(const AServerTestPlayer& _Other) = delete;
	AServerTestPlayer(AServerTestPlayer&& _Other) noexcept = delete;
	AServerTestPlayer& operator=(const AServerTestPlayer& _Other) = delete;
	AServerTestPlayer& operator=(AServerTestPlayer&& _Other) noexcept = delete;

protected:

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

