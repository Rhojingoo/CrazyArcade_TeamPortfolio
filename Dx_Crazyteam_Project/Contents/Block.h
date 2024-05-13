#pragma once
#include "MapSpriteObject.h"

// ���� :
class ABlock : public AMapSpriteObject
{
	GENERATED_BODY(AMapSpriteObject)
public:
	// constructor destructor
	ABlock();
	~ABlock();

	// delete Function
	ABlock(const ABlock& _Other) = delete;
	ABlock(ABlock&& _Other) noexcept = delete;
	ABlock& operator=(const ABlock& _Other) = delete;
	ABlock& operator=(ABlock&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

