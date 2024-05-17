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
	
	std::vector<UImage*> RoomVector;
	std::vector<UImage*>::iterator RoomIter = RoomVector.begin();
	std::vector<bool> RoomVectorNumber;


	bool SwitchON = false;
	bool TeamSwitchON = false;
	bool IsSelectSharacter = false;
	bool IsTeamSelectSharacter = false;
	bool RoomO = true;
	bool RoomX = false;
	bool RoomSwitch= false;
	int  PlayerCount = 0;
	int TestCount = 0;
};

