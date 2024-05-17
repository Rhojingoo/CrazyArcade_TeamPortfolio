#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>

class UImage;
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
	
	//�÷��̾� Room
	UImage* Room1;
	UImage* Room2;
	UImage* Room3;
	UImage* Room4;
	UImage* Room5;
	UImage* Room6;
	UImage* Room7;

	UImage* XRoom1;
	UImage* XRoom2;
	UImage* XRoom3;
	UImage* XRoom4;
	UImage* XRoom5;
	UImage* XRoom6;
	UImage* XRoom7;


	bool SwitchON = false;
	bool TeamSwitchON = false;
	bool IsSelectSharacter = false;
	bool IsTeamSelectSharacter = false;
	bool RoomO = true;
	bool RoomX = false;
	bool RoomSwitch= false;
	bool OX = false;
	int  PlayerCount = 0;
	int TestCount = 0;
};

