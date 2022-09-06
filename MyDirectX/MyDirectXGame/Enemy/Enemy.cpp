#include "Enemy.h"

void Enemy::Update()
{
}

void Enemy::Move()
{
	switch (movePatern)
	{
	case 1: // ‰¡•ûŒü‚ÌˆÚ“®

		break;

	case 2: // c•ûŒü‚ÌˆÚ“®

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
