#include "MapChip.h"
#include "../collision/Collision.h"
#include<time.h>
#include<random>

void MapChip::Initialize()
{
	modelMapWall = Model::CreateFromObject("jimen", false);
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			objMapWall[y][x] = Object3d::Create(modelMapWall);
			objMapWall[y][x]->SetScale(XMFLOAT3({ 2, 1, 2 }));
			objMapWall[y][x]->SetPosition(XMFLOAT3({ x * 4.0f - (MapValue * 4.0f / 2) + 2, 0.0f, y * 4.0f - (MapValue * 4.0f / 2) + 2 }));

			objMapWall2[y][x] = Object3d::Create(modelMapWall);
			objMapWall2[y][x]->SetScale(XMFLOAT3({ 2, 2, 2 }));
			objMapWall2[y][x]->SetPosition(XMFLOAT3({ x * 4.0f - (MapValue * 4.0f / 2) + 2, 2.0f, y * 4.0f - (MapValue * 4.0f / 2) + 2 }));
		}
	}
}

void MapChip::InitializeValue()
{
	MapValue = 8;
	MapValueX = 15;
	MapValueZ = 15;
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			mapWall[y][x] = mapWall2[y][x];
		}
	}
	stopTime = 0;
	stopFlag = false;
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			objMapWall[y][x] = Object3d::Create(modelMapWall);
			objMapWall[y][x]->SetScale(XMFLOAT3({ 2, 1, 2 }));
			objMapWall[y][x]->SetPosition(XMFLOAT3({ x * 4.0f - (MapValue * 4.0f / 2) + 2, 0.0f, y * 4.0f - (MapValue * 4.0f / 2) + 2 }));

			objMapWall2[y][x] = Object3d::Create(modelMapWall);
			objMapWall2[y][x]->SetScale(XMFLOAT3({ 2, 2, 2 }));
			objMapWall2[y][x]->SetPosition(XMFLOAT3({ x * 4.0f - (MapValue * 4.0f / 2) + 2, 2.0f, y * 4.0f - (MapValue * 4.0f / 2) + 2 }));
		}
	}
}


void MapChip::Update()
{
	
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			objMapWall[y][x]->Update();
			objMapWall2[y][x]->Update();
		}
	}
}

int MapChip::ArrayValue(float x, float y)
{
	int mapY = (y / 4) + ((MapValue+1) / 2);
	int mapX = (x / 4) + ((MapValue+1) / 2);
	
	return mapWall[mapY][mapX];
}

void MapChip::Draw()
{
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			objMapWall[y][x]->Draw();
		}
	}
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			if (mapWall[y][x] == 1)
			{
				objMapWall2[y][x]->Draw();
			}
		}
	}
}

void MapChip::DrawSprite()
{
}


