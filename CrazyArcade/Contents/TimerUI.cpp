#include"PreCompile.h"
#include "TimerUI.h"

ATimerUI::ATimerUI()
{
	
}

ATimerUI::~ATimerUI()
{
}


void ATimerUI::BeginPlay()
{
	Super::BeginPlay();
	UEngineSprite::CreateCutting("TimeNumber.png", 10, 1); //
	
	MinUI = CreateWidget<UImage>(GetWorld(), "Min");
	MinUI->SetAutoSize(1.0f, true);
	MinUI->AddToViewPort(10);
	MinUI->SetPosition(FVector{ 315,252 });
	MinUI->SetSprite("TimeNumber.png");



	MinUI2 = CreateWidget<UImage>(GetWorld(), "Min2");
	MinUI2->SetAutoSize(1.0f, true);
	MinUI2->AddToViewPort(10);
	MinUI2->SetPosition(FVector{ 327,252 });
	//MinUI2->SetSprite("0.png");
	
	SecUI = CreateWidget<UImage>(GetWorld(), "Sec");
	SecUI->SetAutoSize(1.0f, true);
	SecUI->AddToViewPort(10);
	SecUI->SetPosition(FVector{ 348,252 });

	SecUI2 = CreateWidget<UImage>(GetWorld(), "Sec2");
	SecUI2->SetAutoSize(1.0f, true);
	SecUI2->AddToViewPort(10);
	SecUI2->SetPosition(FVector{ 360,252 });

	

}
void ATimerUI::Tick(float _DeltaTIme)
{

	Super::Tick(_DeltaTIme);
	CountDown(_DeltaTIme);
	TimerText();
}

void ATimerUI::CountDown(float _DeltaTime)
{
	Timer -= _DeltaTime;


	if (Timer < 0)
	{
		Timer = 0;
		return;
	}
}


void ATimerUI::TimerText()
{
	int Time = static_cast<int>(Timer);




	int Min = Time / 60;//��
	int Sec = Time % 60;//��
	
	Secint = Sec / 10;
	SecInt2 = Sec % 10;
	//std::string MinTexter = std::to_string(Min);
	//MinText = std::to_string(Time / 60);
	//SecText = std::to_string(Time % 60);

	MinUI2->SetSprite( "TimeNumber.png" , Min);
	SecUI->SetSprite( "TimeNumber.png" , Secint);
	SecUI2->SetSprite( "TimeNumber.png", SecInt2);
	
}

