#pragma once
#include "MapHelper.h"

class AMainPlayLevel;

// ���� : �� ��ź �ĵ�
class AWave : public ANetActor
{
	GENERATED_BODY(ANetActor)
public:
	// constrcuter destructer
	AWave();
	~AWave();

	// delete Function
	AWave(const AWave& _Other) = delete;
	AWave(AWave&& _Other) noexcept = delete;
	AWave& operator=(const AWave& _Other) = delete;
	AWave& operator=(AWave&& _Other) noexcept = delete;

	void SetWaveType(EWaveType _WaveType);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void SetImgCutting();
	void CreateAnim();

private:
	AMainPlayLevel* PlayLevel = nullptr;
	USpriteRenderer* Body = nullptr;
	EWaveType WaveType = EWaveType::None;
	FPoint CurPoint = { -1, -1 };
};

