#pragma once
#include <EngineBase/NetObject.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "ContentsEnum.h"
#include "CAObject.h"
#include "NetInterface.h"

class APlayer;
class PlayerInfo
{
	friend APlayer;

public:
	POINT CurIndex = POINT(0, 0);
	ECharacterType MyType = ECharacterType::Bazzi;
	ETeamType Team = ETeamType::None;
	EPlayerRideType RideType = EPlayerRideType::None;

	int Speed = -1;					// �ӵ�
	int WBCount = -1;				// ����ź ����	
	int WBPower = -1;				// ����ź �Ŀ�(���ٱ� ����)

	int MaxSpeed = -1;
	int MaxWBCount = -1;
	int MaxWBPower = -1;
};

class APlayer_Shadow;

class APlayer : public ACAObject
{
	GENERATED_BODY(ACAObject)
public:
	APlayer();
	~APlayer();

	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;
	
	void SetCharacterType(ECharacterType _Type);

	void SetWBCount(int _count)
	{
		Info->WBCount = _count;
	}

	void SetTeamType(ETeamType _Team)
	{
		Info->Team = _Team;
	}
	
	void SetSpeed(int _speed)
	{
		Info->Speed = _speed;
	}

	int GetWBCount()
	{
		return Info->WBCount;
	}

	int GetWBPower()
	{
		return Info->WBPower;
	}

	int GetSpeed()
	{
		return Info->Speed;
	}

	PlayerInfo* GetPlayerInfo()
	{
		return Info.get();
	}

	static int WaterBomb_Token;

protected:
	std::shared_ptr<PlayerInfo> Info = nullptr;
	UStateManager State;
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	void StateInit();

	void IdleStart();
	void Idle(float _DeltaTime);
	void MoveStart();
	void Move(float _DeltaTime);
	void TrapStart();
	void Trap(float _DeltaTime);
	void RescueStart();
	void Rescue(float _DeltaTime);
	void DieStart();
	void Die(float _DeltaTime);
	void RealDieStart();
	void RealDie(float _DeltaTime);
	void RideIdleStart();
	void RideIdle(float _DeltaTime);
	void RideMoveStart();
	void RideMove(float _DeltaTime);


	std::string GetAnimationName(std::string_view _StateName);

	FVector Dir = FVector::Down;
	float AnimationInter = 0.1f;
	float MoveSpeed = 20.f;		// �ӵ� ���

	float TrapMoveSpeed = 0.4f;
	float TrapMoveTime = 1.f;
	float TrapAnimationTime = 3.f;
	float TrapToDieTime = 5.f;
	FVector TrapDir = FVector::Up;

	bool DieAnimationChange = false;
	bool DieAniTwinkleActive = false;
	float DieAnimationTime = 2.f;
	float DieTwinkleTime = 0.1f;

	std::shared_ptr<APlayer_Shadow> Shadow = nullptr;



};


