#pragma once
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineProtocol.h>

// ���� ������ ��� ����

// ������ ������Ʈ�� ����� �־�.
// ������ ������Ʈ�� ����� �־�� �Ѵ�.
enum ServerObjectType
{
	Player,
	Bomb,
};

enum EContentPacket
{
	ActorUpdatePacket = 99,
	SpawnUpdatePacket,

};

// �츮�� �ּ� 16����Ʈ�� �־�� �����Ҽ� �ִ�.
// 16����Ʈ �̻� �Դٰ� �ص�
// �׺��� �� ū ��Ŷ�鵵 �ִ�.

// �ּ� 16����Ʈ�� �־�� �ϰ� + 32
// ���� :
class UActorUpdatePacket : public UEngineProtocol
{
public: 
	static const EContentPacket Type = EContentPacket::ActorUpdatePacket;
public: 
	UActorUpdatePacket()
	{ 
		SetType(EContentPacket::ActorUpdatePacket);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << Pos;
		_Ser << SpriteName;

		int a = 0;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Pos;
		_Ser >> SpriteName;
	}

public:
	float4 Pos = float4::Zero;
	std::string SpriteName; // ?? ����
};

class USpawnUpdatePacket : public UEngineProtocol {
public:
	static const EContentPacket Type = EContentPacket::SpawnUpdatePacket;
public:
	USpawnUpdatePacket()
	{
		SetType(EContentPacket::SpawnUpdatePacket);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << Pos;
		_Ser << SpawnSelect;
		_Ser << SpawnTime;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Pos;
		_Ser >> reinterpret_cast<int&>(SpawnSelect);
	}

public:
	float4 Pos = float4::Zero;
	ServerObjectType SpawnSelect = ServerObjectType::Player; // ?? ����
	float SpawnTime = 0.0f;
};
