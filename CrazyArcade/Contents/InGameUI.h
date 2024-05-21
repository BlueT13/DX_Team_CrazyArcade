#pragma once
#include"ConnectionInfo.h"

class AInGameUI : public AActor
{
	struct PlayerState
	{
		int Order;
		std::string PlayerName;
		ECharacterColor PlayerColor;
		ECharacterType PlayerType;
		bool IsDead;



		//�����̶� �������̽� �����ϰ� ���� 
	};
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	AInGameUI();
	~AInGameUI();

	// delete Function
	AInGameUI(const AInGameUI& _Other) = delete;
	AInGameUI(AInGameUI&& _Other) noexcept = delete;
	AInGameUI& operator=(const AInGameUI& _Other) = delete;
	AInGameUI& operator=(AInGameUI&& _Other) = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTIme) override;

private:
	void CountDown(float _DeltaTime);
	void TimerText();
	void IntToText();


	std::string MinText;
	std::string SecText;

	int Min = 0;


	UImage* CancelBtn = nullptr;
	UImage* ResultBackGround = nullptr;
	UImage* ResultSummary = nullptr;

	UImage* PlayerStateRender = nullptr;

	int ServerToken = 0;
	
	std::vector<UImage*> PlayerUI; //�÷��̾�
	std::vector<UTextWidget*> PlayerNameUI;
	std::vector<PlayerState> PlayerInfo;


	void InitPlayerInfo();

	void PlayerUpdate();


	void DataToRender();





};

