#include "PreCompile.h"
#include "ServerGameMode.h"
#include "Player.h"
#include <EngineCore/Image.h>
#include <EngineCore/Camera.h>
#include <EngineBase/EngineSerializer.h>
#include <EngineCore/BlurEffect.h>
#include <EngineCore/EngineEditorGUI.h>
#include "PlayGameMode.h"
#include "CrazyArcadeCore.h"
#include "Packets.h"
#include "ServerTestPlayer.h"
#include "ServerTestOtherPlayer.h"
#include <EngineBase/NetObject.h>
#include "ServerHelper.h"
#include "CrazyArcadeEnum.h"
#include "BombBase.h"
#include "MapBase.h"
#include "ServerManager.h"

AServerGameMode::AServerGameMode()
	:AMainPlayLevel()
{
}

AServerGameMode::~AServerGameMode()
{

}

void AServerGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AServerGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	UNetObject::AllNetObject;
	int a = 0;
}

void AServerGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
	if (Player->GetObjectToken() == -1) {
		Player->SetObjectToken(GetToken);
	}
}


void AServerGameMode::HandlerInit()
{
	UEngineDispatcher& Dis = UCrazyArcadeCore::Net->Dispatcher;
	if (ENetType::Server == UCrazyArcadeCore::NetManager.GetNetType()) {
		Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
			{
				if (nullptr == UCrazyArcadeCore::Net)
				{
					MsgBoxAssert("�̰ſֵ���?");
				}
				UCrazyArcadeCore::Net->Send(_Packet);

				GetWorld()->PushFunction([=]()
					{
						// ���� �־�����ϱ�.
						ANetActor* OtherPlayer = UNetObject::GetNetObject<ANetActor>(_Packet->GetObjectToken());
						if (nullptr == OtherPlayer)
						{
							ServerHelper::EnumSpawn(GetWorld(), _Packet->SpawnSelect, _Packet->GetObjectToken());
							OtherPlayer = UNetObject::GetNetObject<ANetActor>(_Packet->GetObjectToken());
						}

						OtherPlayer->PushProtocol(_Packet);
					});


			});

		Dis.AddHandler<USpawnUpdatePacket>([=](std::shared_ptr<USpawnUpdatePacket> _Packet)  //���� ���� �׽�Ʈ��
			{
				GetWorld()->PushFunction([=]()
					{
						ABombBase* Bomb = UNetObject::GetNetObject<ABombBase>(_Packet->GetObjectToken());
						if (Bomb != nullptr) {
							MsgBoxAssert("�̰ŵ���������ȵ�����ȵ�����ȵ�����ȵ�����ȵ�����ȵ�")   // -Test-
						}

						ServerHelper::EnumSpawn(GetWorld(), _Packet->SpawnSelect, _Packet->GetObjectToken(), _Packet->Pos);
						Bomb = UNetObject::GetNetObject<ABombBase>(_Packet->GetObjectToken());
						Bomb->SetObjectToken(_Packet->GetObjectToken());
						Bomb->PushProtocol(_Packet);
						//MyBomb->SetObjectToken(_Packet->GetObjectToken());

						//MyBomb->SetActorLocation(_Packet->Pos);
						
						//FPoint Point = AMapBase::ConvertLocationToPoint(_Packet->Pos);
						//MyBomb->SetCurPoint(Point);
						//GetMap()->SetMapBomb(Point, MyBomb);
						
						//FEngineTimeStamp Stamp = UEngineTime::GetCurTime();
						//float FloatResult = Stamp.TimeToFloat();
						//MyBomb->ReduceCurExplosionTime(FloatResult - _Packet->SpawnTime);
					});
			});
	}
	if (ENetType::Client == UCrazyArcadeCore::NetManager.GetNetType()) {
		Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
			{
				if (nullptr == UCrazyArcadeCore::Net)
				{
					MsgBoxAssert("�̰ſֵ���?");
				}
				GetWorld()->PushFunction([=]()
					{
						// ���� �־�����ϱ�.
						ANetActor* OtherPlayer = UNetObject::GetNetObject<ANetActor>(_Packet->GetObjectToken());
						if (nullptr == OtherPlayer)
						{
							ServerHelper::EnumSpawn(GetWorld(), _Packet->SpawnSelect, _Packet->GetObjectToken());
							OtherPlayer = UNetObject::GetNetObject<ANetActor>(_Packet->GetObjectToken());
						}

						OtherPlayer->PushProtocol(_Packet);
					});
			});

		Dis.AddHandler<USpawnUpdatePacket>([=](std::shared_ptr<USpawnUpdatePacket> _Packet)  //���� ���� �׽�Ʈ��
			{
				GetWorld()->PushFunction([=]()
					{
						ABombBase* Bomb = UNetObject::GetNetObject<ABombBase>(_Packet->GetObjectToken());
						if (Bomb != nullptr) {
							MsgBoxAssert("�̰ŵ���������ȵ�����ȵ�����ȵ�����ȵ�����ȵ�����ȵ�")   // -Test-
						}

						ServerHelper::EnumSpawn(GetWorld(), _Packet->SpawnSelect, _Packet->GetObjectToken(), _Packet->Pos);
						Bomb = UNetObject::GetNetObject<ABombBase>(_Packet->GetObjectToken());
						Bomb->SetObjectToken(_Packet->GetObjectToken());
						Bomb->PushProtocol(_Packet);
						/*ABombBase* MyBomb;
						ServerHelper::EnumSpawn(GetWorld(), _Packet->SpawnSelect, 0);
						MyBomb->SetObjectToken(_Packet->GetObjectToken());
						MyBomb->PushProtocol(_Packet);
						MyBomb->SetActorLocation(_Packet->Pos);

						FPoint Point = AMapBase::ConvertLocationToPoint(_Packet->Pos);
						MyBomb->SetCurPoint(Point);
						GetMap()->SetMapBomb(Point, MyBomb);

						FEngineTimeStamp Stamp = UEngineTime::GetCurTime();
						float FloatResult = Stamp.TimeToFloat();
						MyBomb->ReduceCurExplosionTime(FloatResult - _Packet->SpawnTime);*/
					});
			});

	}
}

void AServerGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}