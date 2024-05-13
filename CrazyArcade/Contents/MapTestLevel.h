#pragma once

class APlayer;
class AVillageMap;

// ���� : Map �׽�Ʈ ����
class AMapTestLevel : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	AMapTestLevel();
	~AMapTestLevel();

	// delete Function
	AMapTestLevel(const AMapTestLevel& _Other) = delete;
	AMapTestLevel(AMapTestLevel&& _Other) noexcept = delete;
	AMapTestLevel& operator=(const AMapTestLevel& _Other) = delete;
	AMapTestLevel& operator=(AMapTestLevel&& _Other) noexcept = delete;
		
	std::shared_ptr<AVillageMap> GetMap() const
	{
		return TileMap;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<AVillageMap> TileMap = nullptr;
	std::shared_ptr<APlayer> Player = nullptr;

};

