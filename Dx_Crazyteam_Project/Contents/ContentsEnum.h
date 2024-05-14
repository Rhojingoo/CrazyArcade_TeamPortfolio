#pragma once

enum class EObjectOrder
{
	None,
	Background,
	Map,
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

enum class ERenderOrder
{
	Back,
	Player,
	Test,
};

enum class EMapObjectType {
	None,
	Block,   //���������� �μ������� �ʴ� ��� / ��ǳ��
	BrakableBlock,   //�μ����� ���
	MoveBlock,     //�����̴� ���
	Bush,          //�ν�
	Water,  //��ǳ��
};

enum class EMapObject
{
	NormalBlock,
	CampBlock,
	WaterBomb,
};

enum class ECharacterType
{
	None,
	Bazzi,
	Dao,
	Marid,
};