#pragma once

class ABlockBase;
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

	FPoint CovertLocationToPoint(const FVector& _Pos);
	
	int GetRenderOrder(const FVector& _CurPos);
	
	bool CanMovePos(const FVector& _NextPos, const FVector& _Dir);
	
	static float GetBlockSize()
	{
		return BlockSize;
	}

	std::shared_ptr<ABlockBase> GetMapBlock(FPoint _Point) const
	{
		return MapInfo[_Point.Y][_Point.X].Block;
	}

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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* BackGround = nullptr;
	USpriteRenderer* PlayUI_BackGround = nullptr;

	std::vector<std::vector<UTileInfo>> MapInfo;

	FVector StartPos = { 20.0f, 40.0f, 0.0f };
	static float BlockSize;
	int SizeX = 0;
	int SizeY = 0;

};

