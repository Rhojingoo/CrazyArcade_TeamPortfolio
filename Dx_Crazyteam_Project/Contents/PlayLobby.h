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
	void SwapTeamSelectCharacter(UImage* _SelectCharacter);


	void TeamSelectBegin();
	void RoomBegin();
	void CharacterBegin();
	void StartBegin();
	void MapSelectBegin();
	void LobbyPlayerBegin();

	UImage* PlayLobbyUI = nullptr;
	UImage* GameStart = nullptr;
	UImage* SelectMap = nullptr;

	//ĳ���� ����â
	UImage* RandomBT = nullptr;
	UImage* DaoBT = nullptr;
	UImage* DizniBT = nullptr;
	UImage* MosBT = nullptr;
	UImage* EthiBT = nullptr;
	UImage* MaridBT = nullptr;
	UImage* BazziBT = nullptr;
	UImage* UniBT = nullptr;
	UImage* KephiBT = nullptr;
	UImage* SuBT = nullptr;
	UImage* HooUBT = nullptr;
	UImage* RayBT = nullptr;

	//ĳ���� ����
	UImage* LobbyCharacterBanner = nullptr;
	UImage* Randomex = nullptr;
	UImage* Daoex = nullptr;
	UImage* Maridex = nullptr;
	UImage* Kephiex = nullptr;
	UImage* Bazziex = nullptr;
	
	//�� ����
	UImage* SelectTeam = nullptr;
	UImage* TeamA = nullptr;
	UImage* TeamB = nullptr;
	
	//������ ĳ����
	UImage* SelectCharacter = nullptr;
	UImage* checkUI = nullptr;

	//�κ� �÷��̾� ĳ����
	std::vector<UImage*> LobbyPlayer;
	std::vector<UImage*> Rank;
	
	//�÷��̾� Room
	UImage* Room1 = nullptr;
	UImage* Room2 = nullptr;
	UImage* Room3 = nullptr;
	UImage* Room4 = nullptr;
	UImage* Room5 = nullptr;
	UImage* Room6 = nullptr;
	UImage* Room7 = nullptr;
	
	ACAGameMode* Teamtyp = nullptr;


	bool SwitchON = false;
	bool TeamSwitchON = false;
	bool IsSelectSharacter = false;
	bool IsTeamSelectSharacter = false;

	bool RoomHoverChack = false;
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

