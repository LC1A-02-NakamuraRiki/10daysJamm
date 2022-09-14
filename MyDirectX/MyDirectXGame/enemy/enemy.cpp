#include "enemy.h"
#include "../collision/Collision.h"
#include "../Effect/Effect.h"
#include<time.h>
#include<random>

void Enemy::Initialize(int x, int y, int moveVector, int enemysNo)
{

	enemyType[enemysNo] = moveVector;
	modelEnemy = Model::CreateFromObject("largeCarL", false);
	objEnemy[enemysNo] = Object3d::Create(modelEnemy);
	objEnemy[enemysNo]->SetScale(XMFLOAT3({ 0.75, 0.75, 0.75 }));
	pos[enemysNo] = XMFLOAT3({ x * 4.0f - (MapValue * 4.0f / 2) + 2, 1.0f, y * 4.0f - (MapValue * 4.0f / 2) + 2 });
	objEnemy[enemysNo]->SetPosition(pos[enemysNo]);

}

void Enemy::EndInitialize()
{
	for (int i = 0; i < 11; i++)
	{
		pos[i] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
		angle[i] = { 0.0f,0.0f,0.0f };

		enemyY[i] = 0;//盤面の位置
		enemyX[i] = 0;//盤面の位置

		enemyDead[i] = true;

		returnCount[i] = 3;
		enemyLv[i] = 1;

		score = 0;

		spawnNum = 2;

		wave = 1;
		killCount = 40;

		moveCount = 0;

		lane[i] = 0;
		objEnemy[i]->SetPosition(pos[i]);
	}
	
	/*InitializeValue(1, 1, 0, 1, 1);
	InitializeValue(1, 1, 0, 4, 1);
	InitializeValue(1, 1, 0, 6, 1);
	InitializeValue(1, 1, 0, 9, 1);
	
	InitializeValue(11, 11, 3, 2, 2);
	InitializeValue(11, 11, 3, 7, 2);
	InitializeValue(11, 11, 3, 10, 2);*/
;
}


void Enemy::enemyCreate()
{
	for (int enemyNo = 0; enemyNo < spawnNum; enemyNo++)
	{
		if (enemyDead[enemyNo])
		{
			std::random_device rnd;
			std::mt19937 mt(rnd());
			std::uniform_int_distribution<>rand500(1, 2000);//0~3の範囲
			int spown_cnt = rand500(mt);
		
			if (spown_cnt == 1)
			{
				if(enemyNo == 0 || enemyNo == 3 || enemyNo == 5 || enemyNo == 8 || enemyNo == 11)
				{
					InitializeValue(9, 9, 3, enemyNo, 0);
				}
				if (enemyNo == 1 || enemyNo == 4 || enemyNo == 6 || enemyNo == 9)
				{
					InitializeValue(1, 1, 0, enemyNo, 1);
				}
				if (enemyNo == 2 || enemyNo == 7 || enemyNo == 10 )
				{
					InitializeValue(11, 11, 3, enemyNo, 2);
				}
			}
		}
	}
}

void Enemy::InitializeValue(int x, int y, int moveVector, int enemysNo,int laneNo)
{
	pos[enemysNo] = { 0.0f,0.0f,0.0f };
	angle[enemysNo] = { 0.0f,0.0f,0.0f };
	enemyType[enemysNo] = moveVector;
	enemyY[enemysNo] = 0;//盤面の位置
	enemyX[enemysNo] = 0;//盤面の位置
	returnCount[enemysNo] = 3;
	enemyLv[enemysNo] = 1;
	pos[enemysNo] = XMFLOAT3({ x * 4.0f - (MapValue * 4.0f / 2) + 2 + 1, 1.0f, y * 4.0f - (MapValue * 4.0f / 2) + 2 + 1 });
	objEnemy[enemysNo]->SetPosition(pos[enemysNo]);
	if (moveVector == 0) { angle[enemysNo].y = 270; }
	if (moveVector == 1) { angle[enemysNo].y = 90; }
	if (moveVector == 2) { angle[enemysNo].y = 0; }
	if (moveVector == 3) { angle[enemysNo].y = 180; }
	objEnemy[enemysNo]->SetRotation(angle[enemysNo]);
	lane[enemysNo] = laneNo;
	enemyDead[enemysNo] = false;
}

void Enemy::Update(Player* player, MapChip* mapChip, bool strat)
{
	EnemyFire(mapChip);

	for (int enemyNo = 0; enemyNo < enemyMaxNo; enemyNo++)
	{
	//	EnemyExplosion(player, mapChip);
		objEnemy[enemyNo]->Update();
		if (strat == false)
		{
			enemyCreate();
			Move(player, mapChip);
		}
		Explosion(player, mapChip);
		objEnemy[enemyNo]->SetRotation(angle[enemyNo]);
	}

	if (killCount > 25) 
	{ spawnNum = 11; wave = 6; }
	else if (killCount > 20) 
	{ spawnNum = 9; wave = 5; }
	else if (killCount > 15) 
	{ spawnNum = 7; wave = 4; }
	else if (killCount > 10) 
	{ spawnNum = 5; wave = 3; }
	else if (killCount > 5) 
	{ spawnNum = 4; wave = 2; }
}

void Enemy::Draw()
{
	for (int enemyNo = 0; enemyNo < enemyMaxNo; enemyNo++)
	{
		if (!enemyDead[enemyNo])
		{
			objEnemy[enemyNo]->Draw();
		}
		
	}
}

void Enemy::DrawSprite(MapChip* mapChip)
{
}

void Enemy::Move(Player* player, MapChip* mapChip)
{
	for (int enemyNo = 0; enemyNo < enemyMaxNo; enemyNo++)
	{
		if(lane[enemyNo] == 0)
		{
			if (enemyType[enemyNo] == 0)
			{
				if (!enemyDead[enemyNo])
				{
					pos[enemyNo].z += 0.02;
					objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
					if (pos[enemyNo].z > 14)
					{
						enemyType[enemyNo] = 3;
						pos[enemyNo].z = 14;
						objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
						angle[enemyNo].y = 180;
						objEnemy[enemyNo]->SetRotation(angle[enemyNo]);
					}
				}
			}
			if (enemyType[enemyNo] == 1)
			{
				if (!enemyDead[enemyNo])
				{
					pos[enemyNo].z -= 0.02;
					objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
					if (pos[enemyNo].z < -14)
					{
						enemyType[enemyNo] = 2;
						pos[enemyNo].z = -14;
						objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
						angle[enemyNo].y = 0;
						objEnemy[enemyNo]->SetRotation(angle[enemyNo]);
					}
				}
			}
			if (enemyType[enemyNo] == 2)
			{
				if (!enemyDead[enemyNo])
				{
					pos[enemyNo].x += 0.02;
					objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
					if (pos[enemyNo].x > 14)
					{
						enemyType[enemyNo] = 0;
						pos[enemyNo].x = 14;
						objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
						angle[enemyNo].y = 270;
						objEnemy[enemyNo]->SetRotation(angle[enemyNo]);
					}
				}
			}
			if (enemyType[enemyNo] == 3)
			{
				if (!enemyDead[enemyNo])
				{
					pos[enemyNo].x -= 0.02;
					objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
					if (pos[enemyNo].x < -14)
					{
						enemyType[enemyNo] = 1;
						pos[enemyNo].x = -14;
						objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
						angle[enemyNo].y = 90;
						objEnemy[enemyNo]->SetRotation(angle[enemyNo]);
					}
				}
			}
		}


		if (lane[enemyNo] == 1)
		{
			if (enemyType[enemyNo] == 0)
			{
				if (!enemyDead[enemyNo])
				{
					pos[enemyNo].z += 0.02;
					objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
					if (pos[enemyNo].z > 18)
					{
						enemyType[enemyNo] = 2;
						pos[enemyNo].z = 18;
						objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
						angle[enemyNo].y = 0;
						objEnemy[enemyNo]->SetRotation(angle[enemyNo]);
					}
				}
			}
			if (enemyType[enemyNo] == 1)
			{
				if (!enemyDead[enemyNo])
				{
					pos[enemyNo].z -= 0.02;
					objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
					if (pos[enemyNo].z < -18)
					{
						enemyType[enemyNo] = 3;
						pos[enemyNo].z = -18;
						objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
						angle[enemyNo].y = 180;
						objEnemy[enemyNo]->SetRotation(angle[enemyNo]);
					}
				}
			}
			if (enemyType[enemyNo] == 2)
			{
				if (!enemyDead[enemyNo])
				{
					pos[enemyNo].x += 0.02;
					objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
					if (pos[enemyNo].x > 18)
					{
						enemyType[enemyNo] = 1;
						pos[enemyNo].x = 18;
						objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
						angle[enemyNo].y = 90;
						objEnemy[enemyNo]->SetRotation(angle[enemyNo]);
					}
				}
			}
			if (enemyType[enemyNo] == 3)
			{
				if (!enemyDead[enemyNo])
				{
					pos[enemyNo].x -= 0.02;
					objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
					if (pos[enemyNo].x < -18)
					{
						enemyType[enemyNo] = 0;
						pos[enemyNo].x = -18;
						objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
						angle[enemyNo].y = 270;
						objEnemy[enemyNo]->SetRotation(angle[enemyNo]);
					}
				}
			}
		}

		if (lane[enemyNo] == 2)
		{
			if (enemyType[enemyNo] == 0)
			{
				if (!enemyDead[enemyNo])
				{
					pos[enemyNo].z += 0.02;
					objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
					if (pos[enemyNo].z > 22)
					{
						enemyType[enemyNo] = 3;
						pos[enemyNo].z = 22;
						objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
						angle[enemyNo].y = 180;
						objEnemy[enemyNo]->SetRotation(angle[enemyNo]);
					}
				}
			}
			if (enemyType[enemyNo] == 1)
			{
				if (!enemyDead[enemyNo])
				{
					pos[enemyNo].z -= 0.02;
					objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
					if (pos[enemyNo].z < -22)
					{
						enemyType[enemyNo] = 2;
						pos[enemyNo].z = -22;
						objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
						angle[enemyNo].y = 0;
						objEnemy[enemyNo]->SetRotation(angle[enemyNo]);
					}
				}
			}
			if (enemyType[enemyNo] == 2)
			{
				if (!enemyDead[enemyNo])
				{
					pos[enemyNo].x += 0.02;
					objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
					if (pos[enemyNo].x > 22)
					{
						enemyType[enemyNo] = 0;
						pos[enemyNo].x = 22;
						objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
						angle[enemyNo].y = 270;
						objEnemy[enemyNo]->SetRotation(angle[enemyNo]);
					}
				}
			}
			if (enemyType[enemyNo] == 3)
			{
				if (!enemyDead[enemyNo])
				{
					pos[enemyNo].x -= 0.02;
					objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
					if (pos[enemyNo].x < -22)
					{
						enemyType[enemyNo] = 1;
						pos[enemyNo].x = -22;
						objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
						angle[enemyNo].y = 90;
						objEnemy[enemyNo]->SetRotation(angle[enemyNo]);
					}
				}
			}
		}
	}
}

void Enemy::Explosion(Player* player, MapChip* mapChip)
{
	for (int enemyNo = 0; enemyNo < enemyMaxNo; enemyNo++)
	{
		if (!enemyDead[enemyNo])
		{
			
			for (int i = 0; i < 20; i++)
			{
				if (player->GetBomPos(i).x - 3.5f <= pos[enemyNo].x &&
					player->GetBomPos(i).x + 3.5f >= pos[enemyNo].x &&
					player->GetBomPos(i).z - 3.5f <= pos[enemyNo].z &&
					player->GetBomPos(i).z + 3.5f >= pos[enemyNo].z)
				{
					player->SetEffectTimer(i);
					player->SetWallFlag(i);
					score += 1000;
					scorePluse = true;
					//player->SetPlayCount();
					killCount++;
					pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
					enemyDead[enemyNo] = true;
					player->SetBomEffectMode(i, 2);//花火エフェクト発生
					player->SetBomAlive(i);
				}

				/*if (player->GetBomPos(i).z - 2 <= pos[enemyNo].z &&
					player->GetBomPos(i).z + 2 >= pos[enemyNo].z &&
					player->GetBomPos(i).x - 2 <= pos[enemyNo].x &&
					player->GetBomPos(i).x + 2 >= pos[enemyNo].x)
				{
					player->SetEffectTimer(i);
					player->SetWallFlag(i);
					score += 1000;
					player->SetPlayCount();
					killCount++;
					enemyDead[enemyNo] = true;
				}*/

				if (player->GetExplosion(i) == true)
				{
					/*if (player->GetBomPos(i).x - 2 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 2 >= pos[enemyNo].x &&
						player->GetBomPos(i).z - 2 <= pos[enemyNo].z &&
						player->GetBomPos(i).z + 2 >= pos[enemyNo].z)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
					}*/
					if (player->GetBomPos(i).x - 3 - 4 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 3 - 4 >= pos[enemyNo].x &&
						player->GetBomPos(i).z - 3 <= pos[enemyNo].z &&
						player->GetBomPos(i).z + 3 >= pos[enemyNo].z && player->GetLv(i) >= 2)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).x - 3 - 8 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 3 - 8 >= pos[enemyNo].x &&
						player->GetBomPos(i).z - 3 <= pos[enemyNo].z &&
						player->GetBomPos(i).z + 3 >= pos[enemyNo].z && player->GetLv(i) >= 3)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).x - 3 - 12 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 3 - 12 >= pos[enemyNo].x &&
						player->GetBomPos(i).z - 3 <= pos[enemyNo].z &&
						player->GetBomPos(i).z + 3 >= pos[enemyNo].z && player->GetLv(i) >= 4)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).x - 3 - 16 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 3 - 16 >= pos[enemyNo].x &&
						player->GetBomPos(i).z - 3 <= pos[enemyNo].z &&
						player->GetBomPos(i).z + 3 >= pos[enemyNo].z && player->GetLv(i) >= 5)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).x - 3 - 20 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 3 - 20 >= pos[enemyNo].x &&
						player->GetBomPos(i).z - 3 <= pos[enemyNo].z &&
						player->GetBomPos(i).z + 3 >= pos[enemyNo].z && player->GetLv(i) >= 6)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).x - 3 - 24 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 3 - 24 >= pos[enemyNo].x &&
						player->GetBomPos(i).z - 3 <= pos[enemyNo].z &&
						player->GetBomPos(i).z + 3 >= pos[enemyNo].z && player->GetLv(i) >= 7)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).x - 3 - 28 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 3 - 28 >= pos[enemyNo].x &&
						player->GetBomPos(i).z - 3 <= pos[enemyNo].z &&
						player->GetBomPos(i).z + 3 >= pos[enemyNo].z && player->GetLv(i) >= 8)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}


					if (player->GetBomPos(i).x + 3 + 4 >= pos[enemyNo].x &&
						player->GetBomPos(i).x - 3 + 4 <= pos[enemyNo].x &&
						player->GetBomPos(i).z - 3 <= pos[enemyNo].z &&
						player->GetBomPos(i).z + 3 >= pos[enemyNo].z && player->GetLv(i) >= 2)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).x + 3 + 8 >= pos[enemyNo].x &&
						player->GetBomPos(i).x - 3 + 8 <= pos[enemyNo].x &&
						player->GetBomPos(i).z - 3 <= pos[enemyNo].z &&
						player->GetBomPos(i).z + 3 >= pos[enemyNo].z && player->GetLv(i) >= 3)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).x + 3 + 12 >= pos[enemyNo].x &&
						player->GetBomPos(i).x - 3 + 12 <= pos[enemyNo].x &&
						player->GetBomPos(i).z - 3 <= pos[enemyNo].z &&
						player->GetBomPos(i).z + 3 >= pos[enemyNo].z && player->GetLv(i) >= 4)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).x + 3 + 16 >= pos[enemyNo].x &&
						player->GetBomPos(i).x - 3 + 16 <= pos[enemyNo].x &&
						player->GetBomPos(i).z - 3 <= pos[enemyNo].z &&
						player->GetBomPos(i).z + 3 >= pos[enemyNo].z && player->GetLv(i) >= 5)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).x + 3 + 20 >= pos[enemyNo].x &&
						player->GetBomPos(i).x - 3 + 20 <= pos[enemyNo].x &&
						player->GetBomPos(i).z - 3 <= pos[enemyNo].z &&
						player->GetBomPos(i).z + 3 >= pos[enemyNo].z && player->GetLv(i) >= 6)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).x + 3 + 24 >= pos[enemyNo].x &&
						player->GetBomPos(i).x - 3 + 24 <= pos[enemyNo].x &&
						player->GetBomPos(i).z - 3 <= pos[enemyNo].z &&
						player->GetBomPos(i).z + 3 >= pos[enemyNo].z && player->GetLv(i) >= 7)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).x + 3 + 28 >= pos[enemyNo].x &&
						player->GetBomPos(i).x - 3 + 28 <= pos[enemyNo].x &&
						player->GetBomPos(i).z - 3 <= pos[enemyNo].z &&
						player->GetBomPos(i).z + 3 >= pos[enemyNo].z && player->GetLv(i) >= 8)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}


					if (player->GetBomPos(i).z - 3 <= pos[enemyNo].z &&
						player->GetBomPos(i).z + 3 >= pos[enemyNo].z &&
						player->GetBomPos(i).x - 3 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 3 >= pos[enemyNo].x)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).z + 3 - 4 >= pos[enemyNo].z &&
						player->GetBomPos(i).z - 3 - 4 <= pos[enemyNo].z &&
						player->GetBomPos(i).x - 3 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 3 >= pos[enemyNo].x && player->GetLv(i) >= 2)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).z + 3 - 8 >= pos[enemyNo].z &&
						player->GetBomPos(i).z - 3 - 8 <= pos[enemyNo].z &&
						player->GetBomPos(i).x - 3 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 3 >= pos[enemyNo].x && player->GetLv(i) >= 3)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).z + 3 - 12 >= pos[enemyNo].z &&
						player->GetBomPos(i).z - 3 - 12 <= pos[enemyNo].z &&
						player->GetBomPos(i).x - 3 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 3 >= pos[enemyNo].x && player->GetLv(i) >= 4)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).z + 3 - 16 >= pos[enemyNo].z &&
						player->GetBomPos(i).z - 3 - 16 <= pos[enemyNo].z &&
						player->GetBomPos(i).x - 3 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 3 >= pos[enemyNo].x && player->GetLv(i) >= 5)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).z + 3 - 20 >= pos[enemyNo].z &&
						player->GetBomPos(i).z - 3 - 20 <= pos[enemyNo].z &&
						player->GetBomPos(i).x - 3 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 3 >= pos[enemyNo].x && player->GetLv(i) >= 6)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).z + 3 - 24 >= pos[enemyNo].z &&
						player->GetBomPos(i).z - 3 - 24 <= pos[enemyNo].z &&
						player->GetBomPos(i).x - 3 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 3 >= pos[enemyNo].x && player->GetLv(i) >= 7)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).z + 3 - 28 >= pos[enemyNo].z &&
						player->GetBomPos(i).z - 3 - 28 <= pos[enemyNo].z &&
						player->GetBomPos(i).x - 3 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 3 >= pos[enemyNo].x && player->GetLv(i) >= 8)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}



					if (player->GetBomPos(i).z + 3 + 4 >= pos[enemyNo].z &&
						player->GetBomPos(i).z - 3 + 4 <= pos[enemyNo].z &&
						player->GetBomPos(i).x - 3 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 3 >= pos[enemyNo].x && player->GetLv(i) >= 2)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).z + 3 + 8 >= pos[enemyNo].z &&
						player->GetBomPos(i).z - 3 + 8 <= pos[enemyNo].z &&
						player->GetBomPos(i).x - 3 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 3 >= pos[enemyNo].x && player->GetLv(i) >= 3)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).z + 3 + 12 >= pos[enemyNo].z &&
						player->GetBomPos(i).z - 3 + 12 <= pos[enemyNo].z &&
						player->GetBomPos(i).x - 3 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 3 >= pos[enemyNo].x && player->GetLv(i) >= 4)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).z + 3 + 16 >= pos[enemyNo].z &&
						player->GetBomPos(i).z - 3 + 16 <= pos[enemyNo].z &&
						player->GetBomPos(i).x - 3 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 3 >= pos[enemyNo].x && player->GetLv(i) >= 5)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).z + 3 + 20 >= pos[enemyNo].z &&
						player->GetBomPos(i).z - 3 + 20 <= pos[enemyNo].z &&
						player->GetBomPos(i).x - 3 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 3 >= pos[enemyNo].x && player->GetLv(i) >= 6)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).z + 3 + 24 >= pos[enemyNo].z &&
						player->GetBomPos(i).z - 3 + 24 <= pos[enemyNo].z &&
						player->GetBomPos(i).x - 3 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 3 >= pos[enemyNo].x && player->GetLv(i) >= 7)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					if (player->GetBomPos(i).z + 3 + 28 >= pos[enemyNo].z &&
						player->GetBomPos(i).z - 3 + 28 <= pos[enemyNo].z &&
						player->GetBomPos(i).x - 3 <= pos[enemyNo].x &&
						player->GetBomPos(i).x + 3 >= pos[enemyNo].x && player->GetLv(i) >= 8)
					{
						score += 1000 * player->GetLv(i);
						player->SetPlayCount();
						killCount++;
						enemyDead[enemyNo] = true;
						pos[enemyNo] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
						scorePluse = true;
					}
					
				}
				objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
			}
		}
	}
}

void Enemy::EnemyExplosion(Player* player, MapChip* mapChip)
{
	for (int enemyNo = 0; enemyNo < enemyMaxNo; enemyNo++)
	{
		for (int i = 0; i < 3; i++)
		{
			bool checkEnd = false;
			if (player->GetExplosion(i) == true)
			{
				if (player->GetBomPos(i).x == pos[enemyNo].x && player->GetBomPos(i).z + 4 == pos[enemyNo].z)
				{
					pos[enemyNo].z += 4;
					if (enemyY[enemyNo] == 7 || mapChip->GetWallFlag(enemyX[enemyNo], enemyY[enemyNo] + 1))
					{
						pos[enemyNo].z -= 4;
						enemyLv[enemyNo] = 2;
						returnCount[enemyNo] += 3;
					}
					objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
					checkEnd = true;
				}
				if (player->GetBomPos(i).x == pos[enemyNo].x && player->GetBomPos(i).z - 4 == pos[enemyNo].z)
				{
					pos[enemyNo].z -= 4;
					if (enemyY == 0 || mapChip->GetWallFlag(enemyX[enemyNo], enemyY[enemyNo] - 1))
					{
						pos[enemyNo].z += 4;
						enemyLv[enemyNo] = 2;
						returnCount[enemyNo] += 3;
					}
					objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
					checkEnd = true;
				}
				if (player->GetBomPos(i).x - 4 == pos[enemyNo].x && player->GetBomPos(i).z == pos[enemyNo].z)
				{
					pos[enemyNo].x -= 4;
					if (enemyY == 0 || mapChip->GetWallFlag(enemyX[enemyNo] - 1, enemyY[enemyNo]))
					{
						pos[enemyNo].x += 4;
						enemyLv[enemyNo] = 2;
						returnCount[enemyNo] += 3;
					}
					objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
					checkEnd = true;
				}
				if (player->GetBomPos(i).x + 4 == pos[enemyNo].x && player->GetBomPos(i).z == pos[enemyNo].z)
				{
					pos[enemyNo].x += 4;
					if (enemyY == 0 || mapChip->GetWallFlag(enemyX[enemyNo] + 1, enemyY[enemyNo]))
					{
						pos[enemyNo].x -= 4;
						enemyLv[enemyNo] = 2;
						returnCount[enemyNo] += 2;
					}
					objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
					checkEnd = true;
				}
				if (checkEnd)
				{

					player->SetBomPos(i);
				}
			}
		}
	}
}

void Enemy::EnemyFire(MapChip* mapChip)
{

	for (int i = 0; i < 12; i++)
	{
		int mapY = 0;
		int mapX = 0;

		if (enemyDead[i] == false)
		{
  			mapY = (pos[i].z / 4) + ((12 + 1) / 2);
			mapX = (pos[i].x / 4) + ((12 + 1) / 2);
			if (mapChip->GetWallFlag(mapX, mapY) == 2)
			{
				pos[i] = { 500.0f,0.0f,0.0f };//プレイヤーの位置
				objEnemy[i]->SetPosition(pos[i]);
				enemyDead[i] = true;
				score += 100;
				scorePluse = true;
			}
		}
	}
}
