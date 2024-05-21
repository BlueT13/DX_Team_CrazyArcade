#pragma once
#include "MapHelper.h"

class AMainPlayLevel;
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
	std::shared_ptr<ABushBase> Bush = nullptr;
	std::shared_ptr<AItemBase> Item = nullptr;
	std::shared_ptr<ABombBase> Bomb = nullptr;
};

// ���� : Map ���� Ŭ����
class AMapBase : public AActor
{
	GENERATED_BODY(AActor)

	friend ABombBase;
	friend AMoveBox;
	friend ABox;
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

public:
	static int GetRenderOrder(const FVector& _Pos);
	static FPoint ConvertLocationToPoint(const FVector& _Pos);
	static FVector ConvertPointToLocation(FPoint _Point);
	static bool MapRangeCheckByPoint(FPoint _Point);
	
	// Tile�� �Ѻ��� ���̸� ��ȯ
	static float GetBlockSize()
	{
		return BlockSize;
	}

	// TileMap �� ���� ��ġ�� ��ȯ
	static FVector GetStartPos()
	{
		return StartPos;
	}

	bool CanMovePos(const FVector& _NextPos, const FVector& _Dir);
	bool IsBombPos(const FVector& _Pos, const FVector& _Dir);
	bool IsBushPos(const FVector& _Pos);
	EItemType IsItemTile(const FVector& _Pos);
	
	std::shared_ptr<ABombBase> SpawnBomb(const FVector& _Pos, APlayer* _Player);
	
protected:
	inline void SetBackGround(std::string_view _Name)
	{
		BackGround->SetSprite(_Name);
	}

	void SetMapInfoSize(int _SizeX, int _SizeY);
	void CreateWall(FPoint _Point, std::string_view _ImgName);
	void CreateAnimationWall(FPoint _Point, std::string_view _ImgName);
	void CreateBox(FPoint _Point, std::string_view _ImgName, EItemType _SpawnItemType = EItemType::None);
	void CreateMoveBox(FPoint _Point, std::string_view _ImgName, EItemType _SpawnItemType = EItemType::None);
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
	AMainPlayLevel* PlayLevel = nullptr;
	USpriteRenderer* BackGround = nullptr;
	USpriteRenderer* PlayUI_BackGround = nullptr;

	std::vector<std::vector<UTileInfo>> TileInfo;

	static FVector StartPos;
	static float BlockSize;
	static int SizeX;
	static int SizeY;

	static float BombAdjustPosY;
	

// Tile Check ����
private:
	void SetCheckPos(const FVector& _NextPos, const FVector& _Dir);

	bool SubMoveBoxCheck(FPoint _NextPoint, const FVector& _Dir);
	bool SubMoveBoxOnlyCheck(FPoint _NextPoint, const FVector& _Dir);

private:
	FVector NextPos = FVector::Zero;	// Main Pos
	FVector NextPos1 = FVector::Zero;	// Sub Pos1
	FVector NextPos2 = FVector::Zero;	// Sub Pos2

	FPoint NextPoint = { -1, -1 };		// Main Point
	FPoint NextPoint1 = { -1, -1 };		// Sub Point1
	FPoint NextPoint2 = { -1, -1 };		// Sub Point2

	const float BlockCheckAdjustPosX = 11.0f;
	const float BlockCheckAdjustPosY = 8.0f;

};

