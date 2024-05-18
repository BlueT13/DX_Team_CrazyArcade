#pragma once
#include <EngineCore/Widget.h>
#include <EngineCore/TextWidget.h>
#include<vector>
class AMainTitleGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constructor destructor
	AMainTitleGameMode();
	~AMainTitleGameMode();

	// delete Function
	AMainTitleGameMode(const AMainTitleGameMode& _Other) = delete;
	AMainTitleGameMode(AMainTitleGameMode&& _Other) noexcept = delete;
	AMainTitleGameMode& operator=(const AMainTitleGameMode& _Other) = delete;
	AMainTitleGameMode& operator=(AMainTitleGameMode&& _Other) = delete;

	std::string GetPlayerName();



protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	void ServerStart();
	void ClientStart();
private:
	void StringToText();
	
	// UI
	UImage* TitleBackGround = nullptr;
	UImage* LoginUI = nullptr;

	UImage* StartButton = nullptr;
	UImage* Button_1P = nullptr;
	UImage* Button_2P = nullptr;

	UImage* VoidBox = nullptr;
	UImage* PlayerNameBox = nullptr;
	UTextWidget* TextWidget = nullptr;
	UImage* IPNumBox = nullptr;
	UTextWidget* IPNumText = nullptr;
	UTextWidget* IPNumTitle = nullptr;
	UImage* PortNumBox = nullptr;
	UTextWidget* PortNumText = nullptr;
	UTextWidget* PortNumTitle = nullptr;

	std::string PlayerName;
	std::string IPNum;
	std::string PortNum;

	bool IsNameBoxAct = false;
	bool IsIPNumBoxActive = false;
	bool IsPortNumBoxActive = false;
};