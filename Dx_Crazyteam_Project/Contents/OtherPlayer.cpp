#include "PreCompile.h"
#include "OtherPlayer.h"
#include <EngineCore/Collision.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "Game_Core.h"
#include "Packets.h"

AOtherPlayer::AOtherPlayer() 
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	USpriteRenderer* Ptr = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Ptr->SetupAttachment(Root);

	SetRoot(Root);

	SetActorScale3D({ 150.0f, 150.0f ,150.0f });
}

AOtherPlayer::~AOtherPlayer() 
{
}

void AOtherPlayer::BeginPlay()
{
	AActor::BeginPlay();
}

void AOtherPlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	if (nullptr == UGame_Core::Net)
	{
		MsgBoxAssert("��Ʈ��ũ ������ �ȵȻ��¿��� �ƴ��÷�� ��������ϴ�.");
	}

	// ������ ��Ŷ�� �°� �ִٸ� �ϳ� ������.
	// PopPacket();

}
