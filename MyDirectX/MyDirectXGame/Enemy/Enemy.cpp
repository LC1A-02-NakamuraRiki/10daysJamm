#include "Enemy.h"

void Enemy::Update()
{
}

void Enemy::Move()
{
	switch (movePatern)
	{
	case 1: // �������̈ړ�

		break;

	case 2: // �c�����̈ړ�

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
