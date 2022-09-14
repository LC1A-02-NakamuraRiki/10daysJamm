#include "Effect.h"

using namespace DirectX;

ParticleManager* Effect::particle = nullptr;
XMFLOAT4 Effect::color{};

XMFLOAT4 Effect::GetRandomColor()
{
	//�F
	float rand_range = 20;
	color.x = (rand() % (int)rand_range) / 200;
	color.y = (float)(rand() % (int)rand_range) / 20;
	color.z = (float)(rand() % (int)rand_range) / 20;
	color.w = (float)(rand() % 3) / 2 + 0.1f;

	return color;
}

void Effect::Explosion(const XMFLOAT3& position)
{
	//�\������钷��
	int life = 8;

	//�����ʒu
	XMFLOAT3 pos{};
	pos = position;

	//���x
	float rand_range = 12;
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
	XMFLOAT4 col{};
	col.x = 0.0f;//B
	col.y = 16.0f;//R
	col.z = 0.5f;//G
	col.w = 0.2f;

	particle->Add(life, pos, vel, acc, start_scale, end_scale, col);
}

void Effect::Move(const XMFLOAT3& position, const XMFLOAT4& color)
{
	//�\������钷��
	int life = 5;

	//�����ʒu
	XMFLOAT3 pos{};
	pos = position;

	//���x
	XMFLOAT3 vel{};
	vel.x = 0;
	vel.y = 0;
	vel.z = 0;

	//�����x
	XMFLOAT3 acc{};
	acc.x = 0;
	acc.y = 0;
	acc.z = 0;

	//�傫��
	float start_scale = 2.0f;
	float end_scale = 0.0f;

	//�F
	XMFLOAT4 col{};
	col = color;

	particle->Add(life, pos, vel, acc, start_scale, end_scale, col);
}

void Effect::Burning(const XMFLOAT3& position)
{
	//�\������钷��
	int life = 16;

	for (int i = 0; i < 5; i++)
	{
		//�����ʒu
		float rand_range = 8;
		XMFLOAT3 pos{};
		pos.x = position.x + (float)((rand() % (int)rand_range) - (int)rand_range / 2) / 8;
		pos.y = position.y + abs((float)((rand() % (int)rand_range) - (int)rand_range / 2) / 8);
		pos.z = position.z + (float)((rand() % (int)rand_range) - (int)rand_range / 2) / 8;

		//���x
		XMFLOAT3 vel{};
		vel.x = 0;
		vel.y = abs((float)((rand() % (int)rand_range) - (int)rand_range / 2) / 10);
		vel.z = 0;

		//�����x
		XMFLOAT3 acc{};
		acc.x = (float)((rand() % (int)rand_range) - (int)rand_range / 2) / 400;
		acc.y = abs((float)((rand() % (int)rand_range) - (int)rand_range / 2) / 400);
		acc.z = (float)((rand() % (int)rand_range) - (int)rand_range / 2) / 400;

		//�傫��
		float start_scale = 2.5f;
		float end_scale = 0.0f;

		//�F
		XMFLOAT4 col{};
		col.x = 0.0f;//B
		col.y = 16.0f;//R
		col.z = 0.3f;//G
		col.w = 0.2f;

		particle->Add(life, pos, vel, acc, start_scale, end_scale, col);
	}
}

void Effect::FireWorks(const XMFLOAT3& position)
{
	for (int i = 0; i < 20; i++)
	{
		//�\������钷��
		int life = 15;

		//�����ʒu
		XMFLOAT3 pos = position;
		pos.y++;

		//���x
		float rand_range = 12;
		XMFLOAT3 vel{};
		vel.x = (float)((rand() % (int)rand_range) - (int)rand_range / 2) / 10;
		vel.y = (float)((rand() % (int)rand_range) - (int)rand_range / 2) / 10;
		vel.z = (float)((rand() % (int)rand_range) - (int)rand_range / 2) / 10;

		//�����x
		XMFLOAT3 acc{};
		acc.x = (float)((rand() % (int)rand_range) - (int)rand_range / 2) / 400;
		acc.y = -abs((float)((rand() % (int)rand_range)) / 400);
		acc.z = (float)((rand() % (int)rand_range) - (int)rand_range / 2) / 400;

		//�傫��
		float start_scale = 2.0f;
		float end_scale = 0.5f;

		particle->Add(life, pos, vel, acc, start_scale, end_scale, color);
	}
}