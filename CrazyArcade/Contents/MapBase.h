#pragma once
#include "MapHelper.h"

class ABlockBase;
class ABombBase;
class AItemBase;
class UTileInfo;
class APlayer;
class AWave;
class ABox;

// Tile ����
class UTileInfo
{
public:
	std::shared_ptr<ABlockBase> Block = nullptr;
	std::shared_ptr<AItemBase> Item = nullptr;
	std::shared_ptr<ABombBase> Bomb = nullptr;
};

// ���� : Map ���� Ŭ����
class AMapBase : public AActor
{
	GENERATED_BODY(AActor)

	friend ABombBase;
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
	static FVector ConvertPointToLocation(const FPoint& _Point);
	
	bool CanMovePos(const FVector& _NextPos, const FVector& _Dir);
	EItemType IsItemTile(const FVector& _Pos);
	ABombBase* SpawnBomb(const FVector& _Pos, APlayer* _Player);
	
	// Tile�� �Ѻ��� ���̸� ��ȯ
	static float GetBlockSize()
	{
		return BlockSize;
	}

	// �ش� ��ǥ Tile�� ����� ��ȯ
	std::shared_ptr<ABlockBase> GetMapBlock(FPoint _Point) const
	{
		return TileInfo[_Point.Y][_Point.X].Block;
	}

	// �ش� ��ǥ Tile�� ����� ����
	void SetMapBlock(FPoint _Point, std::shared_ptr<ABlockBase> _Block)
	{
		TileInfo[_Point.Y][_Point.X].Block = _Block;
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
	int SizeX = 0;
	int SizeY = 0;

	static float BombAdjustPosY;

};

