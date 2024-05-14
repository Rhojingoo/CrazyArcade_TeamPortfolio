#pragma once
#include "CAObject.h"

// ���� :
class UDefaultSceneComponent;
class AMapObject : public ACAObject
{
	GENERATED_BODY(ACAObject)
public:
	// constructor destructor
	AMapObject();
	~AMapObject();

	// delete Function
	AMapObject(const AMapObject& _Other) = delete;
	AMapObject(AMapObject&& _Other) noexcept = delete;
	AMapObject& operator=(const AMapObject& _Other) = delete;
	AMapObject& operator=(AMapObject&& _Other) noexcept = delete;

	EMapObjectType GetType()
	{
		return Type;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UDefaultSceneComponent* Root = nullptr;

	EMapObjectType Type = EMapObjectType::None;

	std::function<void()> PlayerInteract;
	std::function<void()> WaterInteract;
	
private:

};

