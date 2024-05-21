#pragma once
#include "NetGameMode.h"

class AVillageMap;

class AMapBase;
class ServerTestPlayer;

//UI
class ATimerUI;
class AInGameUI;

// ���� : Map �׽�Ʈ ����
class AMainPlayLevel : public ANetGameMode
{
	GENERATED_BODY(ANetGameMode)
public:
	// constrcuter destructer
	AMainPlayLevel();
	~AMainPlayLevel();

	// delete Function
	AMainPlayLevel(const AMainPlayLevel& _Other) = delete;
	AMainPlayLevel(AMainPlayLevel&& _Other) noexcept = delete;
	AMainPlayLevel& operator=(const AMainPlayLevel& _Other) = delete;
	AMainPlayLevel& operator=(AMainPlayLevel&& _Other) noexcept = delete;
		
	inline std::shared_ptr<AMapBase> GetMap() const
	{
		return TileMap;
	}

	inline std::shared_ptr<ServerTestPlayer> GetPlayer() const
	{
		return Player;
	}

	inline void SetMapType(EMapType _MapType)
	{
		MapType = _MapType;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel) override;
	void LevelStart(ULevel* _PrevLevel) override;

protected:
	void CreateMap();

protected:
	std::shared_ptr<AMapBase> TileMap = nullptr;
	EMapType MapType = EMapType::None;

	std::shared_ptr<ServerTestPlayer> Player = nullptr;
	std::shared_ptr<ATimerUI> Timer = nullptr;
	std::shared_ptr<AInGameUI> InGameUI = nullptr;
};

