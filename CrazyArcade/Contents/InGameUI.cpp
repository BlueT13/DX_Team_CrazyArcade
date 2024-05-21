#include"PreCompile.h"
#include "InGameUI.h"
#include "Player.h"
#include "CrazyArcadeCore.h"
#include "ConnectionInfo.h"
AInGameUI::AInGameUI()
{

}

AInGameUI::~AInGameUI()
{
}


void AInGameUI::BeginPlay()
{
	UEngineSprite::CreateCutting("Play_ExitButtonHover.png", 1, 2);

	Super::BeginPlay();
	CancelBtn = CreateWidget<UImage>(GetWorld(), "CancelButton");
	CancelBtn->CreateAnimation("CancelButtonUnHoverAni", "Play_ExitButtonUnHover.png", 0.1f, false, 0, 0);
	CancelBtn->CreateAnimation("CancelButtonHoverAni", "Play_ExitButtonHover.png", 0.1f, false, 0, 1);
	CancelBtn->CreateAnimation("CancelButtonIsDownAni", "Play_ExitButtonIsDown.png", 0.1f, false, 0, 0);

	CancelBtn->SetAutoSize(1.0f, true);
	CancelBtn->ChangeAnimation("CancelButtonUnHoverAni");
	CancelBtn->SetWidgetLocation({ 316.0f, -276.0f });
	CancelBtn->AddToViewPort(3);


	ResultBackGround = CreateWidget<UImage>(GetWorld(), "ResultBackGroundUI");
	ResultBackGround->SetSprite("ResultWindow.png");
	ResultBackGround->SetMulColor({ 1.0f,1.0f,1.0f,0.7f });
	ResultBackGround->AddWidgetLocation(FVector{-80.0,-30.0f });
	ResultBackGround->AddToViewPort(3);
	ResultBackGround->SetScale({ 550,400 });


	ResultSummary = CreateWidget<UImage>(GetWorld(), "ResultBackGroundUI");
	ResultSummary->SetSprite("Result_Summary.png");
	
	ResultSummary->AddWidgetLocation(FVector{ -90.0f,140.0f });
	ResultSummary->SetScale({ 350,20 });
	ResultSummary->AddToViewPort(4);



	CancelBtn->SetUnHover([=] {



		CancelBtn->ChangeAnimation("CancelButtonUnHoverAni");

		});
	CancelBtn->SetHover([=] {

		CancelBtn->ChangeAnimation("CancelButtonHoverAni");


		});
	CancelBtn->SetDown([=] {



		CancelBtn->ChangeAnimation("CancelButtonUnHoverAni");
		CancelBtn->SetUp([=] {

			GEngine->ChangeLevel("LobbyTitleTestLevel");
			});

		});


	//���� ���� �ϸ� ���� ���� �����ͼ� ǥ�����ֱ� 
	
	for (int i = 0; i < 9; i++)
	{

		UImage* Render = CreateWidget<UImage>(GetWorld(), "PlayerRender" + i);
		//Render->SetSprite();
		Render->AddToViewPort(4);
		PlayerUI.push_back(Render);
		
		UTextWidget* Name = CreateWidget<UTextWidget>(GetWorld(), "PlayerNameUI" + i);
		Name->SetFont("����");
		Name->SetScale(12.0f);
		Name->SetColor(Color8Bit::White);
		Name->AddToViewPort(30);
		Name->SetFlag(FW1_LEFT);
		Name->SetPosition({ 0 * (i + 20),0 });
		
		PlayerNameUI.push_back(Name);

		PlayerState State;
		State.Order = i;
		State.PlayerName = "";
		State.PlayerColor = ECharacterColor::Red;
		State.PlayerType = ECharacterType::Random;
		State.IsDead = false;
		PlayerInfo.push_back(State);
	}
	
	InitPlayerInfo();
	//DataToRender();

	ResultBackGround->SetActive(false);
	ResultSummary->SetActive(false);
	std::vector<UImage*> PlayerUI; //�÷��̾�
	std::vector<UTextWidget*> PlayerNameUI ;
	std::vector<PlayerState> PlayerInfo;


}
void AInGameUI::Tick(float _DeltaTIme)
{

	Super::Tick(_DeltaTIme);

	for (std::pair<const int, bool>& Pair : FPlayerInfo::IsDeads)
	{
		//if (Pair.first == true)
		//{
		//	// ���� �÷��̾ �ؾ��� �ڵ�
		//	//PlayerUI[Pair.first]->ChangeAnimation();
		//	
		//}
	}
	//�׾����� ��Ҵ��� Ȯ���ϴ� ���� �ڵ�(������)

	if (this->IsActive() == true)
	{
	InitPlayerInfo();
	DataToRender();
	}



}




void AInGameUI::PlayerUpdate()
{
	std::map<int, std::string> UserInfos = ConnectionInfo::GetInst().GetUserInfos();
	
	for (std::pair<int, std::string> Iterator : UserInfos)
	{
	//	PlayerInfo[Iterator.first].IsDead = FPlayerInfo::IsDeads;
	}
	
	
	for (int i = 0; i < UCrazyArcadeCore::Net->GetSessionToken(); i++)
	{
		//PlayerInfo[i].IsDead() = FPlayerInfo::IsDeads();
	}

	
}



void AInGameUI::InitPlayerInfo()
{
	//

	std::map<int, std::string> UserInfos = ConnectionInfo::GetInst().GetUserInfos();
	std::map<int, bool>UserDeadCheck = FPlayerInfo::IsDeads;


	//������ �̸� ��������
	for (std::pair<int, std::string> Iterator : UserInfos)
	{ //���ͷ����ͷ� ������ 
		PlayerInfo[Iterator.first].Order = Iterator.first;
		PlayerInfo[Iterator.first].PlayerName = Iterator.second;
		//PlayerInfo[Iterator.first].IsDead = UserDeadCheck[Iterator.first];
		//�ӽ� �۾��� �ڵ� 	
		
		

	}


	for (std::pair<int, bool> Iterattor : UserDeadCheck)
	{	
		PlayerInfo[Iterattor.first].IsDead = Iterattor.second;
	}
	

}


void AInGameUI::DataToRender()
{
	//PlayerInfo.size()
	for (int i = 0; i < PlayerInfo.size(); i++)
	{
		PlayerNameUI[i]->SetPosition({306,180-(i*43)});
		PlayerNameUI[i]->SetText(PlayerInfo[i].PlayerName);
		
	}


}