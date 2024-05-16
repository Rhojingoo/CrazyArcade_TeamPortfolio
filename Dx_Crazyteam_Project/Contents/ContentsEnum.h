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
	Water,  //��ǳ��
	WaterBalloon,
	Item,
};

enum class EItemType
{
	None,
	ItemBubble,	// ���� + 1 ������
	ItemFluid,	// �ٱ� + 1 ������
	ItemRoller,	// �ӵ� + 1 ������
	ItemOwl,    // �ӵ� ����6 ������
	ItemShoes,  // ��ǳ�� kick ������
	ItemNiddle, // Trap ���¿��� Rescue ������ִ� ������
};

enum class EMapObject
{
	Default,
	DummyBlock,
	NormalBlock,
	CampBlock,
	CampMoveBlock,
	WaterBomb,
	Water,
};

enum class ECharacterType
{
	None,
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