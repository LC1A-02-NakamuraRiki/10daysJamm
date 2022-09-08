#include "Effect.h"

ParticleManager* Effect::particle = nullptr;

using namespace DirectX;

void Effect::Explosion(const XMFLOAT3& position)
{
	//�\������钷��
	int life = 10;

	//�����ʒu
	XMFLOAT3 pos{};
	pos = position;

	//���x
	float rand_range = 18;
	XMFLOAT3 vel{};
	vel.x = (float)((rand() % (int)rand_range) - (int)rand_range / 2) / 40;
	vel.y = abs((float)((rand() % (int)rand_range) - (int)rand_range / 2) / 40);
	vel.z = (float)((rand() % (int)rand_range) - (int)rand_range / 2) / 40;

	//�����x
	XMFLOAT3 acc{};
	acc.x = 0;
	acc.y = 0;
	acc.z = 0;

	//�傫��
	float start_scale = 2.5f;
	float end_scale = 0.4f;

	//�F
	XMFLOAT4 color{};
	color.x = 0.0f;//B
	color.y = 16.0f;//R
	color.z = 0.5f;//G
	color.w = 0.2f;

	particle->Add(life, pos, vel, acc, start_scale, end_scale, color);
}
