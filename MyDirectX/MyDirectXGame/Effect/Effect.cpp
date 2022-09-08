#include "Effect.h"

ParticleManager* Effect::particle = nullptr;

using namespace DirectX;

void Effect::Explosion(const XMFLOAT3& position)
{
	//表示される長さ
	int life = 8;

	//初期位置
	XMFLOAT3 pos{};
	pos = position;

	//速度
	float rand_range = 12;
	XMFLOAT3 vel{};
	vel.x = (float)((rand() % (int)rand_range) - (int)rand_range / 2) / 40;
	vel.y = abs((float)((rand() % (int)rand_range) - (int)rand_range / 2) / 40);
	vel.z = (float)((rand() % (int)rand_range) - (int)rand_range / 2) / 40;

	//加速度
	XMFLOAT3 acc{};
	acc.x = 0;
	acc.y = 0;
	acc.z = 0;

	//大きさ
	float start_scale = 2.5f;
	float end_scale = 0.4f;

	//色
	XMFLOAT4 col{};
	col.x = 0.0f;//B
	col.y = 16.0f;//R
	col.z = 0.5f;//G
	col.w = 0.2f;

	particle->Add(life, pos, vel, acc, start_scale, end_scale, col);
}

void Effect::Move(const XMFLOAT3& position, const XMFLOAT4& color)
{
	//表示される長さ
	int life = 5;

	//初期位置
	XMFLOAT3 pos{};
	pos = position;

	//速度
	XMFLOAT3 vel{};
	vel.x = 0;
	vel.y = 0;
	vel.z = 0;

	//加速度
	float rand_range = 10;
	XMFLOAT3 acc{};
	acc.x = 0;
	acc.y = 0;
	acc.z = 0;

	//大きさ
	float start_scale = 2.0f;
	float end_scale = 0.0f;

	//色
	XMFLOAT4 col{};
	col = color;

	particle->Add(life, pos, vel, acc, start_scale, end_scale, col);
}

void Effect::Dust(const XMFLOAT3& position)
{
	//表示される長さ
	int life = 5;

	//初期位置
	float rand_range = 4;
	XMFLOAT3 pos{};
	pos.x = position.x + (float)((rand() % (int)rand_range) - (int)rand_range / 2) / 5;
	pos.y = position.y + abs((float)((rand() % (int)rand_range) - (int)rand_range / 2) / 5);
	pos.z = position.z + (float)((rand() % (int)rand_range) - (int)rand_range / 2) / 5;

	//速度
	XMFLOAT3 vel{};
	vel.x = (float)((rand() % (int)rand_range) - (int)rand_range / 2) / 40;
	vel.y = abs((float)((rand() % (int)rand_range) - (int)rand_range / 2) / 40);
	vel.z = (float)((rand() % (int)rand_range) - (int)rand_range / 2) / 40;

	//加速度
	XMFLOAT3 acc{};
	acc.x = (float)((rand() % (int)rand_range) - (int)rand_range / 2) / 400;
	acc.y = abs((float)((rand() % (int)rand_range) - (int)rand_range / 2) / 400);
	acc.z = (float)((rand() % (int)rand_range) - (int)rand_range / 2) / 400;

	//大きさ
	float start_scale = 2.5f;
	float end_scale = 0.0f;

	//色
	XMFLOAT4 col{};
	col.x = 0.0f;//B
	col.y = 1.0f;//R
	col.z = 1.0f;//G
	col.w = 1.0f;

	particle->Add(life, pos, vel, acc, start_scale, end_scale, col);
}