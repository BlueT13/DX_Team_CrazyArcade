#include "PreCompile.h"
#include "ForestMap.h"
#include "MapConstant.h"

#include "Box.h"

AForestMap::AForestMap()
{
}

AForestMap::~AForestMap()
{
}

void AForestMap::BeginPlay()
{
	Super::BeginPlay();

	SetBackGround(MapImgRes::Forest_background);
	SetMapInfoSize(15, 13);
}

void AForestMap::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	CreateHouses();
	CreateTrees();
	CreateVillageBoxs();
	CreateVillageMoveBoxs();
	CreateItems();
	CreateHollowWall({ 0, 7 });
}

void AForestMap::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void AForestMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AForestMap::CreateHouses()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			CreateWall({ 2 * i, 2 * j }, MapImgRes::block_vil_house_1);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			CreateWall({ 10 + 2 * i, 8 + 2 * j }, MapImgRes::block_vil_house_2);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			CreateWall({ 1 + 2 * i, 7 + 2 * j }, MapImgRes::block_vil_house_0);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			CreateWall({ 11 + 2 * i, 1 + 2 * j }, MapImgRes::block_vil_house_0);
		}
	}
}

void AForestMap::CreateTrees()
{
	CreateWall({ 0,  6 }, MapImgRes::block_vil_tree_0);
	CreateWall({ 2,  6 }, MapImgRes::block_vil_tree_0);
	CreateWall({ 4,  6 }, MapImgRes::block_vil_tree_0);
	CreateWall({ 5,  1 }, MapImgRes::block_vil_tree_0);
	CreateWall({ 5,  3 }, MapImgRes::block_vil_tree_0);
	CreateWall({ 5,  7 }, MapImgRes::block_vil_tree_0);
	CreateWall({ 5,  9 }, MapImgRes::block_vil_tree_0);
	CreateWall({ 5, 11 }, MapImgRes::block_vil_tree_0);
	CreateWall({ 9,  1 }, MapImgRes::block_vil_tree_0);
	CreateWall({ 9,  3 }, MapImgRes::block_vil_tree_0);
	CreateWall({ 9,  5 }, MapImgRes::block_vil_tree_0);
	CreateWall({ 9,  9 }, MapImgRes::block_vil_tree_0);
	CreateWall({ 9, 11 }, MapImgRes::block_vil_tree_0);
	CreateWall({ 10,  6 }, MapImgRes::block_vil_tree_0);
	CreateWall({ 12,  6 }, MapImgRes::block_vil_tree_0);
	CreateWall({ 14,  6 }, MapImgRes::block_vil_tree_0);
}

void AForestMap::CreateVillageBoxs()
{
	CreateBox({ 0,  3 }, MapImgRes::block_vil_box2);
	CreateBox({ 0,  7 }, MapImgRes::block_vil_box2);
	CreateBox({ 1,  5 }, MapImgRes::block_vil_box2);
	CreateBox({ 1,  8 }, MapImgRes::block_vil_box2);
	CreateBox({ 1, 12 }, MapImgRes::block_vil_box2);
	CreateBox({ 2,  3 }, MapImgRes::block_vil_box2);
	CreateBox({ 2,  7 }, MapImgRes::block_vil_box2);
	CreateBox({ 2, 10 }, MapImgRes::block_vil_box2);
	CreateBox({ 3,  1 }, MapImgRes::block_vil_box2);
	CreateBox({ 3,  5 }, MapImgRes::block_vil_box2);
	CreateBox({ 3,  8 }, MapImgRes::block_vil_box2);
	CreateBox({ 3, 12 }, MapImgRes::block_vil_box2);
	CreateBox({ 4,  3 }, MapImgRes::block_vil_box2);
	CreateBox({ 4,  7 }, MapImgRes::block_vil_box2);
	CreateBox({ 4, 10 }, MapImgRes::block_vil_box2);
	CreateBox({ 10,  0 }, MapImgRes::block_vil_box2);
	CreateBox({ 10,  4 }, MapImgRes::block_vil_box2);
	CreateBox({ 10,  9 }, MapImgRes::block_vil_box2);
	CreateBox({ 11,  2 }, MapImgRes::block_vil_box2);
	CreateBox({ 11,  7 }, MapImgRes::block_vil_box2);
	CreateBox({ 11, 11 }, MapImgRes::block_vil_box2);
	CreateBox({ 12,  0 }, MapImgRes::block_vil_box2);
	CreateBox({ 12,  4 }, MapImgRes::block_vil_box2);
	CreateBox({ 12,  9 }, MapImgRes::block_vil_box2);
	CreateBox({ 13,  2 }, MapImgRes::block_vil_box2);
	CreateBox({ 13,  7 }, MapImgRes::block_vil_box2);
	CreateBox({ 14,  4 }, MapImgRes::block_vil_box2);
	CreateBox({ 14,  9 }, MapImgRes::block_vil_box2);

	CreateBox({ 0,  5 }, MapImgRes::block_vil_box1);
	CreateBox({ 0,  8 }, MapImgRes::block_vil_box1);
	CreateBox({ 1,  3 }, MapImgRes::block_vil_box1);
	CreateBox({ 2,  1 }, MapImgRes::block_vil_box1);
	CreateBox({ 2,  3 }, MapImgRes::block_vil_box1);
	CreateBox({ 2,  5 }, MapImgRes::block_vil_box1);
	CreateBox({ 2,  8 }, MapImgRes::block_vil_box1);
	CreateBox({ 2, 12 }, MapImgRes::block_vil_box1);
	CreateBox({ 3,  0 }, MapImgRes::block_vil_box1);
	CreateBox({ 3,  3 }, MapImgRes::block_vil_box1);
	CreateBox({ 3, 10 }, MapImgRes::block_vil_box1);
	CreateBox({ 4,  1 }, MapImgRes::block_vil_box1);
	CreateBox({ 4,  5 }, MapImgRes::block_vil_box1);
	CreateBox({ 4,  8 }, MapImgRes::block_vil_box1);
	CreateBox({ 4, 12 }, MapImgRes::block_vil_box1);
	CreateBox({ 10,  2 }, MapImgRes::block_vil_box1);
	CreateBox({ 10,  5 }, MapImgRes::block_vil_box1);
	CreateBox({ 10,  7 }, MapImgRes::block_vil_box1);
	CreateBox({ 10, 11 }, MapImgRes::block_vil_box1);
	CreateBox({ 11,  0 }, MapImgRes::block_vil_box1);
	CreateBox({ 11,  4 }, MapImgRes::block_vil_box1);
	CreateBox({ 11,  9 }, MapImgRes::block_vil_box1);
	CreateBox({ 11, 12 }, MapImgRes::block_vil_box1);
	CreateBox({ 12,  2 }, MapImgRes::block_vil_box1);
	CreateBox({ 12,  5 }, MapImgRes::block_vil_box1);
	CreateBox({ 12,  7 }, MapImgRes::block_vil_box1);
	CreateBox({ 13,  4 }, MapImgRes::block_vil_box1);
	CreateBox({ 13,  9 }, MapImgRes::block_vil_box1);
	CreateBox({ 14,  5 }, MapImgRes::block_vil_box1);
	CreateBox({ 14,  7 }, MapImgRes::block_vil_box1);
}

void AForestMap::CreateVillageMoveBoxs()
{
	CreateMoveBox({ 0,  9 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 1,  4 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 2,  9 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 2, 11 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 3,  2 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 3,  4 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 4,  9 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 4, 11 }, MapImgRes::block_vil_box0);
	//CreateMoveBox({  6,  1 }, MapImgRes::block_vil_box0);
	//CreateMoveBox({  6,  3 }, MapImgRes::block_vil_box0);
	//CreateMoveBox({  6,  5 }, MapImgRes::block_vil_box0);
	//CreateMoveBox({  6,  7 }, MapImgRes::block_vil_box0);
	//CreateMoveBox({  6,  9 }, MapImgRes::block_vil_box0);
	//CreateMoveBox({  6, 11 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 7,  1 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 7,  4 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 7,  7 }, MapImgRes::block_vil_box0);
	//CreateMoveBox({  7, 10 }, MapImgRes::block_vil_box0);
	//CreateMoveBox({  8,  0 }, MapImgRes::block_vil_box0);
	//CreateMoveBox({  8,  2 }, MapImgRes::block_vil_box0);
	//CreateMoveBox({  8,  4 }, MapImgRes::block_vil_box0);
	//CreateMoveBox({  8,  6 }, MapImgRes::block_vil_box0);
	//CreateMoveBox({  8,  8 }, MapImgRes::block_vil_box0);
	//CreateMoveBox({  8, 10 }, MapImgRes::block_vil_box0);
	//CreateMoveBox({  8, 12 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 10,  1 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 10,  3 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 11,  8 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 11, 10 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 12,  1 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 12,  3 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 13,  8 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 13, 10 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 14,  3 }, MapImgRes::block_vil_box0);
}

void AForestMap::CreateItems()
{
	CreateItem({ 6, 1 }, EItemType::Bubble);
	CreateItem({ 6, 3 }, EItemType::Devil);
	CreateItem({ 6, 5 }, EItemType::Fluid);
	CreateItem({ 6, 7 }, EItemType::Glove);
	CreateItem({ 8, 1 }, EItemType::RedDevil);
	CreateItem({ 8, 3 }, EItemType::Roller);
	CreateItem({ 8, 5 }, EItemType::Shoes);
	CreateItem({ 8, 7 }, EItemType::Ultra);
}