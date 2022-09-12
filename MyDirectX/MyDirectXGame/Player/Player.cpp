#include "Player.h"
#include "../input/Input.h"
#include "../Effect/Effect.h"
using namespace DirectX;

void Player::Initialize(MapChip* map)
{
	modelPlayer = Model::CreateFromObject("attacker1", false);

	objPlayer = Object3d::Create(modelPlayer);
	objPlayer->SetScale(XMFLOAT3({ 1, 1, 1 }));
	pos = XMFLOAT3({ 5 * 4.0f - (MapValue * 4.0f / 2) + 2, 2.0f, 3 * 4.0f - (MapValue * 4.0f / 2) + 2 });
	objPlayer->SetPosition(pos);


	modelBom[0] = Model::CreateFromObject("bom_01", false);
	modelBom[1] = Model::CreateFromObject("bom_02", false);
	modelBom[2] = Model::CreateFromObject("bom_03", false);
	modelBom[3] = Model::CreateFromObject("bom_04", false);
	modelBom[4] = Model::CreateFromObject("bom_05", false);
	modelBom[5] = Model::CreateFromObject("bom_06", false);
	modelBom[6] = Model::CreateFromObject("bom_07", false);
	modelBom[7] = Model::CreateFromObject("bom_08", false);
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 20; i++)
		{
			objBom[j][i] = Object3d::Create(modelBom[j]);
			objBom[j][i]->SetScale(XMFLOAT3({ 0.5, 0.5, 0.5 }));
			bomPos[i] = XMFLOAT3({ 4 * 4.0f - (MapValue * 4.0f / 2) + 2, 1.0f, 4 * 4.0f - (MapValue * 4.0f / 2) + 2 });
			objBom[j][i]->SetPosition(bomPos[i]);
			objBom[j][i]->SetRotation({0,180,0});
		}
	}
}

void Player::InitializeValue()
{
	mapY = (pos.z / 4) + ((12 + 1) / 2);//盤面の位置
	mapX = (pos.x / 4) + ((12 + 1) / 2);//盤面の位置



	pos = { 4.0f,0.0f,-40.0f };//プレイヤーの位置a
	angle = { 0,0,0 };

	moveSpeed = 4.0f;//歩きの速度

	move = false;

	bomNo = 0;

	for (int j = 0; j < 20; j++)
	{
		bomPos[j] = { 0.0f,0.0f,0.0f };//プレイヤーの位置
		bomAngle[j] = 0;
		bomAlive[j] = false;
		explosionCount[j] = 1;
		putFlag = false;
		bomY[j] = 0;//盤面の位置
		bomX[j] = 0;//盤面の位置
		bomLv[j] = 0;

		turnFlag[j] = false;
		nowExplosion[j] = false;
		playCount = 2400;

		fire = false;
		effectTimer[j] = 0;
		effectMode[j] = 0;

		wallFlag[j] = false;
	}
	for (int j = 0; j < 12; j++)
	{
		lvCount[j] = 1;
	}


	objPlayer->SetScale(XMFLOAT3({ 1, 1, 1 }));
	pos = XMFLOAT3({ 5 * 4.0f - (MapValue * 4.0f / 2) + 2, 2.0f, 3 * 4.0f - (MapValue * 4.0f / 2) + 2 });
	objPlayer->SetPosition(pos);


	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 20; i++)
		{
			objBom[j][i]->SetScale(XMFLOAT3({ 0.5, 0.5, 0.5 }));
			bomPos[i] = XMFLOAT3({ 4 * 4.0f - (MapValue * 4.0f / 2) + 2, 1.0f, 4 * 4.0f - (MapValue * 4.0f / 2) + 2 });
			objBom[j][i]->SetPosition(bomPos[i]);
		}
	}
}

void Player::BomInitialize(int i)
{


	bomPos[i] = { 0.0f,0.0f,0.0f };//プレイヤーの位置
	bomAlive[i] = false;
	explosionCount[i] = 1;
	bomY[i] = 0;//盤面の位置
	bomX[i] = 0;//盤面の位置
	nowExplosion[i] = false;

	putFlag = false;

	turnFlag[i] = false;
	for (int j = 0; j < 8; j++)
	{
		objBom[j][i]->SetScale(XMFLOAT3({ 0.5, 0.5, 0.5 }));
		bomPos[i] = XMFLOAT3({ 4 * 4.0f - (MapValue * 4.0f / 2) + 2, 1.0f, 4 * 4.0f - (MapValue * 4.0f / 2) + 2 });
		objBom[j][i]->SetPosition(bomPos[i]);
	}

}

void Player::Update(MapChip* map, bool countStart, bool start)
{
	for (int i = 0; i < 20; i++)
	{
		if (bomAlive[i] == false)
		{
			BomInitialize(i);
		}
	}
	if (countStart == false)
	{
		playCount--;
	}
	if (start == false)
	{
		Move(map);
		playerAngle();
		PutBom(map);
	}
	objPlayer->Update();
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 20; i++)
		{
			BomEffect(i);//エフェクト更新
			objBom[j][i]->Update();
		}
	}
	Explosion(map);
	Effect::Move(pos, { 1.0f,0.0f,0.2f,0.5f });
}

void Player::Draw()
{
	objPlayer->Draw();

	for (int i = 0; i < 20; i++)
	{

		if (bomAlive[i] == true)
		{
			if (bomLv[i] <= 7)
			{
				objBom[bomLv[i]][i]->Draw();
			}
		}
	}
}

void Player::DrawSprite()
{
}

void Player::Move(MapChip* map)
{

	mapY = (pos.z / 4) + ((12 + 1) / 2);
	mapX = (pos.x / 4) + ((12 + 1) / 2);

	if (Input::GetInstance()->KeybordTrigger(DIK_W) && mapY != 8 && map->GetWallFlag(mapX, mapY + 1) == 0)
	{
		pos.z += moveSpeed;// z座標を更新
		angle.y = 180;
		for (int i = 0; i < 12; i++)
		{
			turnFlag[i] = true;
		}

		move = true;
	}
	if (Input::GetInstance()->KeybordTrigger(DIK_A) && mapX != 3 && map->GetWallFlag(mapX - 1, mapY) == 0)
	{
		pos.x -= moveSpeed;// x座標を更新
		angle.y = 90;
		for (int i = 0; i < 12; i++)
		{
			turnFlag[i] = true;
		}
		move = true;
	}
	if (Input::GetInstance()->KeybordTrigger(DIK_S) && mapY != 3 && map->GetWallFlag(mapX, mapY - 1) == 0)
	{
		pos.z -= moveSpeed;// z座標を更新
		angle.y = 0;
		for (int i = 0; i < 12; i++)
		{
			turnFlag[i] = true;
		}
		move = true;
	}
	if (Input::GetInstance()->KeybordTrigger(DIK_D) && mapX != 8 && map->GetWallFlag(mapX + 1, mapY) == 0)
	{
		pos.x += moveSpeed;// x座標を更新
		angle.y = 270;
		for (int i = 0; i < 12; i++)
		{
			turnFlag[i] = true;
		}
		move = true;
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
		if (angle.y == 180 && map->GetWallFlag(mapX, mapY + 1) == 0)
		{

			bomPos[bomNo] = XMFLOAT3({ pos.x, 1.0f,pos.z + 4 });
			for (int j = 0; j < 8; j++)
			{
				objBom[j][bomNo]->SetPosition(bomPos[bomNo]);
			}
			bomAlive[bomNo] = true;
			putFlag = true;
			bomAngle[bomNo] = 0;
		}

		else if (angle.y == 90 && map->GetWallFlag(mapX - 1, mapY) == 0)
		{
			bomPos[bomNo] = XMFLOAT3({ pos.x - 4, 1.0f,pos.z });
			for (int j = 0; j < 8; j++)
			{
				objBom[j][bomNo]->SetPosition(bomPos[bomNo]);
			}
			bomAlive[bomNo] = true;
			putFlag = true;
			bomAngle[bomNo] = 3;
		}
		else if (angle.y == 0 && map->GetWallFlag(mapX, mapY - 1) == 0)
		{
			bomPos[bomNo] = XMFLOAT3({ pos.x, 1.0f,pos.z - 4 });
			for (int j = 0; j < 8; j++)
			{
				objBom[j][bomNo]->SetPosition(bomPos[bomNo]);
			}
			bomAlive[bomNo] = true;
			putFlag = true;
			bomAngle[bomNo] = 1;
		}
		else if (angle.y == 270 && map->GetWallFlag(mapX + 1, mapY) == 0)
		{
			bomPos[bomNo] = XMFLOAT3({ pos.x + 4, 1.0f,pos.z });
			for (int j = 0; j < 8; j++)
			{
				objBom[j][bomNo]->SetPosition(bomPos[bomNo]);
			}
			bomAlive[bomNo] = true;
			putFlag = true;
			bomAngle[bomNo] = 2;
		}

		if (putFlag == true)
		{
			if (bomNo != 19)
			{
				bomNo++;
				for (int i = 0; i < 12; i++)
				{
					turnFlag[i] = true;
				}
			}
			else if (bomNo == 19)
			{
				bomNo = 0;
				for (int i = 0; i < 12; i++)
				{
					turnFlag[i] = true;
				}
			}
			putFlag = false;
			lvCount[bomNo] = 10;
			bomLv[bomNo] = 0;
		}
	}
	for (int i = 0; i < 20; i++)
	{
		if (bomAngle[i] == 0 && bomAlive[i])
		{
			bomPos[i].z += 0.4;
			lvCount[i]++;
			int bomMapY = ((bomPos[i].z - 2) / 4) + ((12 + 1) / 2);
			int bomMapX = (bomPos[i].x / 4) + ((12 + 1) / 2);
			for (int j = 0; j < 8; j++)
			{
				objBom[j][i]->SetPosition(bomPos[i]);
			}
			for (int j = 0; j < 9; j++)
			{
				if (10 * j == lvCount[i])
				{
					bomLv[i] = j;
				}
			}
			if (bomMapY == 11)
			{
				effectTimer[i] = 10;//エフェクト継続時間
				wallFlag[i] = true;
				nowExplosion[i] = true;
			}
			if (map->ArrayValue(bomPos[i].x, bomPos[i].z + 2.0) == 1)
			{
				effectTimer[i] = 10;//エフェクト継続時間
				wallFlag[i] = true;
				nowExplosion[i] = true;
			}
		}
		if (bomAngle[i] == 1 && bomAlive[i])
		{
			bomPos[i].z -= 0.4;
			lvCount[i]++;
			int bomMapY = ((bomPos[i].z + 2) / 4) + ((12 + 1) / 2);
			int bomMapX = (bomPos[i].x / 4) + ((12 + 1) / 2);
			for (int j = 0; j < 8; j++)
			{
				objBom[j][i]->SetPosition(bomPos[i]);
			}
			for (int j = 0; j < 9; j++)
			{
				if (10 * j == lvCount[i])
				{
					bomLv[i] = j;
				}
			}
			if (bomMapY == 0)
			{
				effectTimer[i] = 10;//エフェクト継続時間
				wallFlag[i] = true;
				nowExplosion[i] = true;
			}
			if (map->ArrayValue(bomPos[i].x, bomPos[i].z - 2.0) == 1)
			{
				effectTimer[i] = 10;//エフェクト継続時間
				wallFlag[i] = true;
				nowExplosion[i] = true;
			}
		}
		if (bomAngle[i] == 2 && bomAlive[i])
		{
			bomPos[i].x += 0.4;
			lvCount[i]++;
			int bomMapY = (bomPos[i].z / 4) + ((12 + 1) / 2);
			int bomMapX = ((bomPos[i].x - 2) / 4) + ((12 + 1) / 2);
			for (int j = 0; j < 8; j++)
			{
				objBom[j][i]->SetPosition(bomPos[i]);
			}
			for (int j = 0; j < 9; j++)
			{
				if (10 * j == lvCount[i])
				{
					bomLv[i] = j;
				}
			}
			if (bomMapX == 11)
			{
				effectTimer[i] = 10;//エフェクト継続時間
				wallFlag[i] = true;
				nowExplosion[i] = true;
			}
			if (map->ArrayValue(bomPos[i].x + 2, bomPos[i].z) == 1)
			{
				effectTimer[i] = 10;//エフェクト継続時間
				wallFlag[i] = true;
				nowExplosion[i] = true;
			}
		}
		if (bomAngle[i] == 3 && bomAlive[i])
		{
			bomPos[i].x -= 0.4;
			lvCount[i]++;
			int bomMapY = (bomPos[i].z / 4) + ((12 + 1) / 2);
			int bomMapX = ((bomPos[i].x + 2) / 4) + ((12 + 1) / 2);
			for (int j = 0; j < 8; j++)
			{
				objBom[j][i]->SetPosition(bomPos[i]);
			}
			for (int j = 0; j < 9; j++)
			{
				if (10 * j == lvCount[i])
				{
					bomLv[i] = j;
				}
			}
			if (bomMapX == 0)
			{
				effectTimer[i] = 10;//エフェクト継続時間
				wallFlag[i] = true;
				nowExplosion[i] = true;
			}
			if (map->ArrayValue(bomPos[i].x - 2, bomPos[i].z) == 1)
			{
				effectTimer[i] = 10;//エフェクト継続時間
				wallFlag[i] = true;
				nowExplosion[i] = true;
			}
		}
	}
}

void Player::Explosion(MapChip* map)
{

	for (int i = 0; i < 20; i++)
	{
		if (nowExplosion[i] == true)
		{
			bomAlive[i] = false;
		}

		if (bomAlive[i])
		{
			Effect::Move(bomPos[i], { 1.0f,0.0f,0.2f,1.0f });
		}
		//エフェクト発生
		SetBomEffectMode(i, 1);
	}
}

void Player::SetBomEffectMode(int num, int mode)
{
	if (effectTimer[num] == 10)
	{
		effectMode[num] = mode;
		effectPos[num] = bomPos[num];
		Effect::GetRandomColor();
	}
}

void Player::BomEffect(int num)
{
	switch (effectMode[num])
	{
	case 0:

		return;

	case 1:
		//爆発
		for (int j = 0; j < bomLv[num]; j++)
		{
			if (j == 0)
			{
				//爆発の中心
				Effect::Explosion({ effectPos[num].x, effectPos[num].y, effectPos[num].z });
			}
			else
			{
				//爆弾のレベルに応じて爆発の数を増やす
				Effect::Explosion({ effectPos[num].x + 4 * j, effectPos[num].y, effectPos[num].z });
				Effect::Explosion({ effectPos[num].x - 4 * j, effectPos[num].y, effectPos[num].z });
				Effect::Explosion({ effectPos[num].x, effectPos[num].y, effectPos[num].z + 4 * j });
				Effect::Explosion({ effectPos[num].x, effectPos[num].y, effectPos[num].z - 4 * j });
			}
		}

		effectTimer[num]--;

		break;

	case 2:
		//花火
		if (effectTimer[num] >= 4)
		{
			effectPos[num].y++;
			Effect::Move(effectPos[num], { 0.0f,10.0f,10.0f,1.0f });//花火打ち上げ
		}
		if (effectTimer[num] < 4 && effectTimer[num] >= 0)
		{
			Effect::FireWorks(effectPos[num]);//花火爆発
		}

		effectTimer[num]--;

		break;
	}
	if (effectTimer[num] < 0)
	{
		effectMode[num] = 0;
		effectTimer[num] = -1;
	}
}