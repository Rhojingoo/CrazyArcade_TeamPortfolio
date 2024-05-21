#include "PreCompile.h"
#include "FontActor.h"

#include <EngineCore/TextWidget.h>
#include <EnginePlatform/TextimeInput.h>


AFontActor::AFontActor()
{
}

AFontActor::~AFontActor()
{
}

void AFontActor::BeginPlay()
{
	Super::BeginPlay();

	{//Text
		ShowText = CreateWidget<UTextWidget>(GetWorld(), "ShowText");
		ShowText->SetFont("���� ���");
		ShowText->SetScale(30.0f);
		ShowText->SetColor(Color8Bit::Black);
		ShowText->SetPosition({ -200.0f ,-100.0f });
		ShowText->SetFlag(FW1_LEFT);
		ShowText->AddToViewPort(11);
	}
#ifdef _DEBUG
	InputOn();
#endif

}

void AFontActor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == IsDown(VK_RETURN))
	{
		UTextimeInput::On();
	}

	std::string Text = UTextimeInput::GetReadText();
	if (Text.size() > 0)
	{
		ShowText->SetText(Text);
	}
	else
	{
		ShowText->SetText(" ");
	}

}
