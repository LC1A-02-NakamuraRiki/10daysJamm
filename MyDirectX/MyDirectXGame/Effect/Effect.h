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

	//爆発エフェクト
	static void Explosion(const XMFLOAT3& position);

	//爆風エフェクト
	static void Dust(const XMFLOAT3& position);

	//移動エフェクト
	static void Move(const XMFLOAT3& position, const XMFLOAT4& color);
};