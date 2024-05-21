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
	ETeamType Team = ETeamType::ATeam;
	EPlayerRideType RideType = EPlayerRideType::None;

	int Speed = -1;					// �ӵ� �ܰ� (1�� ���������ָ� �ӵ� ����� ���ؼ� �����)
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
	
	void MainPlayerInit();
	void MainPlayerSetting();

	void SetCharacterType(ECharacterType _Type);
	void SetRideType(EPlayerRideType _Ride);

	void AddBeforeSpeedData()
	{
		if (BeforeSpeedData < 10)
		{
			++BeforeSpeedData;
		}
	}

	void SetWBCount(int _count)
	{
		Info->WBCount = _count;
	}

	void SetTeamType(ETeamType _Team)
	{
		Info->Team = _Team;
	}
	
	void SetSpeed(int _Speed)
	{
		Info->Speed = _Speed;
	}

	void SetCtrlItem(EItemType _Item)
	{
		CtrlItem = _Item;
	}

	ETeamType GetTeamType()
	{
		return Info->Team;
	}

	EPlayerRideType GetRideType()
	{
		return Info->RideType;
	}

	EItemType GetCtrlItem()
	{
		return CtrlItem;
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

	inline bool GetIsSendPacket() const
	{
		return IsSendPacket;
	}

	inline void OffIsSendPacket()
	{
		IsSendPacket = false;
	}

	static int WaterBomb_Token;
	static int WaterCourse_Token;
	static bool SetWater_Token;

protected:
	std::shared_ptr<PlayerInfo> Info = nullptr;
	UStateManager State;
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	EItemType CtrlItem = EItemType::None;
	int BeforeSpeedData = -1;

	void StateInit();

	void GameOnStart();
	void GameOn(float _DeltaTime);
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
	void RideOffStart();
	void RideOff(float _DeltaTime);

	void DebugFunction(float _DeltaTime);

	float GameOnTime = 1.5f;

	std::string GetAnimationName(std::string_view _StateName);
	void SettingZValue();
	void WaterBombUpdate();

	FVector Dir = FVector::Down;
	float AnimationInter = 0.1f;
	float MoveSpeed = 25.f;		// �ӵ� ���

	float TrapMoveSpeed = 0.4f;
	float TrapMoveTime = 1.f;
	float TrapAnimationTime = 3.f;
	float TrapToDieTime = 5.f;
	FVector TrapDir = FVector::Up;

	int DieAniTwinkleActive = 0;
	float DieAnimationTime = 2.f;
	float DieTwinkleTime = 0.1f;

	float RideGodModeTime = 2.f; // Ż�Ϳ� Ÿ�ų� ���� �� ���ʰ� �������
	float RideTwinkleTime = 0.1f;
	int RideAniTwinkleActive = 0;

	std::shared_ptr<APlayer_Shadow> Shadow = nullptr;

	bool IsSendPacket = true;

	bool IsBushRenderOff = false;

};


