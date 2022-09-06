#pragma once
#include <DirectXMath.h>
#include "../3d/Object3d.h"
#include "../2d/Sprite.h"
#include"../helper/LoadCSV.h"

class MapChip
{
protected: // �G�C���A�X
// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	void Initialize();//�ŏ��̏�����
	void InitializeValue();//�^�C�g�����̏�����
	void Update();//�A�b�v�f�[�g
	int ArrayValue(float x, float y);//���W����}�b�v�`�b�v�z��̎Z�o
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