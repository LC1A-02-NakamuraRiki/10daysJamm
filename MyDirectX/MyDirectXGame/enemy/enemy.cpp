#include "enemy.h"
#include "../collision/Collision.h"
#include "../Effect/Effect.h"
#include<time.h>
#include<random>

void Enemy::Initialize(int x, int y, int moveVector,int enemysNo)
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
	for (int i = 0; i < 12; i++)
	{
		pos[i] = { 0.0f,0.0f,0.0f };//プレイヤーの位置
		angle[i] = { 0.0f,0.0f,0.0f };
		enemyType[i] = HORIZONTAL;
		enemyY[i] = 0;//盤面の位置
		enemyX[i] = 0;//盤面の位置

		enemyDead[i] = true;

		returnCount[i] = 3;
		enemyLv[i] = 1;
	}

	score = 0;

	spawnNum = 2;

	wave = 1;
	killCount = 0;

	for (int enemysNo = 0; enemysNo < 12; enemysNo++)
	{
		enemyType[enemysNo] = 1;
		objEnemy[enemysNo]->SetScale(XMFLOAT3({ 0.75, 0.75, 0.75 }));
		pos[enemysNo] = XMFLOAT3({ 0 * 4.0f - (MapValue * 4.0f / 2) + 2, 1.0f, 0 * 4.0f - (MapValue * 4.0f / 2) + 2 });
		objEnemy[enemysNo]->SetPosition(pos[enemysNo]);
	}
}

void Enemy::enemyCreate()
{
	for (int enemyNo = 0; enemyNo < spawnNum; enemyNo++)
	{
		if (enemyDead[enemyNo] == true)
		{
			std::random_device rnd1;
			std::mt19937 mt1(rnd1());
			std::uniform_int_distribution<>rand5(0, 5);//0~3の範囲
			int spown_cnt = rand5(mt1);

			if (spown_cnt == 5)
			{
				std::random_device rnd2;
				std::mt19937 mt2(rnd2());
				std::uniform_int_distribution<>rand3(0, 3);//0~3の範囲
				int vector = rand3(mt2);



				int x = 0;
				int y = 0;
				int moveVector = 0;
				if (vector == 0)
				{
					std::random_device rnd3;
					std::mt19937 mt3(rnd3());
					std::uniform_int_distribution<>rand7(0, 7);//0~3の範囲
					int random = rand7(mt3);
					x = random;
					y = 7;
					angle[enemyNo].y = 90;
					objEnemy[enemyNo]->SetRotation(angle[enemyNo]);
					moveVector = VERTICAL;
				}
				else if (vector == 1)
				{
					std::random_device rnd3;
					std::mt19937 mt3(rnd3());
					std::uniform_int_distribution<>rand7(0, 7);//0~3の範囲
					int random = rand7(mt3);
					x = random;
					y = 0;
					angle[enemyNo].y = 270;
					objEnemy[enemyNo]->SetRotation(angle[enemyNo]);
					moveVector = VERTICAL;
				}
				else if (vector == 2)
				{
					std::random_device rnd3;
					std::mt19937 mt3(rnd3());
					std::uniform_int_distribution<>rand7(0, 7);//0~3の範囲
					int random = rand7(mt3);
					x = 7;
					y = random;
					angle[enemyNo].y = 0;
					objEnemy[enemyNo]->SetRotation(angle[enemyNo]);
					moveVector = HORIZONTAL;
				}
				else if (vector == 3)
				{
					std::random_device rnd3;
					std::mt19937 mt3(rnd3());
					std::uniform_int_distribution<>rand7(0, 7);//0~3の範囲
					int random = rand7(mt3);
					x = 0;
					y = random;
					angle[enemyNo].y = 180;
					objEnemy[enemyNo]->SetRotation(angle[enemyNo]);
					moveVector = HORIZONTAL;
				}
				InitializeValue(x, y, moveVector, enemyNo);
			}
		}
	}
}

void Enemy::InitializeValue(int x, int y, int moveVector, int enemysNo)
{
	pos[enemysNo] = { 0.0f,0.0f,0.0f };
	angle[enemysNo] = { 0.0f,0.0f,0.0f };
	enemyType[enemysNo] = moveVector;
	enemyY[enemysNo] = 0;//盤面の位置
	enemyX[enemysNo] = 0;//盤面の位置
	returnCount[enemysNo] = 3;
	enemyLv[enemysNo] = 1;
	pos[enemysNo] = XMFLOAT3({ x * 4.0f - (MapValue * 4.0f / 2) + 2, 1.0f, y * 4.0f - (MapValue * 4.0f / 2) + 2 });
	objEnemy[enemysNo]->SetPosition(pos[enemysNo]);
	enemyDead[enemysNo] = false;
}

void Enemy::Update(Player* player, MapChip* mapChip)
{
	
	enemyCreate();
	
	for (int enemyNo = 0; enemyNo < enemyMaxNo; enemyNo++)
	{
		EnemyExplosion(player, mapChip);
		objEnemy[enemyNo]->Update();
		
		Move(player, mapChip);
		
		Explosion(player, mapChip);
		objEnemy[enemyNo]->SetRotation(angle[enemyNo]);
	}

	if (killCount > 25) { spawnNum = 11; wave = 2; }
	else if (killCount > 20) { spawnNum = 9; wave = 3;}
	else if (killCount > 15) { spawnNum = 7; wave = 4;}
	else if (killCount > 10) { spawnNum = 5; wave = 5;}
	else if (killCount > 5) { spawnNum = 3; wave = 6;}
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
		if (!enemyDead[enemyNo])
		{
			enemyY[enemyNo] = (pos[enemyNo].z / 4) + ((8 + 1) / 2);//盤面の位置
			enemyX[enemyNo] = (pos[enemyNo].x / 4) + ((8 + 1) / 2);//盤面の位置
			if (player->GetTurnFlag(enemyNo) == true)
			{
				if (enemyType[enemyNo] == HORIZONTAL)
				{
					for (int i = 0; i < enemyLv[enemyNo]; i++)
					{
						if (enemyX[enemyNo] == 7 || mapChip->GetWallFlag(enemyX[enemyNo] + 1, enemyY[enemyNo]) == 1) { angle[enemyNo].y = 180; returnCount[enemyNo]--; }
						if (enemyX[enemyNo] == 0 || mapChip->GetWallFlag(enemyX[enemyNo] - 1, enemyY[enemyNo]) == 1) { angle[enemyNo].y = 0; returnCount[enemyNo]--; }
						if (angle[enemyNo].y == 0)
						{
							pos[enemyNo].x += 4;
							objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
							enemyY[enemyNo] = (pos[enemyNo].z / 4) + ((8 + 1) / 2);//盤面の位置
							enemyX[enemyNo] = (pos[enemyNo].x / 4) + ((8 + 1) / 2);//盤面の位置
							Explosion(player, mapChip);
							player->SetTurnFlag(false, enemyNo);
						}
						if (angle[enemyNo].y == 180)
						{
							pos[enemyNo].x -= 4;
							objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
							enemyY[enemyNo] = (pos[enemyNo].z / 4) + ((8 + 1) / 2);//盤面の位置
							enemyX[enemyNo] = (pos[enemyNo].x / 4) + ((8 + 1) / 2);//盤面の位置
							Explosion(player, mapChip);
							player->SetTurnFlag(false, enemyNo);
						}
					}
				}
				if (enemyType[enemyNo] == VERTICAL)
				{
					for (int i = 0; i < enemyLv[enemyNo]; i++)
					{
						if (enemyY[enemyNo] == 7 || mapChip->GetWallFlag(enemyX[enemyNo], enemyY[enemyNo] + 1) == 1) { angle[enemyNo].y = 90; returnCount[enemyNo]--; }
						if (enemyY[enemyNo] == 0 || mapChip->GetWallFlag(enemyX[enemyNo], enemyY[enemyNo] - 1) == 1) { angle[enemyNo].y = 270; returnCount[enemyNo]--; }
						if (angle[enemyNo].y == 270)
						{
							pos[enemyNo].z += 4;
							objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
							enemyY[enemyNo] = (pos[enemyNo].z / 4) + ((8 + 1) / 2);//盤面の位置
							enemyX[enemyNo] = (pos[enemyNo].x / 4) + ((8 + 1) / 2);//盤面の位置
							Explosion(player, mapChip);
							player->SetTurnFlag(false, enemyNo);
						}
						if (angle[enemyNo].y == 90)
						{
							pos[enemyNo].z -= 4;
							objEnemy[enemyNo]->SetPosition(pos[enemyNo]);
							enemyY[enemyNo] = (pos[enemyNo].z / 4) + ((8 + 1) / 2);//盤面の位置
							enemyX[enemyNo] = (pos[enemyNo].x / 4) + ((8 + 1) / 2);//盤面の位置
							Explosion(player, mapChip);
							player->SetTurnFlag(false, enemyNo);
						}
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
			if (pos[enemyNo].x == player->GetBomPos(0).x && pos[enemyNo].z == player->GetBomPos(0).z && player->GetBomAlive(0) == true)
			{
				player->enemyExplosion(0, mapChip);
				if (enemyLv[enemyNo] == 1)
				{
					score += 1000;
					killCount++;
				}
				else if (enemyLv[enemyNo] == 2)
				{
					score += 3000;
					killCount++;
				}
				player->SetPlayCount();
				enemyDead[enemyNo] = true;
			}
			if (pos[enemyNo].x == player->GetBomPos(1).x && pos[enemyNo].z == player->GetBomPos(1).z && player->GetBomAlive(1) == true)
			{
				player->enemyExplosion(1, mapChip);
				if (enemyLv[enemyNo] == 1)
				{
					score += 1000;
					killCount++;
				}
				else if (enemyLv[enemyNo] == 2)
				{
					score += 3000;
					killCount++;
				}
				player->SetPlayCount();
				enemyDead[enemyNo] = true;
			}
			if (pos[enemyNo].x == player->GetBomPos(2).x && pos[enemyNo].z == player->GetBomPos(2).z && player->GetBomAlive(2) == true)
			{
				player->enemyExplosion(2, mapChip);
				if (enemyLv[enemyNo] == 1)
				{
					score += 1000;
					killCount++;
				}
				else if (enemyLv[enemyNo] == 2)
				{
					score += 3000;
					killCount++;
				}
				player->SetPlayCount();
				enemyDead[enemyNo] = true;
			}
			if (returnCount[enemyNo] == 0)
			{
				enemyDead[enemyNo] = true;
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
