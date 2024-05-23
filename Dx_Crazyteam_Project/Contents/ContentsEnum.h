#pragma once

enum class ERenderOrder
{
	None,
	Background,
	Map,
	Shadow,
	Item,
	BlockFront,
	Player,
	BlockBack,
	WaterBomb,
	UI,
};

enum class ECollisionOrder
{
	Player,
	Monster,
};

enum class EMapObjectType {
	None,
	Block,   //���������� �μ������� �ʴ� ��� / ��ǳ��
	Bush,          //�ν�
	Water,  //���ٱ�
	WaterBalloon, // ��ǳ��
	Item,
};

enum class EMapObject
{
	Default,
	WaterBomb,
	Water,
	Item,
	TownBush,

	DummyBlock,
	NormalBlock,
	CampBlock1,
	CampBlock2,
	CampBlock3,
	CampBlock4,
	CampMoveBlock1,
	CampMoveBlock2,
	CampHPBlock,

	VillageBlock1,
	VillageBlock2,
	VillageMoveBlock,
	VillageTree,
	VillageBlueHouse,
	VillageRedHouse,
	VillageYellowHouse,
};

enum class EItemType
{
	None,
	ItemBubble,	// ���� + 1 ������
	ItemFluid,	// �ٱ� + 1 ������
	ItemRoller,	// �ӵ� + 1 ������
	ItemOwl,    // �ӵ� ����6 ������
	ItemTurtle,	// �ӵ� ����1 ������	
	ItemNiddle, // Trap ���¿��� Rescue ������ִ� ������
	ItemShoes,  // ��ǳ�� kick ������
};


enum class EGimmickType
{
	None,
	Thorn,
	Drain,
};

enum class ECharacterType
{
	None,
	Random,
	Bazzi,
	Dao,
	Marid,
};

enum class ECADir
{
	None,
	Right,
	Left,
	Up,
	Down,
};

enum class ETeamType
{
	None,
	ATeam,
	BTeam,
};

enum class EPlayerRideType
{
	None,
	Owl,
	Turtle,
};

enum class EMap
{
	Camp,
	Village,
};

enum class EGameResult
{
	None,
	ATeamWin,
	BTeamWin,
	Draw,
};