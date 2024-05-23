#include "PreCompile.h"
#include "Intro.h"
#include "PlayLobby.h"
#include "EngineCore/Image.h"

#include "ServerGameMode.h"

AIntro::AIntro()
{

}

AIntro::~AIntro()
{
}

void AIntro::BeginPlay()
{
	Super::BeginPlay();
	InputOn();
	ServerGameMode = dynamic_cast<AServerGameMode*>(GetWorld()->GetGameMode().get());

	IntroUI = CreateWidget<UImage>(GetWorld(), "IntroUser");
	IntroUI->CreateAnimation("IntroUser", "IntroUser", 0.1f, false ,0 , 19);
	IntroUI->CreateAnimation("IntroNexen", "IntroUser", 0.1f, false, 20, 92);
	IntroUI->SetAutoSize(1.0f, true);
	IntroUI->AddToViewPort(10);
	IntroUI->SetActive(false);

	IntroUI->ChangeAnimation("IntroUser");

	StartUI = CreateWidget<UImage>(GetWorld(), "StartUI");
	StartUI->SetSprite("first_bge.png");
	StartUI->SetAutoSize(1.0f, true);
	StartUI->AddToViewPort(10);
	StartUI->SetActive(true);

	TextInputUI = CreateWidget<UImage>(GetWorld(), "TextInputUI");
	TextInputUI->SetSprite("Button_Start_2_1_11zon.png");
	TextInputUI->SetAutoSize(1.0f, true);
	TextInputUI->AddToViewPort(11);
	TextInputUI->SetPosition(FVector(0.0f, -50.0f, 0.0f));
	TextInputUI->SetActive(true);
	
	GameStartButton = CreateWidget<UImage>(GetWorld(), "TitleBackGround");
	GameStartButton->AddToViewPort(11);
	GameStartButton->SetSprite("Button_Start_2_1_11zon.png");
	GameStartButton->SetAutoSize(1.0f, true);
	GameStartButton->SetPosition(FVector(0.0f, -100.0f, 0.0f));
	GameStartButton->SetActive(true);

	TextInputUI->SetHover([=] 
		{
			if (IsDown(VK_LBUTTON))
			{
				// �Է� ���� ����
			}
		});

	GameStartButton->SetHover([=]
		{
			GameStartButton->SetSprite("Button_Start_1_2_11zon.png");

			if (IsDown(VK_LBUTTON))
			{
				//ServerGameMode->GetPlayLobby()->SetIsActive(true);

				AServerGameMode::ServerOpen();

			
				//GEngine->ChangeLevel("");

				//if (nullptr == Function)
				//{
				//	return;
				//}

				//Function();
			}
		});

	TextInputUI->SetUnHover([=]
		{
			if (IsDown(VK_LBUTTON))
			{
				// �Է� �Ұ��� ����
			}
		});

	GameStartButton->SetUnHover([=]
		{
			GameStartButton->SetSprite("Button_Start_2_1_11zon.png");
		});
}

void AIntro::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == AServerGameMode::GetIsServerOpen())
	{
		GEngine->ChangeLevel("LobbyMainMode");
		return;
	}

	if (true == IntroUI->IsCurAnimationEnd())
	{
		IntroUI->ChangeAnimation("IntroNexen");
		if (true == IntroUI->IsCurAnimationEnd())
		{
			IntroUI->SetActive(false);
			StartUI->SetActive(true);
			GameStartButton->SetActive(true);
		}
	}
	


}
