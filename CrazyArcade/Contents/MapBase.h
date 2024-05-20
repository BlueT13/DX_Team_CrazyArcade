#pragma once
#include "MapHelper.h"

class ABlockBase;
class ABombBase;
class AMoveBox;
class ABushBase;
class AItemBase;
class UTileInfo;
class APlayer;
class AWave;
class ABox;

// Tile ����
class UTileInfo
{
public:
	ABlockBase* Block = nullptr;
	ABushBase* Bush = nullptr;
	AItemBase* Item = nullptr;
	ABombBase* Bomb = nullptr;
};

// ���� : Map ���� Ŭ����
class AMapBase : public AActor
{
	GENERATED_BODY(AActor)

	friend ABombBase;
	friend AMoveBox;
	friend AWave;
public:
	// constrcuter destructer
	AMapBase();
	~AMapBase();

	// delete Function
	AMapBase(const AMapBase& _Other) = delete;
	AMapBase(AMapBase&& _Other) noexcept = delete;
	AMapBase& operator=(const AMapBase& _Other) = delete;
	AMapBase& operator=(AMapBase&& _Other) noexcept = delete;

	static int GetRenderOrder(const FVector& _Pos);
	static FPoint ConvertLocationToPoint(const FVector& _Pos);
	static FVector ConvertPointToLocation(FPoint _Point);
	static bool MapRangeCheckByPoint(FPoint _Point);
	
	bool CanMovePos(const FVector& _NextPos, const FVector& _Dir);
	EItemType IsItemTile(const FVector& _Pos);
	ABombBase* SpawnBomb(const FVector& _Pos, APlayer* _Player);
	
	// Tile�� �Ѻ��� ���̸� ��ȯ
	static float GetBlockSize()
	{
		return BlockSize;
	}

	// �ش� ��ǥ Tile�� ����� ��ȯ
	ABlockBase* GetMapBlock(FPoint _Point) const
	{
		return TileInfo[_Point.Y][_Point.X].Block;
	}

	// �ش� ��ǥ Tile�� ����� ����
	void SetMapBlock(FPoint _Point, ABlockBase* _Block)
	{
		TileInfo[_Point.Y][_Point.X].Block = _Block;
	}
		
	// �ش� ��ǥ Tile�� ����� ����
	void SetMapBomb(FPoint _Point, ABombBase* _Bomb)
	{
		TileInfo[_Point.Y][_Point.X].Bomb = _Bomb;
	}

protected:
	inline void SetBackGround(std::string_view _Name)
	{
		BackGround->SetSprite(_Name);
	}

	void SetMapInfoSize(int _SizeX, int _SizeY);
	void CreateWall(FPoint _Point, std::string_view _ImgName);
	void CreateBox(FPoint _Point, std::string_view _ImgName);
	void CreateMoveBox(FPoint _Point, std::string_view _ImgName);
	void CreateBush(FPoint _Point, std::string_view _ImgName);
	void CreateHollowWall(FPoint _Point);
	void CreateItem(FPoint _Point, EItemType _ItemType);

private:
	// �ش� ��ǥ�� Tile ������ ������ ��ȯ
	UTileInfo& GetTileInfo(FPoint _Point)
	{
		return TileInfo[_Point.Y][_Point.X];
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel) override;

private:
	USpriteRenderer* BackGround = nullptr;
	USpriteRenderer* PlayUI_BackGround = nullptr;

	std::vector<std::vector<UTileInfo>> TileInfo;

	static FVector StartPos;
	static float BlockSize;
	static int SizeX;
	static int SizeY;

	static float BombAdjustPosY;

};

