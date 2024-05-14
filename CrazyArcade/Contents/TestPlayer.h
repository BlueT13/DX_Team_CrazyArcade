#pragma once
#include "Player.h"

// ���� : �׽�Ʈ �÷��̾�
class ATestPlayer : public APlayer
{
	GENERATED_BODY(APlayer)
public:
	// constrcuter destructer
	ATestPlayer();
	~ATestPlayer();

	// delete Function
	ATestPlayer(const ATestPlayer& _Other) = delete;
	ATestPlayer(ATestPlayer&& _Other) noexcept = delete;
	ATestPlayer& operator=(const ATestPlayer& _Other) = delete;
	ATestPlayer& operator=(ATestPlayer&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void KeyMove(float _DeltaTime, FVector _Dir, float _Speed) override;

private:

};

