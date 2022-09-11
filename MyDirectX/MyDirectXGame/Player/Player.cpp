#include "Player.h"
#include "../input/Input.h"
#include "../Effect/Effect.h"
using namespace DirectX;

void Player::Initialize(MapChip* map)
{
	modelPlayer = Model::CreateFromObject("attacker1", false);

	objPlayer = Object3d::Create(modelPlayer);
	objPlayer->SetScale(XMFLOAT3({ 1, 1, 1 }));
	pos = XMFLOAT3({ 1 * 4.0f - (MapValue * 4.0f / 2) + 2, 2.0f, 3 * 4.0f - (MapValue * 4.0f / 2) + 2 });
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
	mapY = (pos.z / 4) + ((8 + 1) / 2);//�Ֆʂ̈ʒu
	mapX = (pos.x / 4) + ((8 + 1) / 2);//�Ֆʂ̈ʒu

	pos = { -8.0f,0.0f,-40.0f };//�v���C���[�̈ʒua
	angle = { 0,0,0 };

	moveSpeed = 4.0f;//�����̑��x

	bomNo = 0;

	for (int i = 0; i < 3; i++)
	{
		bomPos[i] = { 0.0f,0.0f,0.0f };//�v���C���[�̈ʒu
		bomAlive[i] = false;
		explosionCount[i] = 1;
		bomY[i] = 0;//�Ֆʂ̈ʒu
		bomX[i] = 0;//�Ֆʂ̈ʒu
		nowExplosion[i] = false;
	}

	putFlag = false;
	for (int i = 0; i < 3; i++)
	{
		turnFlag[i] = false;
	}
	playCount = 2400;


	objPlayer->SetScale(XMFLOAT3({ 1, 1, 1 }));
	pos = XMFLOAT3({ 1 * 4.0f - (MapValue * 4.0f / 2) + 2, 2.0f, 3 * 4.0f - (MapValue * 4.0f / 2) + 2 });
	objPlayer->SetPosition(pos);


	for (int i = 0; i < 3; i++)
	{
		objBom[i]->SetScale(XMFLOAT3({ 0.5, 0.5, 0.5 }));
		bomPos[i] = XMFLOAT3({ 4 * 4.0f - (MapValue * 4.0f / 2) + 2, 1.0f, 4 * 4.0f - (MapValue * 4.0f / 2) + 2 });
		objBom[i]->SetPosition(bomPos[i]);
	}

}

void Player::BomInitialize(int i)
{


	bomPos[i] = { 0.0f,0.0f,0.0f };//�v���C���[�̈ʒu
	bomAlive[i] = false;
	explosionCount[i] = 1;
	bomY[i] = 0;//�Ֆʂ̈ʒu
	bomX[i] = 0;//�Ֆʂ̈ʒu
	nowExplosion[i] = false;

	putFlag = false;

	turnFlag[i] = false;

	objBom[i]->SetScale(XMFLOAT3({ 0.5, 0.5, 0.5 }));
	bomPos[i] = XMFLOAT3({ 4 * 4.0f - (MapValue * 4.0f / 2) + 2, 1.0f, 4 * 4.0f - (MapValue * 4.0f / 2) + 2 });
	objBom[i]->SetPosition(bomPos[i]);

}

void Player::Update(MapChip* map)
{
	for (int i = 0; i < 3; i++)
	{
		if (bomAlive[i] == false)
		{
			BomInitialize(i);
		}
	}
	playCount--;
	Move(map);
	playerAngle();
	PutBom(map);
	objPlayer->Update();
	for (int i = 0; i < 3; i++)
	{
		BomEffect(i);
		objBom[i]->Update();
	}
	Explosion(map);
	Effect::Move(pos, { 1.0f,0.0f,0.2f,0.5f });
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
		pos.z += moveSpeed;// z���W���X�V
		angle.y = 180;
		for (int i = 0; i < 12; i++)
		{
			turnFlag[i] = true;
		}
		for (int i = 0; i < 3; i++)
		{
			if (bomAlive[i])
			{
				explosionCount[i]++;
			}
		}
		move = true;
	}
	if (Input::GetInstance()->KeybordTrigger(DIK_A) && mapX != 0 && map->GetWallFlag(mapX - 1, mapY) == 0)
	{
		pos.x -= moveSpeed;// x���W���X�V
		angle.y = 90;
		for (int i = 0; i < 12; i++)
		{
			turnFlag[i] = true;
		}
		for (int i = 0; i < 3; i++)
		{
			if (bomAlive[i])
			{
				explosionCount[i]++;
			}
		}
		move = true;
	}
	if (Input::GetInstance()->KeybordTrigger(DIK_S) && mapY != 0 && map->GetWallFlag(mapX, mapY - 1) == 0)
	{
		pos.z -= moveSpeed;// z���W���X�V
		angle.y = 0;
		for (int i = 0; i < 12; i++)
		{
			turnFlag[i] = true;
		}
		for (int i = 0; i < 3; i++)
		{
			if (bomAlive[i])
			{
				explosionCount[i]++;
			}
		}
		move = true;
	}
	if (Input::GetInstance()->KeybordTrigger(DIK_D) && mapX != 7 && map->GetWallFlag(mapX + 1, mapY) == 0)
	{
		pos.x += moveSpeed;// x���W���X�V
		angle.y = 270;
		for (int i = 0; i < 12; i++)
		{
			turnFlag[i] = true;
		}
		for (int i = 0; i < 3; i++)
		{
			if (bomAlive[i])
			{
				explosionCount[i]++;
			}
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
		if (angle.y == 180 && mapY != 7 && map->GetWallFlag(mapX, mapY + 1) == 0)
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
			bomY[bomNo] = (bomPos[bomNo].z / 4) + ((8 + 1) / 2);//�Ֆʂ̈ʒu
			bomX[bomNo] = (bomPos[bomNo].x / 4) + ((8 + 1) / 2);//�Ֆʂ̈ʒu
			map->SetWallFlag(bomX[bomNo], bomY[bomNo], 2);

		}
		else if (angle.y == 90 && mapX != 0 && map->GetWallFlag(mapX - 1, mapY) == 0)
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
			bomY[bomNo] = (bomPos[bomNo].z / 4) + ((8 + 1) / 2);//�Ֆʂ̈ʒu
			bomX[bomNo] = (bomPos[bomNo].x / 4) + ((8 + 1) / 2);//�Ֆʂ̈ʒu
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
			bomY[bomNo] = (bomPos[bomNo].z / 4) + ((8 + 1) / 2);//�Ֆʂ̈ʒu
			bomX[bomNo] = (bomPos[bomNo].x / 4) + ((8 + 1) / 2);//�Ֆʂ̈ʒu
			map->SetWallFlag(bomX[bomNo], bomY[bomNo], 2);
		}
		else if (angle.y == 270 && mapX != 7 && map->GetWallFlag(mapX + 1, mapY) == 0)
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
			bomY[bomNo] = (bomPos[bomNo].z / 4) + ((8 + 1) / 2);//�Ֆʂ̈ʒu
			bomX[bomNo] = (bomPos[bomNo].x / 4) + ((8 + 1) / 2);//�Ֆʂ̈ʒu
			map->SetWallFlag(bomX[bomNo], bomY[bomNo], 2);
		}
		if (putFlag == true)
		{
			if (bomNo != 2)
			{
				bomNo++;
				for (int i = 0; i < 12; i++)
				{
					turnFlag[i] = true;
				}
			}
			else if (bomNo == 2)
			{
				bomNo = 0;
				for (int i = 0; i < 12; i++)
				{
					turnFlag[i] = true;
				}
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
			nowExplosion[i] = true;
			//��
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

			//�E
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

			//��
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

			//��
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
			fire = true;
			bomAlive[i] = false;
			map->SetWallFlag(bomX[i], bomY[i], 0);
			explosionCount[i] = 1;
			effectTimer[i] = 10;//�G�t�F�N�g�p������
		}
		if (bomAlive[i])
		{
			Effect::Move(bomPos[i], { 1.0f,0.0f,0.2f,0.1f });
		}
		//�G�t�F�N�g����
		SetBomEffectMode(i, 1);
	}
}

void Player::enemyExplosion(int no, MapChip* map)
{
	int bomNo = no;
	bomAlive[bomNo] = false;
	fire = true;
	map->SetWallFlag(bomX[bomNo], bomY[bomNo], 0);
	explosionCount[bomNo] = 1;
	effectTimer[bomNo] = 10;//�G�t�F�N�g�p������
	//�G�t�F�N�g����
	SetBomEffectMode(bomNo, 2);
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
		//�����̒��S
		Effect::Explosion(effectPos[num]);

		//����
		if (effectTimer[num] <= 8)
		{
			Effect::Explosion({ effectPos[num].x - 1.2f, effectPos[num].y, effectPos[num].z });
			Effect::Explosion({ effectPos[num].x + 1.2f, effectPos[num].y, effectPos[num].z });
			Effect::Explosion({ effectPos[num].x, effectPos[num].y, effectPos[num].z - 1.2f });
			Effect::Explosion({ effectPos[num].x, effectPos[num].y, effectPos[num].z + 1.2f });

			Effect::Dust({ effectPos[num].x - 3, effectPos[num].y, effectPos[num].z });
			Effect::Dust({ effectPos[num].x + 3, effectPos[num].y, effectPos[num].z });
			Effect::Dust({ effectPos[num].x, effectPos[num].y, effectPos[num].z - 3 });
			Effect::Dust({ effectPos[num].x, effectPos[num].y, effectPos[num].z + 3 });
		}

		effectTimer[num]--;

		break;

	case 2:

		if (effectTimer[num] >= 4)
		{
			effectPos[num].y++;
			Effect::Move(effectPos[num], { 0.0f,10.0f,10.0f,1.0f });
		}
		if (effectTimer[num] < 4 && effectTimer[num] >= 0)
		{
			Effect::FireWorks(effectPos[num]);
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
