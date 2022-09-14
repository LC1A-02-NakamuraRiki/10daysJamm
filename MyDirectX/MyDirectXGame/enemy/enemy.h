#pragma once
#include <DirectXMath.h>
#include "../Map/MapChip.h"
#include "../3d/Object3d.h"
#include "../Player/Player.h"
#include "../2d/Sprite.h"

class Enemy
{
	enum MoveVector
	{
		VERTICAL,
		HORIZONTAL
	};
protected: // �G�C���A�X
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void Initialize(int x, int y, int moveVector, int enemysNo);//�ŏ��̏�����

	void EndInitialize();

	void enemyCreate();

	void InitializeValue(int x, int y, int moveVector, int enemysNo,int laneNo);//�^�C�g�����̏�����

	void Update(Player* player, MapChip* mapChip, bool start);//�A�b�v�f�[�g

	void Draw();

	void DrawSprite(MapChip* mapChip);

	void Move(Player* player, MapChip* mapChip);//����

	void Explosion(Player* player, MapChip* mapChip);

	void EnemyExplosion(Player* player, MapChip* mapChip);

	void EnemyFire(MapChip* mapChip);

	XMFLOAT3 GetPos(int no) { return pos[no]; }
	int GetScore() { return score; }
	int GetWave() { return wave; }

	bool GetScorePluse() { return scorePluse; }
	bool SetScorePluse() { return scorePluse = false; }

private:
	const int MapValue = 12;//�}�b�v�T�C�Y
	const int enemyMaxNo = 12;
	Model* modelEnemy = nullptr;
	Object3d* objEnemy[12];
	XMFLOAT3 pos[12] = { { 0.0f,0.0f,0.0f },{ 0.0f,0.0f,0.0f },{ 0.0f,0.0f,0.0f },{ 0.0f,0.0f,0.0f },
	{ 0.0f,0.0f,0.0f },{ 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f },{ 0.0f,0.0f,0.0f },
	{ 0.0f,0.0f,0.0f },{ 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f },{ 0.0f,0.0f,0.0f }, };//�v���C���[�̈ʒu
	XMFLOAT3 angle[12] = { { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f } ,{ 0.0f,0.0f,0.0f },{ 0.0f,0.0f,0.0f },
	{ 0.0f,0.0f,0.0f },{ 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f },{ 0.0f,0.0f,0.0f },
	{ 0.0f,0.0f,0.0f },{ 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f },{ 0.0f,0.0f,0.0f }, };
	int enemyType[12] = { HORIZONTAL,HORIZONTAL,HORIZONTAL,HORIZONTAL,HORIZONTAL,HORIZONTAL,HORIZONTAL,HORIZONTAL,HORIZONTAL,HORIZONTAL
	,HORIZONTAL ,HORIZONTAL };
	int enemyY[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };//�Ֆʂ̈ʒu
	int enemyX[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };//�Ֆʂ̈ʒu

	bool enemyDead[12] = { true ,true,true,true,true,true
	,true ,true ,true ,true ,true ,true };

	int returnCount[12] = { 3,3,3,3,3,3,3,3,3,3,3,3 };
	int enemyLv[12] = { 1 ,1,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 };

	int score = 0;

	int spawnNum = 2;

	int wave = 1;
	int killCount = 0;

	int moveCount = 0;

	int lane[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	
	bool scorePluse = false;

	int effectTimer[12]{};
	XMFLOAT3 effectPos[12]{};
};

