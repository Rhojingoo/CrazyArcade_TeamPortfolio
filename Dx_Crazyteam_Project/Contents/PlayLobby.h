#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>


class UImage;
class ACAObject;
class ACAGameMode;
class APlayLobby : public AActor, public UNetObject
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	APlayLobby();
	~APlayLobby();

	// delete Function
	APlayLobby(const APlayLobby& _Other) = delete;
	APlayLobby(APlayLobby&& _Other) noexcept = delete;
	APlayLobby& operator=(const APlayLobby& _Other) = delete;
	APlayLobby& operator=(APlayLobby&& _Other) noexcept = delete;

	void SetIsActive(bool _Active);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void SwapSelectCharacter(UImage* _SelectCharacter);

	UImage* PlayLobbyUI = nullptr;
	UImage* GameStart = nullptr;
	UImage* SelectMap = nullptr;

	//ĳ���� ����â
	UImage* RandomBT;
	UImage* DaoBT;
	UImage* DizniBT;
	UImage* MosBT;
	UImage* EthiBT;
	UImage* MaridBT;
	UImage* BazziBT;
	UImage* UniBT;
	UImage* KephiBT;
	UImage* SuBT;
	UImage* HooUBT;
	UImage* RayBT;

	//ĳ���� ����
	UImage* LobbyCharacterBanner;
	UImage* Randomex;
	UImage* Daoex;
	UImage* Maridex;
	UImage* Kephiex;
	UImage* Bazziex;
	
	//�� ����
	UImage* TeamA;
	UImage* TeamB;
	
	//������ ĳ����
	UImage* SelectCharacter;
	UImage* checkUI;

	//�κ� �÷��̾� ĳ����
	std::vector<UImage*> LobbyPlayer;
	std::vector<UImage*> Rank;
	
	//�÷��̾� Room
	UImage* Room1;
	UImage* Room2;
	UImage* Room3;
	UImage* Room4;
	UImage* Room5;
	UImage* Room6;
	UImage* Room7;
	
	ACAGameMode* Teamtyp = nullptr;


	bool SwitchON = false;
	bool TeamSwitchON = false;
	bool IsSelectSharacter = false;
	bool IsTeamSelectSharacter = false;
	bool RoomO1 = true;
	bool RoomX1 = false;
	bool RoomO2 = true;
	bool RoomX2 = false;
	bool RoomO3 = true;
	bool RoomX3 = false;
	bool RoomO4 = true;
	bool RoomX4 = false;
	bool RoomO5 = true;
	bool RoomX5 = false;
	bool RoomO6 = true;
	bool RoomX6 = false;
	bool RoomO7 = true;
	bool RoomX7 = false;


	bool RoomSwitch= false;
	int  PlayerCount = 0;
	int TestCount = 0;
};

