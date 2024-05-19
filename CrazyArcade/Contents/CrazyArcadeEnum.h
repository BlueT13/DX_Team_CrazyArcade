#pragma once

enum class ERenderOrder
{
	BackGround,
	Shadow
};

enum class EMapType
{
	None,
	Village,
	Forest
};

enum class EWaveType
{
	Left,
	LeftEnd,
	Right,
	RightEnd,
	Up,
	UpEnd,
	Down,
	DownEnd,
	UnderBlock,
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
	Ray,
	None,
};

// 3000 ~ 3999 (�� Ÿ��)
enum class ECharacterColor
{
	Red = 3000,
	Yellow,
	Orange,
	Green,
	Skyblue,
	Blue,
	Purple,
	Pink,
	None,
};

// 1000 ~ 1999 (�� ��� Ÿ��)
enum class EBlockType
{
	Wall = 1000,
	Box,
	MoveBox
};

// 2000 ~ 2999 (������ Ÿ��)
enum class EItemType
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