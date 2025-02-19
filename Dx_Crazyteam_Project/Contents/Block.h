#pragma once
#include "MapObject.h"

// 설명 :
class UStateManager;
class ABlock : public AMapObject
{
	GENERATED_BODY(AMapObject)
public:
	// constructor destructor
	ABlock();
	~ABlock();

	// delete Function
	ABlock(const ABlock& _Other) = delete;
	ABlock(ABlock&& _Other) noexcept = delete;
	ABlock& operator=(const ABlock& _Other) = delete;
	ABlock& operator=(ABlock&& _Other) noexcept = delete;

	UStateManager State;

	void SetIsBreak(bool _IsBreak)
	{
		IsBreak = _IsBreak;
	}

	bool GetIsBreak() const
	{
		return IsBreak;
	}

	void SetIsPush(bool _IsPush)
	{
		IsPush = _IsPush;
	}

	bool GetIsPush() const
	{
		return IsPush;
	}

	

	void MinusHP()
	{
		--Hp;
	}

	int GetHp() const
	{
		return Hp;
	}

	void SetHp(int _Hp)
	{
		Hp = _Hp;
	}


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateInit();
	void CreateAnimation();

	void NoneBegin();
	void NoneTick(float _DeltaTime);

	void IdleBegin();
	void IdleTick(float _DeltaTime);
	void IdleExit();

	void BreakBegin();
	void BreakTick(float _DeltaTime);
	void BreakExit();

	void PushBegin();
	void PushTick(float _DeltaTime);
	void PushExit();

	void EndBegin();
	void EndTick(float _DeltaTime);
	void EndExit();

private:
	void BushCheck();

	//break 관련 변수
	bool IsBreak = false;
	float BreakBlockTime = 0.5f;
	float BreakAccTime = 0.f;
	bool BlinkOn = false;
	float BlinkTime = 0.05f;
	float AccBlinkTime = 0.f;
	int Hp = 1;

	//push 관련 변수
	bool IsPush = false;
	float MoveSpeed = 100.f;
	float MoveCompleteTime = 0.4f;
	float PushAccTime = 0.f;

	int ny = 0;
	int nx = 0;

	FVector MoveDir = FVector::Zero;
	POINT PlayerIndex = { 0,0 };

	float FrameTime = 1.0f / 60.0f;
	float CurTime = FrameTime;
	

	
	

};

