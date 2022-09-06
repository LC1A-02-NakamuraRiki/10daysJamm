#pragma once
#include <DirectXMath.h>
#include "../3d/Object3d.h"
#include "../2d/Sprite.h"
#include"../helper/LoadCSV.h"

class MapChip
{
protected: // エイリアス
// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	void Initialize();//最初の初期化
	void InitializeValue();//タイトル時の初期化
	void Update();//アップデート
	int ArrayValue(float x, float y);//座標からマップチップ配列の算出
	void Draw();
	void DrawSprite();
	bool GetStopFlag() { return stopFlag; }
	int GetWallFlag(int NoX, int NoY) { return mapWall[NoY][NoX]; };
	int SetWallFlag(int NoX, int NoY,int info) { return mapWall[NoY][NoX] = info; }
private:

	Model* modelMapWall = nullptr;
	Object3d* objMapWall[8][8];
	Object3d* objMapWall2[8][8];


	int MapValue = 8;
	int MapValueX = 15;
	int MapValueZ = 15;

	int mapWall[8][8] = {
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,1,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,1,0,0 },
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0 }
	};
	int stopTime = 0;
	bool stopFlag = false;

};