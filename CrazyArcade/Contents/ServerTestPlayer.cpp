#include "PreCompile.h"
#include "ServerTestPlayer.h"
#include "Packets.h"
#include "CrazyArcadeCore.h"
#include "ServerTestOtherPlayer.h"

ServerTestPlayer::ServerTestPlayer()
	:APlayer()
{
}

ServerTestPlayer::~ServerTestPlayer()
{
}

void ServerTestPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ServerTestPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


	if (false == IsNetInit())
	{
		// ��Ʈ��ũ ����غ� ���� �ȵ� ������Ʈ��.
		if (nullptr != UCrazyArcadeCore::Net)
		{
			InitNet(UCrazyArcadeCore::Net);
		}
	}

	static float FrameTime = 1.0f / 60.0f;
	static float CurTime = FrameTime;

	CurTime -= _DeltaTime;


	if (0.0f >= CurTime && true == IsNetInit())
	{
		std::shared_ptr<UActorUpdatePacket> Packet = std::make_shared<UActorUpdatePacket>();

		Packet->Pos = GetActorLocation();
		Packet->SpriteName = Renderer->GetCurAnimationName();
		Send(Packet);
		CurTime += FrameTime;
		if (IsPress(VK_SPACE)) {
			std::shared_ptr<USpawnUpdatePacket> SpawnPacket = std::make_shared<USpawnUpdatePacket>();
			SpawnPacket->Pos = GetActorLocation();
			SpawnPacket->SpawnSelect = ServerObjectType::Player;
			ServerTestOtherPlayer* Test = GetWorld()->SpawnActor<ServerTestOtherPlayer>("Test").get();
			Test->SetActorLocation(GetActorLocation());
			Send(SpawnPacket);
		}
	}
}