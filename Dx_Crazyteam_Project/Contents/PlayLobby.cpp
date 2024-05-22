#include "PreCompile.h"
#include "PlayLobby.h"
#include "Player.h"
#include "CAGameMode.h"

#include "EngineCore/Image.h"
#include "EngineBase/EngineDebug.h"
#include "SendPacketManager.h"
#include "Game_Core.h"

bool APlayLobby::IsClient = false;
bool APlayLobby::Create = false;
int APlayLobby::Create_Count =  0;

APlayLobby::APlayLobby()
{
}

APlayLobby::~APlayLobby()
{
}

void APlayLobby::BeginPlay()
{
	Super::BeginPlay();
	InputOn();
	LobbyPlayer.resize(8);
	Rank.resize(8);

	PlayLobbyUI = CreateWidget<UImage>(GetWorld(), "PlayLobbyUI");
	PlayLobbyUI->AddToViewPort(10);
	PlayLobbyUI->SetSprite("Waiting.png");
	PlayLobbyUI->SetScale({ 800, 600 });
	PlayLobbyUI->SetActive(true);

	//�÷��̾� Room
	Room1 = CreateWidget<UImage>(GetWorld(), "Room1");
	Room1->CreateAnimation("UnHover", "Room_0.png", 0.1f, false, 0, 0);
	Room1->CreateAnimation("Hover", "Room_1.png", 0.1f, false, 0, 0);
	Room1->CreateAnimation("Down", "Room_2.png", 0.1f, false, 0, 0);
	Room1->CreateAnimation("Up", "RoomX_0.png", 0.1f, false, 0, 0);
	Room1->CreateAnimation("XUnHover", "RoomX_0.png", 0.1f, false, 0, 0);
	Room1->CreateAnimation("XHover", "RoomX_1.png", 0.1f, false, 0, 0);
	Room1->CreateAnimation("XDown", "RoomX_2.png", 0.1f, false, 0, 0);
	Room1->CreateAnimation("XUp", "Room_0.png", 0.1f, false, 0, 0);
	Room1->AddToViewPort(12);
	Room1->SetSprite("Room_0.png");
	Room1->SetAutoSize(1.0f, true);
	Room1->SetPosition(FVector(-218.f, 157.f));
	Room1->SetActive(true);

	Room2 = CreateWidget<UImage>(GetWorld(), "Room2");
	Room2->CreateAnimation("UnHover", "Room_0.png", 0.1f, false, 0, 0);
	Room2->CreateAnimation("Hover", "Room_1.png", 0.1f, false, 0, 0);
	Room2->CreateAnimation("Down", "Room_2.png", 0.1f, false, 0, 0);
	Room2->CreateAnimation("Up", "RoomX_0.png", 0.1f, false, 0, 0);
	Room2->CreateAnimation("XUnHover", "RoomX_0.png", 0.1f, false, 0, 0);
	Room2->CreateAnimation("XHover", "RoomX_1.png", 0.1f, false, 0, 0);
	Room2->CreateAnimation("XDown", "RoomX_2.png", 0.1f, false, 0, 0);
	Room2->CreateAnimation("XUp", "Room_0.png", 0.1f, false, 0, 0);
	Room2->AddToViewPort(12);
	Room2->SetSprite("Room_0.png");
	Room2->SetAutoSize(1.0f, true);
	Room2->SetPosition(FVector(-112.f, 157.f));
	Room2->SetActive(true);

	Room3 = CreateWidget<UImage>(GetWorld(), "Room3");
	Room3->CreateAnimation("UnHover", "Room_0.png", 0.1f, false, 0, 0);
	Room3->CreateAnimation("Hover", "Room_1.png", 0.1f, false, 0, 0);
	Room3->CreateAnimation("Down", "Room_2.png", 0.1f, false, 0, 0);
	Room3->CreateAnimation("Up", "RoomX_0.png", 0.1f, false, 0, 0);
	Room3->CreateAnimation("XUnHover", "RoomX_0.png", 0.1f, false, 0, 0);
	Room3->CreateAnimation("XHover", "RoomX_1.png", 0.1f, false, 0, 0);
	Room3->CreateAnimation("XDown", "RoomX_2.png", 0.1f, false, 0, 0);
	Room3->CreateAnimation("XUp", "Room_0.png", 0.1f, false, 0, 0);
	Room3->AddToViewPort(12);
	Room3->SetSprite("Room_0.png");
	Room3->SetAutoSize(1.0f, true);
	Room3->SetPosition(FVector(-6.f, 157.f));
	Room3->SetActive(true);

	Room4 = CreateWidget<UImage>(GetWorld(), "Room4");
	Room4->CreateAnimation("UnHover", "Room_0.png", 0.1f, false, 0, 0);
	Room4->CreateAnimation("Hover", "Room_1.png", 0.1f, false, 0, 0);
	Room4->CreateAnimation("Down", "Room_2.png", 0.1f, false, 0, 0);
	Room4->CreateAnimation("Up", "RoomX_0.png", 0.1f, false, 0, 0);
	Room4->CreateAnimation("XUnHover", "RoomX_0.png", 0.1f, false, 0, 0);
	Room4->CreateAnimation("XHover", "RoomX_1.png", 0.1f, false, 0, 0);
	Room4->CreateAnimation("XDown", "RoomX_2.png", 0.1f, false, 0, 0);
	Room4->CreateAnimation("XUp", "Room_0.png", 0.1f, false, 0, 0);
	Room4->AddToViewPort(12);
	Room4->SetSprite("Room_0.png");
	Room4->SetAutoSize(1.0f, true);
	Room4->SetPosition(FVector(-324.f, 11.f));
	Room4->SetActive(true);

	Room5 = CreateWidget<UImage>(GetWorld(), "Room5");
	Room5->CreateAnimation("UnHover", "Room_0.png", 0.1f, false, 0, 0);
	Room5->CreateAnimation("Hover", "Room_1.png", 0.1f, false, 0, 0);
	Room5->CreateAnimation("Down", "Room_2.png", 0.1f, false, 0, 0);
	Room5->CreateAnimation("Up", "RoomX_0.png", 0.1f, false, 0, 0);
	Room5->CreateAnimation("XUnHover", "RoomX_0.png", 0.1f, false, 0, 0);
	Room5->CreateAnimation("XHover", "RoomX_1.png", 0.1f, false, 0, 0);
	Room5->CreateAnimation("XDown", "RoomX_2.png", 0.1f, false, 0, 0);
	Room5->CreateAnimation("XUp", "Room_0.png", 0.1f, false, 0, 0);
	Room5->AddToViewPort(12);
	Room5->SetSprite("Room_0.png");
	Room5->SetAutoSize(1.0f, true);
	Room5->SetPosition(FVector(-218.f, 11.f));
	Room5->SetActive(true);

	Room6 = CreateWidget<UImage>(GetWorld(), "Room6");
	Room6->CreateAnimation("UnHover", "Room_0.png", 0.1f, false, 0, 0);
	Room6->CreateAnimation("Hover", "Room_1.png", 0.1f, false, 0, 0);
	Room6->CreateAnimation("Down", "Room_2.png", 0.1f, false, 0, 0);
	Room6->CreateAnimation("Up", "RoomX_0.png", 0.1f, false, 0, 0);
	Room6->CreateAnimation("XUnHover", "RoomX_0.png", 0.1f, false, 0, 0);
	Room6->CreateAnimation("XHover", "RoomX_1.png", 0.1f, false, 0, 0);
	Room6->CreateAnimation("XDown", "RoomX_2.png", 0.1f, false, 0, 0);
	Room6->CreateAnimation("XUp", "Room_0.png", 0.1f, false, 0, 0);
	Room6->AddToViewPort(12);
	Room6->SetSprite("Room_0.png");
	Room6->SetAutoSize(1.0f, true);
	Room6->SetPosition(FVector(-112.f, 11.f));
	Room6->SetActive(true);

	Room7 = CreateWidget<UImage>(GetWorld(), "Room7");
	Room7->CreateAnimation("UnHover", "Room_0.png", 0.1f, false, 0, 0);
	Room7->CreateAnimation("Hover", "Room_1.png", 0.1f, false, 0, 0);
	Room7->CreateAnimation("Down", "Room_2.png", 0.1f, false, 0, 0);
	Room7->CreateAnimation("Up", "RoomX_0.png", 0.1f, false, 0, 0);
	Room7->CreateAnimation("XUnHover", "RoomX_0.png", 0.1f, false, 0, 0);
	Room7->CreateAnimation("XHover", "RoomX_1.png", 0.1f, false, 0, 0);
	Room7->CreateAnimation("XDown", "RoomX_2.png", 0.1f, false, 0, 0);
	Room7->CreateAnimation("XUp", "Room_0.png", 0.1f, false, 0, 0);
	Room7->AddToViewPort(12);
	Room7->SetSprite("Room_0.png");
	Room7->SetAutoSize(1.0f, true);
	Room7->SetPosition(FVector(-6.f, 11.f));
	Room7->SetActive(true);


	//���� ��ư
	GameStart = CreateWidget<UImage>(GetWorld(), "GameStart");
	GameStart->CreateAnimation("UnHover", "StartBt_1.png", 0.1f, false, 0, 0);
	GameStart->CreateAnimation("Hover", "StartBT", 0.1f, true, 6, 7);
	GameStart->CreateAnimation("Down", "StartBt_3.png", 0.1f, false, 0, 0);
	GameStart->AddToViewPort(10);
	GameStart->SetSprite("StartBt_1.png");
	GameStart->SetScale({ 190,52 });
	GameStart->SetPosition({ 209,-223 });
	GameStart->SetActive(true);
	GameStart->ChangeAnimation("UnHover");

	//�ʼ��� ��ư
	SelectMap = CreateWidget<UImage>(GetWorld(), "SelectMap");
	SelectMap->CreateAnimation("UnHover", "SelectMap_0.png", 0.1f, false, 0, 0);
	SelectMap->CreateAnimation("Hover", "SelectMap", 0.1f, true, 1, 2);
	SelectMap->CreateAnimation("Down", "SelectMap_3.png", 0.1f, false, 0, 0);
	SelectMap->AddToViewPort(12);
	SelectMap->SetSprite("SelectMap_0.png");
	SelectMap->SetAutoSize(1.0f, true);
	SelectMap->SetPosition({ 306.0f,-152.0f });
	SelectMap->SetActive(true);
	SelectMap->ChangeAnimation("UnHover");

	MapSelect = CreateWidget<UImage>(GetWorld(), "MapSelect");
	MapSelect->AddToViewPort(16);
	MapSelect->SetSprite("Village10.png");
	MapSelect->SetAutoSize(1.0f, true);
	MapSelect->SetPosition({ 0.f,0.f });
	MapSelect->SetActive(false);
	
	MapSelectVName = CreateWidget<UImage>(GetWorld(), "MapSelectVName");
	MapSelectVName->AddToViewPort(16);
	MapSelectVName->SetSprite("Village10_name.png");
	MapSelectVName->SetAutoSize(1.0f, true);
	MapSelectVName->SetPosition({ 70.f,110.f });
	MapSelectVName->SetActive(false);

	MapSelectVTitle = CreateWidget<UImage>(GetWorld(), "MapSelectVTitle");
	MapSelectVTitle->AddToViewPort(16);
	MapSelectVTitle->SetSprite("Village10_title.png");
	MapSelectVTitle->SetAutoSize(1.0f, true);
	MapSelectVTitle->SetPosition({ -169.f,171.f });
	MapSelectVTitle->SetActive(false);
	
	MapSelectVPick = CreateWidget<UImage>(GetWorld(), "MapSelectVPick");
	MapSelectVPick->AddToViewPort(16);
	MapSelectVPick->SetSprite("Village10_name_Pick.png");
	MapSelectVPick->SetAutoSize(1.0f, true);
	MapSelectVPick->SetPosition({ 73.f,109.f });
	MapSelectVPick->SetActive(false);
	
	MapSelectVinfo = CreateWidget<UImage>(GetWorld(), "MapSelectVPick");
	MapSelectVinfo->AddToViewPort(16);
	MapSelectVinfo->SetSprite("Village10_info.png");
	MapSelectVinfo->SetAutoSize(1.0f, true);
	MapSelectVinfo->SetPosition({ -169.f,-82.f });
	MapSelectVinfo->SetActive(false);

	MapSelectCTitle = CreateWidget<UImage>(GetWorld(), "MapSelectCTitle");
	MapSelectCTitle->AddToViewPort(16);
	MapSelectCTitle->SetSprite("Cam02_title.png");
	MapSelectCTitle->SetAutoSize(1.0f, true);
	MapSelectCTitle->SetPosition({ -169.f,171.f });
	MapSelectCTitle->SetActive(false);
		
	MapSelectCName = CreateWidget<UImage>(GetWorld(), "MapSelectCName");
	MapSelectCName->AddToViewPort(16);
	MapSelectCName->SetSprite("Cam02_name.png");
	MapSelectCName->SetAutoSize(1.0f, true);
	MapSelectCName->SetPosition({ 70.f,92.f });
	MapSelectCName->SetActive(false);
	
	MapSelectCPick = CreateWidget<UImage>(GetWorld(), "MapSelectCName");
	MapSelectCPick->AddToViewPort(16);
	MapSelectCPick->SetSprite("Cam02_name_Pick.png");
	MapSelectCPick->SetAutoSize(1.0f, true);
	MapSelectCPick->SetPosition({ 65.f,91.f });
	MapSelectCPick->SetActive(false);

	MapSelectCMinimap = CreateWidget<UImage>(GetWorld(), "MapSelectCMinimap");
	MapSelectCMinimap->AddToViewPort(16);
	MapSelectCMinimap->SetSprite("Cam02_minimap.png");
	MapSelectCMinimap->SetAutoSize(1.0f, true);
	MapSelectCMinimap->SetPosition({ -169.f,89.f });
	MapSelectCMinimap->SetActive(false);

	MapSelectCinfo = CreateWidget<UImage>(GetWorld(), "MapSelectVPick");
	MapSelectCinfo->AddToViewPort(16);
	MapSelectCinfo->SetSprite("Cam02_info.png");
	MapSelectCinfo->SetAutoSize(1.0f, true);
	MapSelectCinfo->SetPosition({ 73.f,109.f });
	MapSelectCinfo->SetActive(false);

	
	EnterButton = CreateWidget<UImage>(GetWorld(), "MapSelectVPick");
	EnterButton->AddToViewPort(16);
	EnterButton->SetSprite("Cam02_info.png");
	EnterButton->SetAutoSize(1.0f, true);
	EnterButton->SetPosition({ 73.f,109.f });
	EnterButton->SetActive(false);
	
	CancelButton = CreateWidget<UImage>(GetWorld(), "MapSelectVPick");
	CancelButton->AddToViewPort(16);
	CancelButton->SetSprite("Cam02_info.png");
	CancelButton->SetAutoSize(1.0f, true);
	CancelButton->SetPosition({ 73.f,109.f });
	CancelButton->SetActive(false);




	//ĳ���� ����â
	RandomBT = CreateWidget<UImage>(GetWorld(), "RandomBT");
	RandomBT->CreateAnimation("UnHover", "CharatorSelect_Button_Random_Normal.bmp", 0.1f, false, 0, 0);
	RandomBT->CreateAnimation("Hover", "CharatorSelect_Button_Random_Hover.bmp", 0.1f, false, 0, 0);
	RandomBT->CreateAnimation("Down", "CharatorSelect_Button_Random_Click.bmp", 0.1f, false, 0, 0);
	RandomBT->CreateAnimation("Up", "CharatorSelect_Button_Random_Pick.bmp", 0.1f, false, 0, 0);
	RandomBT->AddToViewPort(11);
	RandomBT->SetSprite("CharatorSelect_Button_Random_Normal.bmp");
	RandomBT->SetScale({ 65.f,43.f });
	RandomBT->SetPosition({ 122.0f,163.0f });
	RandomBT->SetActive(true);

	DaoBT = CreateWidget<UImage>(GetWorld(), "DaoBT");
	DaoBT->CreateAnimation("UnHover", "CharatorSelect_Button_Dao_Normal.bmp", 0.1f, false, 0, 0);
	DaoBT->CreateAnimation("Hover", "CharatorSelect_Button_Dao_Hover.bmp", 0.1f, false, 0, 0);
	DaoBT->CreateAnimation("Down", "CharatorSelect_Button_Dao_Click.bmp", 0.1f, false, 0, 0);
	DaoBT->CreateAnimation("Up", "CharatorSelect_Button_Dao_Pick.bmp", 0.1f, false, 0, 0);
	DaoBT->AddToViewPort(11);
	DaoBT->SetSprite("CharatorSelect_Button_Dao_Pick.bmp");
	DaoBT->SetScale({ 65.f,43.f });
	DaoBT->SetPosition({ 194.0f,163.0f });
	DaoBT->SetActive(true);

	DizniBT = CreateWidget<UImage>(GetWorld(), "DizniBT");
	DizniBT->CreateAnimation("UnHover", "CharatorSelect_Button_Dizni_Normal.bmp", 0.1f, false, 0, 0);
	DizniBT->CreateAnimation("Hover", "CharatorSelect_Button_Dizni_Hover.bmp", 0.1f, false, 0, 0);
	DizniBT->CreateAnimation("Down", "CharatorSelect_Button_Dizni_Click.bmp", 0.1f, false, 0, 0);
	DizniBT->AddToViewPort(11);
	DizniBT->SetSprite("CharatorSelect_Button_Dizni_Normal.bmp");
	DizniBT->SetScale({ 65.f,43.f });
	DizniBT->SetPosition({ 266.0f,163.0f });
	DizniBT->SetActive(true);

	MosBT = CreateWidget<UImage>(GetWorld(), "MosBT");
	MosBT->CreateAnimation("UnHover", "CharatorSelect_Button_Mos_Normal.bmp", 0.1f, false, 0, 0);
	MosBT->CreateAnimation("Hover", "CharatorSelect_Button_Mos_Hover.bmp", 0.1f, false, 0, 0);
	MosBT->CreateAnimation("Down", "CharatorSelect_Button_Mos_Click.bmp", 0.1f, false, 0, 0);
	MosBT->AddToViewPort(11);
	MosBT->SetSprite("CharatorSelect_Button_Mos_Normal.bmp");
	MosBT->SetScale({ 65.f,43.f });
	MosBT->SetPosition({ 338.0f,163.0f });
	MosBT->SetActive(true);

	EthiBT = CreateWidget<UImage>(GetWorld(), "EthiBT");
	EthiBT->CreateAnimation("UnHover", "CharatorSelect_Button_Ethi_Normal.bmp", 0.1f, false, 0, 0);
	EthiBT->CreateAnimation("Hover", "CharatorSelect_Button_Ethi_Hover.bmp", 0.1f, false, 0, 0);
	EthiBT->CreateAnimation("Down", "CharatorSelect_Button_Ethi_Click.bmp", 0.1f, false, 0, 0);
	EthiBT->AddToViewPort(11);
	EthiBT->SetSprite("CharatorSelect_Button_Ethi_Normal.bmp");
	EthiBT->SetScale({ 65.f,43.f });
	EthiBT->SetPosition({ 122.0f,114.0f });
	EthiBT->SetActive(true);

	MaridBT = CreateWidget<UImage>(GetWorld(), "MosBT");
	MaridBT->CreateAnimation("UnHover", "CharatorSelect_Button_Marid_Normal.bmp", 0.1f, false, 0, 0);
	MaridBT->CreateAnimation("Hover", "CharatorSelect_Button_Marid_Hover.bmp", 0.1f, false, 0, 0);
	MaridBT->CreateAnimation("Down", "CharatorSelect_Button_Marid_Click.bmp", 0.1f, false, 0, 0);
	MaridBT->CreateAnimation("Up", "CharatorSelect_Button_Marid_Pick.bmp", 0.1f, false, 0, 0);
	MaridBT->AddToViewPort(11);
	MaridBT->SetSprite("CharatorSelect_Button_Marid_Normal.bmp");
	MaridBT->SetScale({ 65.f,43.f });
	MaridBT->SetPosition({ 194.0f,114.0f });
	MaridBT->SetActive(true);

	BazziBT = CreateWidget<UImage>(GetWorld(), "MosBT");
	BazziBT->CreateAnimation("UnHover", "CharatorSelect_Button_Bazzi_Normal.bmp", 0.1f, false, 0, 0);
	BazziBT->CreateAnimation("Hover", "CharatorSelect_Button_Bazzi_Hover.bmp", 0.1f, false, 0, 0);
	BazziBT->CreateAnimation("Down", "CharatorSelect_Button_Bazzi_Click.bmp", 0.1f, false, 0, 0);
	BazziBT->CreateAnimation("Up", "CharatorSelect_Button_Bazzi_Pick.bmp", 0.1f, false, 0, 0);
	BazziBT->AddToViewPort(11);
	BazziBT->SetSprite("CharatorSelect_Button_Bazzi_Normal.bmp");
	BazziBT->SetScale({ 65.f,43.f });
	BazziBT->SetPosition({ 266.0f,114.0f });
	BazziBT->SetActive(true);

	UniBT = CreateWidget<UImage>(GetWorld(), "UniBT");
	UniBT->CreateAnimation("UnHover", "CharatorSelect_Button_Uni_Normal.bmp", 0.1f, false, 0, 0);
	UniBT->CreateAnimation("Hover", "CharatorSelect_Button_Uni_Hover.bmp", 0.1f, false, 0, 0);
	UniBT->CreateAnimation("Down", "CharatorSelect_Button_Uni_Click.bmp", 0.1f, false, 0, 0);
	UniBT->AddToViewPort(11);
	UniBT->SetSprite("CharatorSelect_Button_Uni_Normal.bmp");
	UniBT->SetScale({ 65.f,43.f });
	UniBT->SetPosition({ 338.0f,114.0f });
	UniBT->SetActive(true);

	KephiBT = CreateWidget<UImage>(GetWorld(), "MosBT");
	KephiBT->CreateAnimation("UnHover", "CharatorSelect_Button_Kephi_Normal.bmp", 0.1f, false, 0, 0);
	KephiBT->CreateAnimation("Hover", "CharatorSelect_Button_Kephi_Hover.bmp", 0.1f, false, 0, 0);
	KephiBT->CreateAnimation("Down", "CharatorSelect_Button_Kephi_Click.bmp", 0.1f, false, 0, 0);
	KephiBT->CreateAnimation("Up", "CharatorSelect_Button_Kephi_Pick.bmp", 0.1f, false, 0, 0);
	KephiBT->AddToViewPort(11);
	KephiBT->SetSprite("CharatorSelect_Button_Kephi_Normal.bmp");
	KephiBT->SetScale({ 65.f,43.f });
	KephiBT->SetPosition({ 122.0f,65.0f });
	KephiBT->SetActive(true);

	SuBT = CreateWidget<UImage>(GetWorld(), "SuBT");
	SuBT->CreateAnimation("UnHover", "CharatorSelect_Button_Su_Normal.bmp", 0.1f, false, 0, 0);
	SuBT->CreateAnimation("Hover", "CharatorSelect_Button_Su_Hover.bmp", 0.1f, false, 0, 0);
	SuBT->CreateAnimation("Down", "CharatorSelect_Button_Su_Click.bmp", 0.1f, false, 0, 0);
	SuBT->AddToViewPort(11);
	SuBT->SetSprite("CharatorSelect_Button_Su_Normal.bmp");
	SuBT->SetScale({ 65.f,43.f });
	SuBT->SetPosition({ 194.0f,65.0f });
	SuBT->SetActive(true);

	HooUBT = CreateWidget<UImage>(GetWorld(), "MosBT");
	HooUBT->CreateAnimation("UnHover", "CharatorSelect_Button_HooU_Normal.bmp", 0.1f, false, 0, 0);
	HooUBT->CreateAnimation("Hover", "CharatorSelect_Button_HooU_Hover.bmp", 0.1f, false, 0, 0);
	HooUBT->CreateAnimation("Down", "CharatorSelect_Button_HooU_Click.bmp", 0.1f, false, 0, 0);
	HooUBT->AddToViewPort(11);
	HooUBT->SetSprite("CharatorSelect_Button_HooU_Normal.bmp");
	HooUBT->SetScale({ 65.f,43.f });
	HooUBT->SetPosition({ 266.0f,65.0f });
	HooUBT->SetActive(true);

	RayBT = CreateWidget<UImage>(GetWorld(), "RayBT");
	RayBT->CreateAnimation("UnHover", "CharatorSelect_Button_Ray_Normal.bmp", 0.1f, false, 0, 0);
	RayBT->CreateAnimation("Hover", "CharatorSelect_Button_Ray_Hover.bmp", 0.1f, false, 0, 0);
	RayBT->CreateAnimation("Down", "CharatorSelect_Button_Ray_Click.bmp", 0.1f, false, 0, 0);
	RayBT->AddToViewPort(11);
	RayBT->SetSprite("CharatorSelect_Button_Ray_Normal.bmp");
	RayBT->SetScale({ 65.f,43.f });
	RayBT->SetPosition({ 338.0f,65.0f });
	RayBT->SetActive(true);

	LobbyCharacterBanner = CreateWidget<UImage>(GetWorld(), "Randomex");
	LobbyCharacterBanner->AddToViewPort(11);
	LobbyCharacterBanner->SetSprite("CharatorSelect_Outline_Random.bmp");
	LobbyCharacterBanner->SetScale({ 281.f, 80.f });
	LobbyCharacterBanner->SetPosition({ 230.0f,237.0f });
	LobbyCharacterBanner->SetActive(true);

	//�� ����
	TeamA = CreateWidget<UImage>(GetWorld(), "TeamA");
	TeamA->CreateAnimation("TeamUnHover", "ATeam.png", 0.1f, false, 0, 0);
	TeamA->CreateAnimation("TeamHover", "ATeam.png", 0.1f, false, 0, 0);
	TeamA->CreateAnimation("TeamDown", "ATeam_Down.png", 0.1f, false, 0, 0);
	TeamA->CreateAnimation("TeamUp", "ATeam_Pick.png", 0.1f, false, 0, 0);
	TeamA->AddToViewPort(12);
	TeamA->SetSprite("ATeam.png");
	TeamA->SetScale({ 100.f, 50.f });
	TeamA->SetPosition({ 160.0f,0.0f });
	TeamA->SetActive(true);

	TeamB = CreateWidget<UImage>(GetWorld(), "TeamB");
	TeamB->CreateAnimation("TeamUnHover", "BTeam.png", 0.1f, false, 0, 0);
	TeamB->CreateAnimation("TeamHover", "BTeam.png", 0.1f, false, 0, 0);
	TeamB->CreateAnimation("TeamDown", "BTeam_Down.png", 0.1f, false, 0, 0);
	TeamB->CreateAnimation("TeamUp", "BTeam_Pick.png", 0.1f, false, 0, 0);
	TeamB->AddToViewPort(12);
	TeamB->SetSprite("BTeam.png");
	TeamB->SetScale({ 100.f, 50.f });
	TeamB->SetPosition({ 300.0f,0.0f });
	TeamB->SetActive(true);


	// ������ ĳ����
	SelectCharacter = RandomBT;
	SelectTeam = TeamA;

	checkUI = CreateWidget<UImage>(GetWorld(), "checkUI");
	checkUI->AddToViewPort(13);
	checkUI->SetSprite("check.png");
	checkUI->SetAutoSize(1.0f, true);
	checkUI->SetPosition({ 222.0f,183.0f });
	checkUI->SetActive(true);

	Teamtyp = dynamic_cast<ACAGameMode*>(GetWorld()->GetGameMode().get());


	MapSelectButtonBegin();
	StartBegin();
	TeamSelectBegin();

	CharacterBegin();
}

void APlayLobby::SettingUIPlayerName(std::vector<std::string> _Names)
{

	if (8 != _Names.size())
	{
		MsgBoxAssert("8���� �������̵� �����Ͱ� �ƴմϴ�.");
	}

	for (size_t i = 0; i < _Names.size(); i++)
	{
		std::string Name = _Names[i];

		if (Name == "None")
		{
			continue;
		}

		if (nullptr == LobbyPlayer[i])
		{
			LobbyPlayer[i] = CreateWidget<UImage>(GetWorld(), "LobbyPlayer");
			LobbyPlayer[i]->AddToViewPort(15);
			if (i <= 3)
			{
				LobbyPlayer[i]->SetPosition(FVector(static_cast<float>(-335.f + i * 105), 160.0f, 100.0f));

			}
			else
			{
				LobbyPlayer[i]->SetPosition(FVector(static_cast<float>(-755.f + i * 105), 10.0f, 100.0f));
			}
		}


		LobbyPlayer[i]->SetSprite(_Names[i]);
		LobbyPlayer[i]->SetAutoSize(1.2f, true);
	}
}

void APlayLobby::NewPlayer()
{
	//PlayerCount
	Cha_Count = Create_Count;
	LobbyPlayer[Cha_Count] = CreateWidget<UImage>(GetWorld(), "LobbyPlayer");
	LobbyPlayer[Cha_Count]->AddToViewPort(15);
	LobbyPlayer[Cha_Count]->SetSprite("Room_Charcater_Bazzi.png");
	LobbyPlayer[Cha_Count]->SetAutoSize(1.2f, true);
	if (Cha_Count <= 3)
	{
		LobbyPlayer[Create_Count]->SetPosition(FVector(static_cast<float>(-335 + Create_Count * 105), 160.0f, 100.0f));
	}
	else
	{
		LobbyPlayer[Create_Count]->SetPosition(FVector(static_cast<float>(-755 + Create_Count * 105), 10.0f, 100.0f));
	}
	Create_Count++;
}

void APlayLobby::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	PlayLobbyUI->SetActive(true);

	//�� ����

	// Room Hover
	RoomBegin();

	//ĳ���� ����


	//��ŸƮ ��ư

	//�� ���� ��ư
}



void APlayLobby::TeamSelectBegin()
{
	{
		TeamA->SetUnHover([=] {
			if ("TEAMUP" != TeamA->GetUiAniName())
			{
				TeamA->ChangeAnimation("TeamUnHover");
			}
			TeamSwitchON = false;
			});
		TeamA->SetHover([=] {
			{
				if (false == TeamSwitchON && "TEAMUP" != TeamA->GetUiAniName())
				{
					TeamA->ChangeAnimation("TeamHover");
					TeamSwitchON = true;
				}
				else if (IsDown(VK_LBUTTON) && true == TeamSwitchON)
				{
					TeamA->ChangeAnimation("TeamDown");
				}
				else if (IsUp(VK_LBUTTON))
				{
					TeamA->ChangeAnimation("TeamUp");
					IsTeamSelectSharacter = true;
					SwapTeamSelectCharacter(TeamA);
					ConstValue::MainPlayerTeamType = ETeamType::ATeam;
				}
			}
			});
	}

	{
		TeamB->SetUnHover([=] {
			if ("TEAMUP" != TeamB->GetUiAniName())
			{
				TeamB->ChangeAnimation("TeamUnHover");
			}
			TeamSwitchON = false;
			});
		TeamB->SetHover([=] {
			{
				if (false == TeamSwitchON && "TEAMUP" != TeamB->GetUiAniName())
				{
					TeamB->ChangeAnimation("TeamHover");
					TeamSwitchON = true;
				}
				else if (IsDown(VK_LBUTTON) && true == TeamSwitchON)
				{
					TeamB->ChangeAnimation("TeamDown");
				}

				else if (IsUp(VK_LBUTTON))
				{
					TeamB->ChangeAnimation("TeamUp");
					IsTeamSelectSharacter = true;
					SwapTeamSelectCharacter(TeamB);
					ConstValue::MainPlayerTeamType = ETeamType::BTeam;
				}
			}
			});
	}
}

void APlayLobby::RoomBegin()
{
	{
		Room1->SetUnHover([=] {
			if (true == RoomO1 && false == RoomSwitch && "UP" != Room1->GetUiAniName())
			{
				Room1->ChangeAnimation("UnHover");
				RoomO1 = true;
				RoomHoverChack = false;
			}
			else if (true == RoomX1 && "UP" == Room1->GetUiAniName())
			{
				Room1->ChangeAnimation("Up");
				RoomO1 = false;
				RoomX1 = true;
				RoomHoverChack = false;
			}
			});

		Room1->SetHover([=] {
			{
				if (false == RoomHoverChack && true == RoomO1 && false == RoomSwitch && "UP" != Room1->GetUiAniName())
				{
					Room1->ChangeAnimation("Hover");
					RoomSwitch = true;
					RoomHoverChack = true;

				}
				else if (IsDown(VK_LBUTTON) && true == RoomSwitch && true == RoomO1)
				{
					Room1->ChangeAnimation("Down");

				}
				else if (IsUp(VK_LBUTTON) && true == RoomO1)
				{
					IsSelectSharacter = false;
					Room1->ChangeAnimation("Up");
					RoomX1 = true;
					RoomSwitch = true;
					RoomO1 = false;
					RoomHoverChack = false;
				}
				else if (false == RoomHoverChack && false == RoomSwitch && true == RoomX1 && false == RoomO1 && "UP" == Room1->GetUiAniName())
				{
					Room1->ChangeAnimation("XHover");
					RoomX1 = true;
				}
				else if (true == RoomX1 && false == RoomO1 && IsDown(VK_LBUTTON))
				{
					Room1->ChangeAnimation("XDown");
					RoomX1 = true;
					RoomSwitch = true;
				}
				else if (true == RoomX1 && false == RoomO1 && IsUp(VK_LBUTTON))
				{
					IsSelectSharacter = false;
					Room1->ChangeAnimation("XUp");
					RoomX1 = false;
					RoomO1 = true;
					RoomHoverChack = false;
				}
			}
			});

	}

	{
		Room2->SetUnHover([=] {
			if (true == RoomO2 && false == RoomSwitch && "UP" != Room1->GetUiAniName())
			{
				Room2->ChangeAnimation("UnHover");
				RoomO2 = true;
			}
			else if (true == RoomX2 && "UP" == Room2->GetUiAniName())
			{
				Room2->ChangeAnimation("Up");
				RoomO2 = false;
				RoomX2 = true;
			}
			});

		Room2->SetHover([=] {
			{
				if (true == RoomO2 && false == RoomSwitch && "UP" != Room2->GetUiAniName())
				{
					Room2->ChangeAnimation("Hover");
					RoomSwitch = true;

				}
				else if (IsDown(VK_LBUTTON) && true == RoomSwitch && true == RoomO2)
				{
					Room2->ChangeAnimation("Down");

				}
				else if (IsUp(VK_LBUTTON) && true == RoomO2)
				{
					IsSelectSharacter = false;
					Room2->ChangeAnimation("Up");
					RoomX2 = true;
					RoomSwitch = true;
					RoomO2 = false;
				}
				else if (false == RoomSwitch && true == RoomX2 && false == RoomO2 && "UP" == Room2->GetUiAniName())
				{
					Room2->ChangeAnimation("XHover");
					RoomX2 = true;
				}
				else if (true == RoomX2 && false == RoomO2 && IsDown(VK_LBUTTON))
				{
					Room2->ChangeAnimation("XDown");
					RoomX2 = true;
					RoomSwitch = true;
				}
				else if (true == RoomX2 && false == RoomO2 && IsUp(VK_LBUTTON))
				{
					IsSelectSharacter = false;
					Room2->ChangeAnimation("XUp");
					RoomX2 = false;
					RoomO2 = true;
				}
			}
			});
	}

	{
		Room3->SetUnHover([=] {
			if (true == RoomO3 && false == RoomSwitch && "UP" != Room3->GetUiAniName())
			{
				Room3->ChangeAnimation("UnHover");
				RoomO3 = true;
				RoomHoverChack = false;
			}
			else if (true == RoomX3 && "UP" == Room3->GetUiAniName())
			{
				Room3->ChangeAnimation("Up");
				RoomO3 = false;
				RoomX3 = true;
				RoomHoverChack = false;
			}
			});

		Room3->SetHover([=] {
			{
				if (true == RoomO3 && false == RoomSwitch && "UP" != Room3->GetUiAniName())
				{
					Room3->ChangeAnimation("Hover");
					RoomSwitch = true;

				}
				else if (IsDown(VK_LBUTTON) && true == RoomSwitch && true == RoomO3)
				{
					Room3->ChangeAnimation("Down");

				}
				else if (IsUp(VK_LBUTTON) && true == RoomO3)
				{
					IsSelectSharacter = false;
					Room3->ChangeAnimation("Up");
					RoomX3 = true;
					RoomSwitch = true;
					RoomO3 = false;
				}
				else if (false == RoomSwitch && true == RoomX3 && false == RoomO3 && "UP" == Room3->GetUiAniName())
				{
					Room3->ChangeAnimation("XHover");
					RoomX3 = true;
				}
				else if (true == RoomX3 && false == RoomO3 && IsDown(VK_LBUTTON))
				{
					Room3->ChangeAnimation("XDown");
					RoomX3 = true;
					RoomSwitch = true;
				}
				else if (true == RoomX3 && false == RoomO3 && IsUp(VK_LBUTTON))
				{
					IsSelectSharacter = false;
					Room3->ChangeAnimation("XUp");
					RoomX3 = false;
					RoomO3 = true;
				}
			}
			});
	}

	{
		Room4->SetUnHover([=] {
			if (true == RoomO4 && false == RoomSwitch && "UP" != Room4->GetUiAniName())
			{
				Room4->ChangeAnimation("UnHover");
				RoomO4 = true;
				RoomHoverChack = false;
			}
			else if (true == RoomX4 && "UP" == Room4->GetUiAniName())
			{
				Room4->ChangeAnimation("Up");
				RoomO4 = false;
				RoomX4 = true;
				RoomHoverChack = false;
			}
			});

		Room4->SetHover([=] {
			{
				if (true == RoomO4 && false == RoomSwitch && "UP" != Room4->GetUiAniName())
				{
					Room4->ChangeAnimation("Hover");
					RoomSwitch = true;

				}
				else if (IsDown(VK_LBUTTON) && true == RoomSwitch && true == RoomO4)
				{
					Room4->ChangeAnimation("Down");

				}
				else if (IsUp(VK_LBUTTON) && true == RoomO4)
				{
					IsSelectSharacter = false;
					Room4->ChangeAnimation("Up");
					RoomX4 = true;
					RoomSwitch = true;
					RoomO4 = false;
				}
				else if (false == RoomSwitch && true == RoomX4 && false == RoomO4 && "UP" == Room4->GetUiAniName())
				{
					Room4->ChangeAnimation("XHover");
					RoomX4 = true;
				}
				else if (true == RoomX4 && false == RoomO4 && IsDown(VK_LBUTTON))
				{
					Room4->ChangeAnimation("XDown");
					RoomX4 = true;
					RoomSwitch = true;
				}
				else if (true == RoomX4 && false == RoomO4 && IsUp(VK_LBUTTON))
				{
					IsSelectSharacter = false;
					Room4->ChangeAnimation("XUp");
					RoomX4 = false;
					RoomO4 = true;
				}
			}
			});
	}

	{
		Room5->SetUnHover([=] {
			if (true == RoomO5 && false == RoomSwitch && "UP" != Room5->GetUiAniName())
			{
				Room5->ChangeAnimation("UnHover");
				RoomO5 = true;
				RoomHoverChack = false;
			}
			else if (true == RoomX5 && "UP" == Room5->GetUiAniName())
			{
				Room5->ChangeAnimation("Up");
				RoomO5 = false;
				RoomX5 = true;
				RoomHoverChack = false;
			}
			});
		Room5->SetHover([=] {
			{
				if (true == RoomO5 && false == RoomSwitch && "UP" != Room5->GetUiAniName())
				{
					Room5->ChangeAnimation("Hover");
					RoomSwitch = true;

				}
				else if (IsDown(VK_LBUTTON) && true == RoomSwitch && true == RoomO5)
				{
					Room5->ChangeAnimation("Down");

				}
				else if (IsUp(VK_LBUTTON) && true == RoomO5)
				{
					IsSelectSharacter = false;
					Room5->ChangeAnimation("Up");
					RoomX5 = true;
					RoomSwitch = true;
					RoomO5 = false;
				}
				else if (false == RoomSwitch && true == RoomX5 && false == RoomO5 && "UP" == Room5->GetUiAniName())
				{
					Room5->ChangeAnimation("XHover");
					RoomX5 = true;
				}
				else if (true == RoomX5 && false == RoomO5 && IsDown(VK_LBUTTON))
				{
					Room5->ChangeAnimation("XDown");
					RoomX5 = true;
					RoomSwitch = true;
				}
				else if (true == RoomX5 && false == RoomO5 && IsUp(VK_LBUTTON))
				{
					IsSelectSharacter = false;
					Room5->ChangeAnimation("XUp");
					RoomX5 = false;
					RoomO5 = true;
				}
			}
			});
	}

	{
		Room6->SetUnHover([=] {
			if (true == RoomO6 && false == RoomSwitch && "UP" != Room6->GetUiAniName())
			{
				Room6->ChangeAnimation("UnHover");
				RoomO6 = true;
				RoomHoverChack = false;
			}
			else if (true == RoomX6 && "UP" == Room6->GetUiAniName())
			{
				Room6->ChangeAnimation("Up");
				RoomO6 = false;
				RoomX6 = true;
				RoomHoverChack = false;
			}
			});
		Room6->SetHover([=] {
			{
				if (true == RoomO6 && false == RoomSwitch && "UP" != Room6->GetUiAniName())
				{
					Room6->ChangeAnimation("Hover");
					RoomSwitch = true;

				}
				else if (IsDown(VK_LBUTTON) && true == RoomSwitch && true == RoomO6)
				{
					Room6->ChangeAnimation("Down");

				}
				else if (IsUp(VK_LBUTTON) && true == RoomO6)
				{
					IsSelectSharacter = false;
					Room6->ChangeAnimation("Up");
					RoomX6 = true;
					RoomSwitch = true;
					RoomO6 = false;
				}
				else if (false == RoomSwitch && true == RoomX6 && false == RoomO6 && "UP" == Room6->GetUiAniName())
				{
					Room6->ChangeAnimation("XHover");
					RoomX6 = true;
				}
				else if (true == RoomX6 && false == RoomO6 && IsDown(VK_LBUTTON))
				{
					Room6->ChangeAnimation("XDown");
					RoomX6 = true;
					RoomSwitch = true;
				}
				else if (true == RoomX6 && false == RoomO6 && IsUp(VK_LBUTTON))
				{
					IsSelectSharacter = false;
					Room6->ChangeAnimation("XUp");
					RoomX6 = false;
					RoomO6 = true;
				}
			}
			});
	}

	{
		Room7->SetUnHover([=] {
			if (true == RoomO7 && false == RoomSwitch && "UP" != Room7->GetUiAniName())
			{
				Room7->ChangeAnimation("UnHover");
				RoomO7 = true;
				RoomHoverChack = false;
			}
			else if (true == RoomX7 && "UP" == Room7->GetUiAniName())
			{
				Room7->ChangeAnimation("Up");
				RoomO7 = false;
				RoomX7 = true;
				RoomHoverChack = false;
			}
			});
		Room7->SetHover([=] {
			{
				if (true == RoomO7 && false == RoomSwitch && "UP" != Room7->GetUiAniName())
				{
					Room7->ChangeAnimation("Hover");
					RoomSwitch = true;

				}
				else if (IsDown(VK_LBUTTON) && true == RoomSwitch && true == RoomO7)
				{
					Room7->ChangeAnimation("Down");

				}
				else if (IsUp(VK_LBUTTON) && true == RoomO7)
				{
					IsSelectSharacter = false;
					Room7->ChangeAnimation("Up");
					RoomX7 = true;
					RoomSwitch = true;
					RoomO7 = false;
				}
				else if (false == RoomSwitch && true == RoomX7 && false == RoomO7 && "UP" == Room7->GetUiAniName())
				{
					Room7->ChangeAnimation("XHover");
					RoomX7 = true;
				}
				else if (true == RoomX7 && false == RoomO7 && IsDown(VK_LBUTTON))
				{
					Room7->ChangeAnimation("XDown");
					RoomX7 = true;
					RoomSwitch = true;
				}
				else if (true == RoomX7 && false == RoomO7 && IsUp(VK_LBUTTON))
				{
					IsSelectSharacter = false;
					Room7->ChangeAnimation("XUp");
					RoomX7 = false;
					RoomO7 = true;
				}
			}
			});
	}
}

void APlayLobby::CharacterBegin()
{
	{
		RandomBT->SetUnHover([=] {
			if ("UP" != RandomBT->GetUiAniName())
			{
				RandomBT->ChangeAnimation("UnHover");
			}
			SwitchON = false;
			});
		RandomBT->SetHover([=] {
			{
				if (false == SwitchON && "UP" != RandomBT->GetUiAniName())
				{
					RandomBT->ChangeAnimation("Hover");
					SwitchON = true;
				}
				else if (IsDown(VK_LBUTTON) && true == SwitchON)
				{
					RandomBT->ChangeAnimation("Down");
				}
				else if (IsUp(VK_LBUTTON))
				{
					LobbyCharacterBanner->SetSprite("CharatorSelect_Outline_Random.bmp");
					SwapSelectCharacter(RandomBT);
					LobbyPlayer[PlayerCount]->SetSprite("RandomCha.png");
					checkUI->SetPosition({ 152.0f,183.0f });
					checkUI->SetActive(true);
					ConstValue::MainPlayerCharacterType = ECharacterType::Random;
				}
			}
			});
	}

	{
		DaoBT->SetUnHover([=] {
			if ("UP" != DaoBT->GetUiAniName())
			{
				DaoBT->ChangeAnimation("UnHover");
			}
			SwitchON = false;
			});
		DaoBT->SetHover([=] {
			{
				if (false == SwitchON && "UP" != DaoBT->GetUiAniName())
				{
					DaoBT->ChangeAnimation("Hover");
					SwitchON = true;
				}
				else if (IsDown(VK_LBUTTON) && true == SwitchON)
				{
					DaoBT->ChangeAnimation("Down");
				}
				else if (IsUp(VK_LBUTTON))
				{
					IsSelectSharacter = true;
					SwapSelectCharacter(DaoBT);
					LobbyPlayer[ChangeUIIndex]->SetSprite("Room_Charcater_Dao.png");

					if (nullptr != ChracterChangeLogic)
					{
						ChracterChangeLogic(this, ChangeUIIndex, "Room_Charcater_Dao.png");
					}
					int a = 0;
					LobbyCharacterBanner->SetSprite("CharatorSelect_Outline_Dao.bmp");
					checkUI->SetPosition({ 222.0f,183.0f });
					checkUI->SetActive(true);
					ConstValue::MainPlayerCharacterType = ECharacterType::Dao;
				}
			}
			});
	}
	{
		MaridBT->SetUnHover([=] {
			if ("UP" != MaridBT->GetUiAniName())
			{
				MaridBT->ChangeAnimation("UnHover");
			}
			SwitchON = false;
			});
		MaridBT->SetHover([=] {
			{
				if (false == SwitchON && "UP" != MaridBT->GetUiAniName())
				{
					MaridBT->ChangeAnimation("Hover");
					SwitchON = true;
				
		
				}
				else if (IsDown(VK_LBUTTON) && true == SwitchON)
				{
					MaridBT->ChangeAnimation("Down");

				}
				else if (IsUp(VK_LBUTTON))
				{
					IsSelectSharacter = true;
					SwapSelectCharacter(MaridBT);
					LobbyPlayer[ChangeUIIndex]->SetSprite("Room_Charcater_Marid.png");
					if (nullptr != ChracterChangeLogic)
					{
						ChracterChangeLogic(this, ChangeUIIndex, "Room_Charcater_Marid.png");
					}
					int a = 0;
					LobbyCharacterBanner->SetSprite("CharatorSelect_Outline_Marid.bmp");
					checkUI->SetPosition({ 222.0f,133.0f });
					checkUI->SetActive(true);
					ConstValue::MainPlayerCharacterType = ECharacterType::Marid;
				}
			}
			});
	}
	{
		BazziBT->SetUnHover([=] {
			if ("UP" != BazziBT->GetUiAniName())
			{
				BazziBT->ChangeAnimation("UnHover");
			}
			SwitchON = false;
			});
		BazziBT->SetHover([=] {
			{
				if (false == SwitchON && "UP" != BazziBT->GetUiAniName())
				{
					BazziBT->ChangeAnimation("Hover");
					SwitchON = true;

				}
				else if (IsDown(VK_LBUTTON) && true == SwitchON)
				{
					BazziBT->ChangeAnimation("Down");

				}
				else if (IsUp(VK_LBUTTON))
				{
					IsSelectSharacter = true;
					SwapSelectCharacter(BazziBT);
					LobbyPlayer[ChangeUIIndex]->SetSprite("Room_Charcater_Bazzi.png");

					if (nullptr != ChracterChangeLogic)
					{
						ChracterChangeLogic(this, ChangeUIIndex, "Room_Charcater_Bazzi.png");
					}
					int a = 0;
					LobbyCharacterBanner->SetSprite("CharatorSelect_Outline_Bazzi.bmp");
					checkUI->SetPosition({ 292.0f,133.0f });
					checkUI->SetActive(true);
					ConstValue::MainPlayerCharacterType = ECharacterType::Bazzi;				
				}
			}
		});
	}
}

void APlayLobby::StartBegin()
{
	{
		GameStart->SetUnHover([=] {
			GameStart->ChangeAnimation("UnHover");
			SwitchON = false;
			});
		GameStart->SetHover([=] {
			if (GameStart->IsCurAnimationEnd() == true)
			{
				GameStart->ChangeAnimation("Hover");
			}
			});
		GameStart->SetDown([=] {
			GameStart->ChangeAnimation("Down");
			//GEngine->ChangeLevel("PlayertestMode");
			GEngine->ChangeLevel("MainGameMode");
			});
	}
}

void APlayLobby::MapSelectButtonBegin()
{
	{
		SelectMap->SetUnHover([=] {
			SelectMap->ChangeAnimation("UnHover");
			SwitchON = false;
			});
		SelectMap->SetHover([=] {
			if (SelectMap->IsCurAnimationEnd() == true)
			{
				SelectMap->ChangeAnimation("Hover");
			}
			else if (true == IsDown(VK_LBUTTON) && "Hover" == SelectMap->GetUiAniName())
			{
				SelectMap->ChangeAnimation("Down");
			}
			else if (true == IsUp(VK_LBUTTON))
			{
				MapSelectBegin();
			}
			});

	}
}

void APlayLobby::LobbyPlayerBegin()
{
	LobbyPlayer[0] = CreateWidget<UImage>(GetWorld(), "LobbyPlayer");
	LobbyPlayer[0]->AddToViewPort(15);
	LobbyPlayer[0]->SetSprite("Room_Charcater_Dao.png");
	LobbyPlayer[0]->SetAutoSize(1.2f, true);
	LobbyPlayer[0]->AddPosition(FVector(static_cast<float>(-335 + PlayerCount * 105), 160.0f, 100.0f));

	Rank[0] = CreateWidget<UImage>(GetWorld(), "Rank");;
	Rank[0]->AddToViewPort(15);
	Rank[0]->SetSprite("CharacterRoom_Flag.png");
	Rank[0]->SetAutoSize(1.0f, true);
	Rank[0]->AddPosition(FVector(static_cast<float>(-300 + PlayerCount * 105), 145.0f, 100.0f));


	//if (IsDown('P') && 3 >= PlayerCount)
	//{
	//	LobbyPlayer[PlayerCount] = CreateWidget<UImage>(GetWorld(), "LobbyPlayer");
	//	LobbyPlayer[PlayerCount]->AddToViewPort(15);
	//	LobbyPlayer[PlayerCount]->SetSprite("bazzi_idle.png", 1);
	//	LobbyPlayer[PlayerCount]->SetScale({ 150, 150 });
	//	LobbyPlayer[PlayerCount]->AddPosition(FVector(static_cast<float>(-330 + PlayerCount * 105), 125.0f, 100.0f));

	//	Rank[PlayerCount] = CreateWidget<UImage>(GetWorld(), "Rank");;
	//	Rank[PlayerCount]->AddToViewPort(15);
	//	Rank[PlayerCount]->SetSprite("CharacterRoom_Flag.png");
	//	Rank[PlayerCount]->SetAutoSize(1.0f, true);
	//	Rank[PlayerCount]->AddPosition(FVector(static_cast<float>(-300 + PlayerCount * 105), 145.0f, 100.0f));

	//	++PlayerCount;
	//}

	//else if (IsDown('P') && 3 < PlayerCount)
	//{
	//	if (7 < PlayerCount)
	//	{
	//		return;
	//	}

	//	LobbyPlayer[PlayerCount] = CreateWidget<UImage>(GetWorld(), "LobbyPlayer");
	//	LobbyPlayer[PlayerCount]->AddToViewPort(15);
	//	LobbyPlayer[PlayerCount]->SetSprite("bazzi_idle.png", 1);
	//	LobbyPlayer[PlayerCount]->SetScale({ 150, 150 });
	//	LobbyPlayer[PlayerCount]->AddPosition(FVector(static_cast<float>(-750 + PlayerCount * 105), -20.0f, 100.0f));

	//	Rank[PlayerCount] = CreateWidget<UImage>(GetWorld(), "Rank");;
	//	Rank[PlayerCount]->AddToViewPort(15);
	//	Rank[PlayerCount]->SetSprite("CharacterRoom_Flag.png");
	//	Rank[PlayerCount]->SetAutoSize(1.0f, true);
	//	Rank[PlayerCount]->AddPosition(FVector(static_cast<float>(-720 + PlayerCount * 105), 0.0f, 100.0f));
	//	++PlayerCount;
	//}
}

void APlayLobby::MapSelectBegin()
{
	MapSelect->SetActive(true);
	MapSelectVName->SetActive(true);
	MapSelectVTitle->SetActive(true);
	MapSelectVPick->SetActive(true);
	MapSelectCName->SetActive(true);
	MapSelectVinfo->SetActive(true);

	MapSelectCName->SetHover([=] {
		if (true == IsUp(VK_LBUTTON))
		{
			MapSelectCPick->SetActive(true);
			MapSelectVPick->SetActive(false);
			MapSelectCTitle->SetActive(true);
			MapSelectCMinimap->SetActive(true);
			MapSelectVinfo->SetActive(false);
		}
		});

	MapSelectVName->SetHover([=] {
		if (true == IsUp(VK_LBUTTON))
		{
			MapSelectCPick->SetActive(false);
			MapSelectVPick->SetActive(true);
			MapSelectCTitle->SetActive(false);
			MapSelectCMinimap->SetActive(false);
			MapSelectVinfo->SetActive(true);
		}
		});
	
}

void APlayLobby::SwapSelectCharacter(UImage* _SelectCharacter)
{
	SelectCharacter->ChangeAnimation("UnHover");
	_SelectCharacter->ChangeAnimation("Up");
	SelectCharacter = _SelectCharacter;
}

void APlayLobby::SwapTeamSelectCharacter(UImage* _SelectTeam)
{
	SelectTeam->ChangeAnimation("TeamUnHover");
	_SelectTeam->ChangeAnimation("TeamUp");
	SelectTeam = _SelectTeam;
}

void APlayLobby::SetIsActive(bool _Active)
{
	PlayLobbyUI->SetActive(_Active);
}



