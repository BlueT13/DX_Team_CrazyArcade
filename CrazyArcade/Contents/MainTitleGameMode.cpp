#include "PreCompile.h"
#include "MainTitleGameMode.h"
#include <vector>

#include "LobbyTitleGameMode.h"

class ALobbyTitleGameMode;

AMainTitleGameMode::AMainTitleGameMode()
{

}

AMainTitleGameMode::~AMainTitleGameMode()
{
}

void AMainTitleGameMode::BeginPlay()
{
	Super::BeginPlay();
	TitleBackGround = CreateWidget<UImage>(GetWorld(), "TitleBackGround");
	TitleBackGround->SetSprite("Login.png");
	TitleBackGround->AddToViewPort(1); //UITest;
	TitleBackGround->SetScale({ 800,600 });
	TitleBackGround->SetPosition({ 0.0f,0.0f });

	StartButton = CreateWidget<UImage>(GetWorld(), "TitleBackGround");
	StartButton->AddToViewPort(2); //UITest;
	StartButton->SetAutoSize(1.0f, true);
	StartButton->CreateAnimation("NoneStartButtonAni", "StartButton", 0.1f, false, 0, 0);
	StartButton->CreateAnimation("HoverStartButtonAni", "StartButton", 0.5f, false, 1, 1);
	StartButton->ChangeAnimation("NoneStartButtonAni");
	StartButton->SetPosition({ 0.0f,-218.0f });

	VoidBox = CreateWidget<UImage>(GetWorld(), "VoidBoxUI");
	VoidBox->SetSprite("Login.png");
	VoidBox->AddToViewPort(1); //UITest;
	VoidBox->SetScale({ 800,600 });
	VoidBox->SetPosition({ 0.0f,0.0f });

	PlayerNameBox = CreateWidget<UImage>(GetWorld(), "PlayerBoxUI");
	PlayerNameBox->AddToViewPort(3);
	PlayerNameBox->CreateAnimation("NotActiveAni", "NameBoxNotActive.png", 0.1f, false, 0, 0);
	PlayerNameBox->CreateAnimation("ActiveAni", "NameBox.png", 0.1f, false, 0, 0);
	PlayerNameBox->ChangeAnimation("NotActiveAni");
	PlayerNameBox->SetScale({ 210.0f, 22.5f });
	PlayerNameBox->SetWidgetLocation({ -10.5f,-155.5f });

	TextWidget = CreateWidget<UTextWidget>(GetWorld(), "TextWidget");
	TextWidget->SetFont("����");
	TextWidget->SetScale(20.0f);
	TextWidget->SetColor(Color8Bit::Black);
	TextWidget->SetPosition({ -115.0f ,-143.0f });
	TextWidget->SetFlag(FW1_LEFT); //�·� ����
	TextWidget->AddToViewPort(4);
	TextWidget->SetText(PlayerName);


	StartButton->SetUnHover([=] {

		StartButton->ChangeAnimation("NoneStartButtonAni");
		});


	StartButton->SetHover([=]
		{
			StartButton->ChangeAnimation("HoverStartButtonAni");

		});

	StartButton->SetDown([=] {

		if (TextWidget->GetText().size() <= 1)
		{
			// �̸��� �Է����ּ��� UI �߰� 
			return;
		}
		GEngine->ChangeLevel("LobbyTitleTestLevel");
		});

	VoidBox->SetDown([=] {
		//Ű �Է� ����
		if (IsNameBoxAct == true)
		{
			PlayerNameBox->ChangeAnimation("NotActiveAni");
			IsNameBoxAct = false;
			UEngineInputRecorder::GetText();
			UEngineInputRecorder::RecordEnd();


		}

		});



	PlayerNameBox->SetDown([=] {
		//Ű �Է�
		PlayerNameBox->ChangeAnimation("ActiveAni");
		IsNameBoxAct = true;
		UEngineInputRecorder::RecordStart(TextWidget->GetText());
		
		GetPlayerName();
		});






	if (UEngineInput::IsDown('M'))
	{
		GetPlayerName();
	}
}


void AMainTitleGameMode::Tick(float _DeltaTime)
{


	Super::Tick(_DeltaTime);

	/*if (UEngineInput::IsAnykeyDown())
	{
		if (PlayerName.size() > 8)
		{
			return;
		}

		char ch = UEngineInput::GetAnyDownKey();

		if (ch != NULL)
		{
			PlayerName.push_back(ch);

		}

		TextWidget->SetText(PlayerName);
	std::string CurText = TextWidget->GetText();
	�ӽ� ����
	}*/
	StringToText();

	
}

void AMainTitleGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
	//UEngineInputRecorder::RecordStart();
	//���� ���۰� ���ÿ� �Է� ���� �غ� 
}

void AMainTitleGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
	ALobbyTitleGameMode* Lobby = dynamic_cast<ALobbyTitleGameMode*>(_NextLevel->GetGameMode().get());
	Lobby->SetPlayerName(PlayerName);
	//UEngineInputRecorder::RecordEnd();
}


std::string AMainTitleGameMode::GetPlayerName()
{
	return TextWidget->GetText();
}
void AMainTitleGameMode::StringToText()
{
	PlayerName = UEngineInputRecorder::GetText();
	
	if (PlayerName.size() > 0)
	{
		TextWidget->SetText(PlayerName);
	}
	else
	{
		TextWidget->SetText(" ");
	}
}