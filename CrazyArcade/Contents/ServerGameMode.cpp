#include "PreCompile.h"
#include "ServerGameMode.h"
#include "Player.h"
#include <EngineCore/Image.h>
#include <EngineCore/Camera.h>
#include <EngineBase/EngineSerializer.h>
#include <EngineCore/BlurEffect.h>
#include <EngineCore/EngineEditorGUI.h>
#include "ServerPlayer.h"
#include "PlayGameMode.h"
#include "CrazyArcadeCore.h"
#include "Packets.h"
#include "OtherPlayer.h"
#include "ServerTestPlayer.h"
#include "ServerTestOtherPlayer.h"


AServerGameMode::AServerGameMode()
{
}

AServerGameMode::~AServerGameMode()
{
	if (nullptr != UCrazyArcadeCore::Net)
	{
		UCrazyArcadeCore::Net->End();
		UCrazyArcadeCore::Net = nullptr;
	}
}

void AServerGameMode::BeginPlay()
{
	Super::BeginPlay();
	// TestThread.Start();
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	MainPlayer = GetWorld()->SpawnActor<ServerTestPlayer>("Player");

}

void AServerGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void AServerGameMode::LevelStart(ULevel* _DeltaTime)
{
	if (nullptr == NetWindow)
	{
		NetWindow = UEngineEditorGUI::CreateEditorWindow<UEngineNetWindow>("NetWindow");

		NetWindow->SetServerOpenFunction([&]()
			{
				UCrazyArcadeCore::Net = std::make_shared<UEngineServer>();
				UCrazyArcadeCore::Net->ServerOpen(30000, 512);

				// ���⿡�� ���� �÷��̾����� ��ȣ�� �ϳ� �̴ٰϴ�.

				MainPlayer->SetObjectToken(UNetObject::GetNewObjectToken());

				ServerPacketInit(UCrazyArcadeCore::Net->Dispatcher);
			});

		NetWindow->SetClientConnectFunction([&](std::string IP, short PORT)
			{
				UCrazyArcadeCore::Net = std::make_shared<UEngineClient>();
				UCrazyArcadeCore::Net->Connect(IP, PORT);

				UCrazyArcadeCore::Net->SetTokenPacketFunction([=](USessionTokenPacket* _Token)
					{
						MainPlayer->SetObjectToken(_Token->GetObjectToken());

					});

				// � ��Ű�� ������ ��� ó���Ұ����� ���ϴ� �� �ؾ��Ѵ�.
				ClientPacketInit(UCrazyArcadeCore::Net->Dispatcher);
			});
	}
	NetWindow->On();
}

void AServerGameMode::ServerPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
		{
			if (nullptr == UCrazyArcadeCore::Net)
			{
				return;
			}

			// �ٸ� ��������� �� ������Ʈ�� ���ؼ� �˸���
			UCrazyArcadeCore::Net->Send(_Packet);

			GetWorld()->PushFunction([=]()
				{
					// ���� �־�����ϱ�.
					ServerTestOtherPlayer* OtherPlayer = UNetObject::GetNetObject<ServerTestOtherPlayer>(_Packet->GetObjectToken());
					if (nullptr == OtherPlayer)
					{
						OtherPlayer = this->GetWorld()->SpawnActor<ServerTestOtherPlayer>("OtherPlayer", 0).get();
						OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
					}
					OtherPlayer->PushProtocol(_Packet);
				});


		});

	Dis.AddHandler<USpawnUpdatePacket>([=](std::shared_ptr<USpawnUpdatePacket> _Packet)  //���� ���� �׽�Ʈ��
		{
			GetWorld()->PushFunction([=]()
				{
					ServerTestOtherPlayer* OtherPlayer;
					OtherPlayer = this->GetWorld()->SpawnActor<ServerTestOtherPlayer>("OtherPlayer", 0).get();
					OtherPlayer->SetObjectToken(10);
					OtherPlayer->SetActorLocation(_Packet->Pos);
				});
		});
}

void AServerGameMode::ClientPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
		{
			GetWorld()->PushFunction([=]()
				{
					ServerTestOtherPlayer* OtherPlayer = UNetObject::GetNetObject<ServerTestOtherPlayer>(_Packet->GetObjectToken());
					if (nullptr == OtherPlayer)
					{
						OtherPlayer = this->GetWorld()->SpawnActor<ServerTestOtherPlayer>("OtherPlayer", 0).get();
						OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
					}
					OtherPlayer->SetActorLocation(_Packet->Pos);
					OtherPlayer->GetRenderer()->ChangeAnimation(_Packet->SpriteName);
				});
		});

	Dis.AddHandler<USpawnUpdatePacket>([=](std::shared_ptr<USpawnUpdatePacket> _Packet)  //���� ���� �׽�Ʈ��
		{
			GetWorld()->PushFunction([=]()
				{
					ServerTestOtherPlayer* OtherPlayer;
					OtherPlayer = this->GetWorld()->SpawnActor<ServerTestOtherPlayer>("OtherPlayer", 0).get();
					OtherPlayer->SetObjectToken(10);
					OtherPlayer->SetActorLocation(_Packet->Pos);
				});
		});
}

void AServerGameMode::LevelEnd(ULevel* _DeltaTime)
{
	NetWindow->Off();
}