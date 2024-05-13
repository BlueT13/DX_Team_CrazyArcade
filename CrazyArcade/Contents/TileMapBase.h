#pragma once

// ���� : TileMap ���� Ŭ����
class ATileMapBase : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	ATileMapBase();
	~ATileMapBase();

	// delete Function
	ATileMapBase(const ATileMapBase& _Other) = delete;
	ATileMapBase(ATileMapBase&& _Other) noexcept = delete;
	ATileMapBase& operator=(const ATileMapBase& _Other) = delete;
	ATileMapBase& operator=(ATileMapBase&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* BackGround = nullptr;

};

