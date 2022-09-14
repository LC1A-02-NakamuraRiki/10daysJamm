#pragma once
#include "../3d/ParticleManager.h"

class Effect
{
protected: // �G�C���A�X
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	static ParticleManager* particle;
	static XMFLOAT4 color;

public:
	static void SetParticleManager(ParticleManager* particleManager) { Effect::particle = particleManager; }

	static XMFLOAT4 GetRandomColor();

	//�����G�t�F�N�g
	static void Explosion(const XMFLOAT3& position);

	//�����G�t�F�N�g
	static void Burning(const XMFLOAT3& position);

	//�ړ��G�t�F�N�g
	static void Move(const XMFLOAT3& position, const XMFLOAT4& color);

	//�ԉ�
	static void FireWorks(const XMFLOAT3& position);
};