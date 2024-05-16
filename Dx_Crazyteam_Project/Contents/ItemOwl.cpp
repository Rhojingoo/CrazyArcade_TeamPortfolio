#include "PreCompile.h"
#include "ItemOwl.h"
#include "Player.h"
#include "CAGameMode.h"
#include "BaseMap.h"

AItemOwl::AItemOwl()
{
	
}

AItemOwl::~AItemOwl()
{
}

void AItemOwl::BeginPlay()
{
	Super::BeginPlay();

	FrontRenderer->CreateAnimation("ItemOwl", "Owl.png", 0.3f, true, 0, 5);
	FrontRenderer->ChangeAnimation("ItemOwl");
	FrontRenderer->SetAutoSize(1.0f, true);

}

void AItemOwl::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}

void AItemOwl::Action()
{
	//�÷��̾� ���º���
	EPlayerRideType Type = GetGameMode()->GetPlayer()->GetPlayerInfo()->RideType;

	if (Type == EPlayerRideType::None)
	{
		GetGameMode()->GetPlayer()->GetPlayerInfo()->RideType = EPlayerRideType::Owl;
	}

	GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
}
