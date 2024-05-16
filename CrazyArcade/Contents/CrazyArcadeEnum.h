#pragma once

enum class ERenderOrder
{
	BackGround,
	Shadow
};

// 0 ~ 999 (ĳ���� Ÿ��)
enum class ECharacterType
{
	Random,
	Dao,
	Dizni,
	Mos,
	Ethi,
	Marid,
	Bazzi,
	Uni,
	Kephi,
	Su,
	HooU,
	Ray
};

// 1000 ~ 1999 (�� ��� Ÿ��)
enum class EBlockType
{
	Wall = 1000,
	Box,
	MoveBox
};

// 2000 ~ 2999 (������ Ÿ��)
enum class EPlayerItem
{
	None = 2000,
	Bubble,
	Devil,
	Fluid,
	Glove,
	RedDevil,
	Roller,
	Shoes,
	Ultra
};