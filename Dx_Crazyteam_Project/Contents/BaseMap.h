#pragma once
#include "CAObject.h"

// ���� :
class UEngineTexture;
class UDefaultSceneComponent;
class AMapObject;
class ABaseMap : public ACAObject
{
	GENERATED_BODY(ACAObject)
public:
	// constructor destructor
	ABaseMap();
	~ABaseMap();

	// delete Function
	ABaseMap(const ABaseMap& _Other) = delete;
	ABaseMap(ABaseMap&& _Other) noexcept = delete;
	ABaseMap& operator=(const ABaseMap& _Other) = delete;
	ABaseMap& operator=(ABaseMap&& _Other) noexcept = delete;

	bool IsMove(FVector _PlayerPos);
	void AddMapObject(int _Y, int _X, EMapObject _MapObjectType);
	void SpawnWaterBomb(FVector _SpawnPos);
	POINT PlayerPosToPoint(FVector _PlayerPos);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	USpriteRenderer* BackMap = nullptr;
	UDefaultSceneComponent* Root = nullptr;

	std::vector<std::vector<std::shared_ptr<AMapObject>>> MapStatus;
private:

	void GetWaterWavePoint();
};

