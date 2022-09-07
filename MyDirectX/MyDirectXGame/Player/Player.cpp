#include "Player.h"
#include "../input/Input.h"
using namespace DirectX;

void Player::Initialize(MapChip* map)
{
	modelPlayer = Model::CreateFromObject("attacker1", false);

	objPlayer = Object3d::Create(modelPlayer);
	objPlayer->SetScale(XMFLOAT3({ 1, 1, 1 }));
	pos = XMFLOAT3({ 3 * 4.0f - (MapValue * 4.0f / 2) + 2, 2.0f, 3 * 4.0f - (MapValue * 4.0f / 2) + 2 });
	objPlayer->SetPosition(pos);


	modelBom = Model::CreateFromObject("bom", false);
	for (int i = 0; i < 3; i++)
	{
		objBom[i] = Object3d::Create(modelBom);
		objBom[i]->SetScale(XMFLOAT3({ 0.5, 0.5, 0.5 }));
		bomPos[i] = XMFLOAT3({ 4 * 4.0f - (MapValue * 4.0f / 2) + 2, 1.0f, 4 * 4.0f - (MapValue * 4.0f / 2) + 2 });
		objBom[i]->SetPosition(bomPos[i]);
	}
}

void Player::InitializeValue()
{
}

void Player::Update(MapChip* map)
{
	Move(map);
	playerAngle();
	PutBom(map);
	objPlayer->Update();
	for (int i = 0; i < 3; i++)
	{
		objBom[i]->Update();
	}
	Explosion(map);
}

void Player::Draw()
{
	objPlayer->Draw();
	for (int i = 0; i < 3; i++)
	{
		if (bomAlive[i] == true)
		{
			objBom[i]->Draw();
		}
	}
}

void Player::DrawSprite()
{
}

void Player::Move(MapChip* map)
{
	mapY = (pos.z / 4) + ((8 + 1) / 2);
	mapX = (pos.x / 4) + ((8 + 1) / 2);

	if (Input::GetInstance()->KeybordTrigger(DIK_W) && mapY != 7 && map->GetWallFlag(mapX, mapY + 1) == 0)
	{
		pos.z += moveSpeed;// z座標を更新
		angle.y = 180;
		for (int i = 0; i < 3; i++)
		{
			if (bomAlive[i])
			{
				explosionCount[i]++;
			}
		}
	}
	if (Input::GetInstance()->KeybordTrigger(DIK_A) && mapX != 0 && map->GetWallFlag(mapX-1, mapY) == 0)
	{
		pos.x -= moveSpeed;// x座標を更新
		angle.y = 90;
		for (int i = 0; i < 3; i++)
		{
			if (bomAlive[i])
			{
				explosionCount[i]++;
			}
		}
	}
	if (Input::GetInstance()->KeybordTrigger(DIK_S) && mapY != 0 && map->GetWallFlag(mapX, mapY - 1) == 0)
	{
		pos.z -= moveSpeed;// z座標を更新
		angle.y = 0;
		for (int i = 0; i < 3; i++)
		{
			if (bomAlive[i])
			{
				explosionCount[i]++;
			}
		}
	}
	if (Input::GetInstance()->KeybordTrigger(DIK_D) && mapX != 7 && map->GetWallFlag(mapX + 1, mapY) == 0)
	{
		pos.x += moveSpeed;// x座標を更新
		angle.y = 270;
		for (int i = 0; i < 3; i++)
		{
			if (bomAlive[i])
			{
				explosionCount[i]++;
			}
		}
	}
	objPlayer->SetPosition(pos);
	objPlayer->SetRotation(angle);
}

void Player::playerAngle()
{
	if (Input::GetInstance()->KeybordTrigger(DIK_UP))
	{
		angle.y = 180;
	}
	else if (Input::GetInstance()->KeybordTrigger(DIK_DOWN))
	{
		angle.y = 0;
	}
	else if (Input::GetInstance()->KeybordTrigger(DIK_RIGHT))
	{
		angle.y = 270;
	}
	else if (Input::GetInstance()->KeybordTrigger(DIK_LEFT))
	{
		angle.y = 90;
	}
	objPlayer->SetRotation(angle);
}

void Player::PutBom(MapChip* map)
{
	if (Input::GetInstance()->KeybordTrigger(DIK_SPACE))
	{
		if(angle.y == 180 && mapY != 7 && map->GetWallFlag(mapX, mapY + 1) == 0)
		{ 
			for (int i = 0; i < 3; i++)
			{
				if (bomAlive[i])
				{
					explosionCount[i]++;
				}
			}
			bomPos[bomNo] = XMFLOAT3({ mapX * 4.0f - (MapValue * 4.0f / 2) + 2, 1.0f, (mapY + 1) * 4.0f - (MapValue * 4.0f / 2) + 2 });
			objBom[bomNo]->SetPosition(bomPos[bomNo]);
			bomAlive[bomNo] = true;
			putFlag = true;
			bomY[bomNo] = (bomPos[bomNo].z / 4) + ((8 + 1) / 2);//盤面の位置
			bomX[bomNo] = (bomPos[bomNo].x / 4) + ((8 + 1) / 2);//盤面の位置
			map->SetWallFlag(bomX[bomNo], bomY[bomNo], 2);
		}
		else if (angle.y == 90 && mapX != 0 && map->GetWallFlag(mapX-1, mapY) == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				if (bomAlive[i])
				{
					explosionCount[i]++;
				}
			}
			bomPos[bomNo] = XMFLOAT3({ (mapX - 1) * 4.0f - (MapValue * 4.0f / 2) + 2, 1.0f, mapY * 4.0f - (MapValue * 4.0f / 2) + 2 });
			objBom[bomNo]->SetPosition(bomPos[bomNo]);
			bomAlive[bomNo] = true;
			putFlag = true;
			bomY[bomNo] = (bomPos[bomNo].z / 4) + ((8 + 1) / 2);//盤面の位置
			bomX[bomNo] = (bomPos[bomNo].x / 4) + ((8 + 1) / 2);//盤面の位置
			map->SetWallFlag(bomX[bomNo], bomY[bomNo], 2);
		}
		else if (angle.y == 0 && mapY != 0 && map->GetWallFlag(mapX, mapY - 1) == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				if (bomAlive[i])
				{
					explosionCount[i]++;
				}
			}
			bomPos[bomNo] = XMFLOAT3({ mapX * 4.0f - (MapValue * 4.0f / 2) + 2, 1.0f, (mapY - 1) * 4.0f - (MapValue * 4.0f / 2) + 2 });
			objBom[bomNo]->SetPosition(bomPos[bomNo]);
			bomAlive[bomNo] = true;
			putFlag = true;
			bomY[bomNo] = (bomPos[bomNo].z / 4) + ((8 + 1) / 2);//盤面の位置
			bomX[bomNo] = (bomPos[bomNo].x / 4) + ((8 + 1) / 2);//盤面の位置
			map->SetWallFlag(bomX[bomNo], bomY[bomNo], 2);
		}
		else if (angle.y == 270 && mapX != 7 && map->GetWallFlag(mapX+1, mapY) == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				if (bomAlive[i])
				{
					explosionCount[i]++;
				}
			}
			bomPos[bomNo] = XMFLOAT3({ (mapX + 1) * 4.0f - (MapValue * 4.0f / 2) + 2, 1.0f, mapY * 4.0f - (MapValue * 4.0f / 2) + 2 });
			objBom[bomNo]->SetPosition(bomPos[bomNo]);
			bomAlive[bomNo] = true;
			putFlag = true;
			bomY[bomNo] = (bomPos[bomNo].z / 4) + ((8 + 1) / 2);//盤面の位置
			bomX[bomNo] = (bomPos[bomNo].x / 4) + ((8 + 1) / 2);//盤面の位置
			map->SetWallFlag(bomX[bomNo], bomY[bomNo], 2);
		}
		if (putFlag == true)
		{
			if (bomNo != 2)
			{
				bomNo++;
			}
			else if (bomNo == 2)
			{
				bomNo = 0;
			}
			putFlag = false;
		}
	}
}

void Player::Explosion(MapChip* map)
{
	for (int i = 0; i < 3; i++)
	{
		if (explosionCount[i] > 2)
		{		
				//左
				bool cansel1 = false;
				if (map->GetWallFlag(bomX[i] - 1, bomY[i]) == 1)
				{
					if (bomX[i] - 1 == 0) { cansel1 = true; }
					if (cansel1 == false)
					{
						map->SetWallFlag(bomX[i] - 2, bomY[i], 1);
						map->SetWallFlag(bomX[i] - 1, bomY[i], 0);
					}
				}

				//右
				bool cansel2 = false;
				if (map->GetWallFlag(bomX[i] + 1, bomY[i]) == 1)
				{
					if (bomX[i] + 1 == 7) { cansel2 = true; }
					if (cansel2 == false)
					{
						map->SetWallFlag(bomX[i] + 2, bomY[i], 1);
						map->SetWallFlag(bomX[i] + 1, bomY[i], 0);
					}
				}
				
				//上
				bool cansel3 = false;
				if (map->GetWallFlag(bomX[i], bomY[i] + 1) == 1)
				{
					if (bomY[i] + 1 == 7) { cansel3 = true; }
					if (cansel3 == false)
					{
						map->SetWallFlag(bomX[i], bomY[i] + 2, 1);
						map->SetWallFlag(bomX[i], bomY[i] + 1, 0);
					}
				}

				//下
				bool cansel4 = false;
				if (map->GetWallFlag(bomX[i], bomY[i] - 1) == 1)
				{
					if (bomY[i] - 1 == 0) { cansel4 = true; }
					if (cansel4 == false)
					{
						map->SetWallFlag(bomX[i], bomY[i] - 2, 1);
						map->SetWallFlag(bomX[i], bomY[i] - 1, 0);
					}
				}
			bomAlive[i] = false;
			map->SetWallFlag(bomX[i], bomY[i], 0);
			explosionCount[i] = 1;
		}
	}
}
