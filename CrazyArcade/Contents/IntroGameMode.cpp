#include "PreCompile.h"
#include "IntroGameMode.h"

AIntroGameMode::AIntroGameMode()
{

	//UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("IntroRenderer");
	//IntroRenderer = CreateDefaultSubObject<USpriteRenderer>("IntroRenderer");
	//IntroRenderer->SetupAttachment(Root);

	//SetRoot(Root);


}

AIntroGameMode::~AIntroGameMode()
{
}

void AIntroGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	// ��Ʈ�� ������ �̹��� ù��° �̸� :
	// intro_frame_0.png






}

void AIntroGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}

void AIntroGameMode::CreateIntroFrame(std::string _Name)
{
	// ��Ʈ�� ������ �̹��� ù��° �̸� :
	// intro_frame_0.png
	
	//IntroRenderer->CreateAnimation("IntroFrame", "intro_frame_0", 0.1f, true, 0,5);


}

