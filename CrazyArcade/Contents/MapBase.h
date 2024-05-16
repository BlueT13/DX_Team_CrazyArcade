#pragma once

class ABlockBase;
class ABombBase;
class AItemBase;
class UTileInfo;
class ABox;

// Tile ��ǥ ����ü
struct FPoint
{
	int X;
	int Y;
};

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
public:
	// constrcuter destructer
	AMapBase();
	~AMapBase();

	// delete Function
	AMapBase(const AMapBase& _Other) = delete;
	AMapBase(AMapBase&& _Other) noexcept = delete;
	AMapBase& operator=(const AMapBase& _Other) = delete;
	AMapBase& operator=(AMapBase&& _Other) noexcept = delete;

	int GetRenderOrder(const FVector& _Pos);
	FPoint CovertLocationToPoint(const FVector& _Pos);
	bool CanMovePos(const FVector& _NextPos, const FVector& _Dir);
	EItemType IsItemTile(const FVector& _Pos);
	bool CreateBomb(const FVector& _Pos);
	
	// Tile�� �Ѻ��� ���̸� ��ȯ
	static float GetBlockSize()
	{
		return BlockSize;
	}

	// �ش� ��ǥ Tile�� ����� ��ȯ
	std::shared_ptr<ABlockBase> GetMapBlock(FPoint _Point) const
	{
		return MapInfo[_Point.Y][_Point.X].Block;
	}

	// �ش� ��ǥ Tile�� ����� ����
	void SetMapBlock(FPoint _Point, std::shared_ptr<ABlockBase> _Block)
	{
		MapInfo[_Point.Y][_Point.X].Block = _Block;
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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel) override;

private:
	USpriteRenderer* BackGround = nullptr;
	USpriteRenderer* PlayUI_BackGround = nullptr;

	std::vector<std::vector<UTileInfo>> MapInfo;

	FVector StartPos = { 20.0f, 40.0f, 0.0f };
	static float BlockSize;
	int SizeX = 0;
	int SizeY = 0;

};

