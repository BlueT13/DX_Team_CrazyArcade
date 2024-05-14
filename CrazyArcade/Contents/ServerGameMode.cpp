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
	:AMainPlayLevel()
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

				Player->SetObjectToken(UNetObject::GetNewObjectToken());

				ServerPacketInit(UCrazyArcadeCore::Net->Dispatcher);
			});

		NetWindow->SetClientConnectFunction([&](std::string IP, short PORT)
			{
				UCrazyArcadeCore::Net = std::make_shared<UEngineClient>();
				UCrazyArcadeCore::Net->Connect(IP, PORT);

				UCrazyArcadeCore::Net->SetTokenPacketFunction([=](USessionTokenPacket* _Token)
					{
						Player->SetObjectToken(_Token->GetObjectToken());

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
					//OtherPlayer
				});


		});

	Dis.AddHandler<USpawnUpdatePacket>([=](std::shared_ptr<USpawnUpdatePacket> _Packet)  //���� ���� �׽�Ʈ��
		{
			GetWorld()->PushFunction([=]()
				{
					ServerTestOtherPlayer* OtherPlayer;
					OtherPlayer = this->GetWorld()->SpawnActor<ServerTestOtherPlayer>("OtherPlayer", 0).get();
					OtherPlayer->SetObjectToken(10);
					OtherPlayer->PushProtocol(_Packet);
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
					OtherPlayer->PushProtocol(_Packet);
				});
		});
}

void AServerGameMode::LevelEnd(ULevel* _DeltaTime)
{
	NetWindow->Off();
}