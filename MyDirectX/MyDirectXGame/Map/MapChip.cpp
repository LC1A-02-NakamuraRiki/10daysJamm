#include "MapChip.h"
#include "../collision/Collision.h"
#include<time.h>
#include<random>

void MapChip::Initialize()
{
	modelMapWall = Model::CreateFromObject("cube_blue", false);
	modelMapWall2 = Model::CreateFromObject("cube_red", false);
	modelMapWall3 = Model::CreateFromObject("cube_burned", false);
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			if (y == 0|| y == 1 || y == 2 || y == 9 || y == 10 || y == 11||
				x == 0 || x == 1 || x == 2 || x == 9 || x == 10 || x == 11)
			{
				objMapWall2[y][x] = Object3d::Create(modelMapWall);
			}
			else
			{
				objMapWall[y][x] = Object3d::Create(modelMapWall2);
			}
			objMapWall[y][x] = Object3d::Create(modelMapWall2);
			objMapWall[y][x]->SetScale(XMFLOAT3({ 2, 1, 2 }));
			objMapWall[y][x]->SetPosition(XMFLOAT3({ x * 4.0f - (MapValue * 4.0f / 2) + 2, 0.0f, y * 4.0f - (MapValue * 4.0f / 2) + 2 }));

			objMapWall2[y][x] = Object3d::Create(modelMapWall);
			objMapWall2[y][x]->SetScale(XMFLOAT3({ 2, 2, 2 }));
			objMapWall2[y][x]->SetPosition(XMFLOAT3({ x * 4.0f - (MapValue * 4.0f / 2) + 2, 2.0f, y * 4.0f - (MapValue * 4.0f / 2) + 2 }));

			objMapWall3[y][x] = Object3d::Create(modelMapWall3);
			objMapWall3[y][x]->SetScale(XMFLOAT3({ 2, 1, 2 }));
			objMapWall3[y][x]->SetPosition(XMFLOAT3({ x * 4.0f - (MapValue * 4.0f / 2) + 2, 0.0f, y * 4.0f - (MapValue * 4.0f / 2) + 2 }));
		}
	}
}

void MapChip::InitializeValue()
{
	MapValue = 12;
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
			if (y == 0 || y == 1 || y == 2 || y == 9 || y == 10 || y == 11 ||
				x == 0 || x == 1 || x == 2 || x == 9 || x == 10 || x == 11)
			{
				objMapWall[y][x] = Object3d::Create(modelMapWall);
			}
			else
			{
				objMapWall[y][x] = Object3d::Create(modelMapWall2);
			}
			objMapWall[y][x]->SetScale(XMFLOAT3({ 2, 1, 2 }));
			objMapWall[y][x]->SetPosition(XMFLOAT3({ x * 4.0f - (MapValue * 4.0f / 2) + 2, 0.0f, y * 4.0f - (MapValue * 4.0f / 2) + 2 }));

			objMapWall2[y][x] = Object3d::Create(modelMapWall);
			objMapWall2[y][x]->SetScale(XMFLOAT3({ 2, 2, 2 }));
			objMapWall2[y][x]->SetPosition(XMFLOAT3({ x * 4.0f - (MapValue * 4.0f / 2) + 2, 2.0f, y * 4.0f - (MapValue * 4.0f / 2) + 2 }));
			returnCount[y][x] = 0;
		}
	}
}


void MapChip::Update()
{

	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			if (returnCount[y][x] > 600)
			{
				mapWall[y][x] = 0;
				returnCount[y][x] = 0;
			}
			if (mapWall[y][x] == 0)
			{
				objMapWall[y][x]->SetScale(XMFLOAT3({ 2, 1, 2 }));
			}
			else if (mapWall[y][x] == 2)
			{
				returnCount[y][x]++;
				//objMapWall[y][x]->SetScale(XMFLOAT3({ 2, 2, 2 }));
			}
			objMapWall[y][x]->Update();
			objMapWall2[y][x]->Update();
			objMapWall3[y][x]->Update();
		}
	}
}

int MapChip::ArrayValue(float x, float y)
{
	int mapY = (y / 4) + ((MapValue + 1) / 2);
	int mapX = (x / 4) + ((MapValue + 1) / 2);

	return mapWall[mapY][mapX];
}

void MapChip::Draw()
{
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			if (mapWall[y][x] == 0)
			{
				objMapWall[y][x]->Draw();
			}
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
	for (int x = 0; x < MapValue; x++)
	{
		for (int y = 0; y < MapValue; y++)
		{
			if (mapWall[y][x] == 2)
			{
				objMapWall3[y][x]->Draw();
			}
		}
	}
}

void MapChip::DrawSprite()
{
}


