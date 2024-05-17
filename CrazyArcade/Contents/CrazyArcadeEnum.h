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
	UnderBlock
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

enum class ECharacterColor
{
	Red,
	Yellow,
	Orange,
	Green,
	Skyblue,
	Blue,
	Purple,
	Pink
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