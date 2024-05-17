#pragma once

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
	void CreateAnimation();

private:
	USpriteRenderer* Body = nullptr;

};

