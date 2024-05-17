#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "MapUI.h"

// ���� :
class USpriteRenderer;
class OtherUI : public AMapUI
{
public:
	// constrcuter destructer
	OtherUI();
	~OtherUI();

	// delete Function
	OtherUI(const OtherUI& _Other) = delete;
	OtherUI(OtherUI&& _Other) noexcept = delete;
	OtherUI& operator=(const OtherUI& _Other) = delete;
	OtherUI& operator=(OtherUI&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	int OherBomb_Second = 0;
	int OherBomb_MilliSecond = 0;
};

