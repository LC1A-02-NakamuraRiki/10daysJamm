#include "Enemy.h"

void Enemy::Update()
{
}

void Enemy::Move()
{
	switch (movePatern)
	{
	case 1: // 横方向の移動

		break;

	case 2: // 縦方向の移動

		break;
	}
}

void Enemy::HitWall()
{
}

void Enemy::CountUp()
{
}

void Enemy::Vanish()
{
	if (count == 0)
	{
		alive = false;
	}
}
