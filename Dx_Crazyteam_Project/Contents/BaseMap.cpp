#include "PreCompile.h"
#include "BaseMap.h"
#include <EngineCore/DefaultSceneComponent.h>

const FVector ABaseMap::TileSize = FVector(40.f, 40.f, 10.f);

const int ABaseMap::TileY = 13;
const int ABaseMap::TileX = 15;


ABaseMap::ABaseMap()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	SetRoot(Root);
}

ABaseMap::~ABaseMap()
{
}

bool ABaseMap::IsMove(FVector _PlayerPos)
{
	if (_PlayerPos.X > - 80.f + TileSize.X / 2.f * TileX ||
		_PlayerPos.X < -80.f + TileSize.X / 2.f * (-TileX))
	{
		return false;
	}

	if (_PlayerPos.Y > TileSize.Y / 2.f * TileY ||
		_PlayerPos.Y < TileSize.Y / 2.f * (-TileY))
	{
		return false;
	}




	return true;
}

void ABaseMap::BeginPlay()
{
	Super::BeginPlay();

	for (int y = 0; y < TileY; y++)
	{
		std::vector<AMapObject*> Temp;
		MapStatus.push_back(Temp);
		for (int x = 0; x < TileX; x++)
		{
			MapStatus[y].push_back(nullptr);
		}
	}

}

void ABaseMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}


//1.
// Plaery�� ��ǳ���� ��ġ�� ��,
// Power���� ��ǳ���� �ְ�,
// Map�� ��ǳ���� �ִ� Power���� ������ ���ٱ⸦ ǥ���Ѵ�.
//2.
// Player�� ��ǳ���� ��ġ�� ��,
// Power���� Map�� �ְ�.
// Map�� �� ������ ���ٱ⸦ ǥ���Ѵ�.
void ABaseMap::GetWaterWavePoint()
{

}
