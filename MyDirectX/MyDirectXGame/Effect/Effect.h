#pragma once
#include "../3d/ParticleManager.h"

class Effect
{
protected: // エイリアス
// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	static ParticleManager* particle;

public:
	static void SetParticleManager(ParticleManager* particleManager) { Effect::particle = particleManager; }

	static void Explosion(const XMFLOAT3& position);
};