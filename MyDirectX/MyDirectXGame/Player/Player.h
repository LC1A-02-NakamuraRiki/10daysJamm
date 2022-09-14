#pragma once
#include <DirectXMath.h>
#include "../Map/MapChip.h"
#include "../2d/Sprite.h"
#include "../3d/ParticleManager.h"
class Player
{
protected: // �G�C���A�X
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:

	void Initialize(MapChip* map);//�ŏ��̏�����

	void InitializeValue();//�^�C�g�����̏�����
	void BomInitialize(int i);//�^�C�g�����̏�����

	void Update(MapChip* map, bool countStart, bool start);//�A�b�v�f�[�g

	void Draw();

	void DrawSprite();

	void Move(MapChip* map);//����

	void playerAngle();

	void PutBom(MapChip* map);

	void Explosion(MapChip* map);


	XMFLOAT3 GetPos() { return pos; }
	XMFLOAT3 GetBomPos(int no) { return bomPos[no]; };
	XMFLOAT3 SetBomPos(int no) { return bomPos[no] = XMFLOAT3({ 100,100,100 }); };
	int GetPlayCount() { return playCount; }
	int SetPlayCount() { return playCount += 60; }
	bool GetBomAlive(int No) { return bomAlive[No]; }
	bool SetBomAlive(int No) { return bomAlive[No] = false; }
	bool GetTurnFlag(int no) { return turnFlag[no]; }
	bool SetTurnFlag(bool turn, int no) { return turnFlag[no] = turn; }
	bool GetExplosion(int No) { return nowExplosion[No]; }
	bool SetExplosionF(int No) { return nowExplosion[No] = false; }
	bool SetExplosionT(int No) { return nowExplosion[No] = true; }
	bool GetFire() { return fire; }
	bool SetFire() { return fire = false; }
	bool GetMove() { return move; }
	bool SetMove() { return move = false; }
	int GetPlayCount(int no) { return explosionCount[no]; }
	int SetPlayCount(int no, int turn) { return explosionCount[no] = turn; }
	int GetLv(int no) { return bomLv[no]; }
	int SetEffectTimer(int no) { return effectTimer[no] = 10; }
	bool SetWallFlag(int No) { return wallFlag[No] = false; }
	void SetBomEffectMode(int num, int mode);
	void BomEffect(int num,MapChip* map);
private:

	const int MapValue = 12;//�}�b�v�T�C�Y
	int mapY = (pos.z / 4) + ((12 + 1) / 2);//�Ֆʂ̈ʒu
	int mapX = (pos.x / 4) + ((12 + 1) / 2);//�Ֆʂ̈ʒu

	Model* modelPlayer = nullptr;
	Object3d* objPlayer;

	XMFLOAT3 pos = { 4.0f,0.0f,-40.0f };//�v���C���[�̈ʒua
	XMFLOAT3 angle = { 0,0,0 };

	float moveSpeed = 4.0f;//�����̑��x

	bool move = false;

	int bomNo = 0;

	Model* modelBom[8] = { false, false,false ,false , false , false , false , false  };
	Object3d* objBom[8][20];

	XMFLOAT3 bomPos[20] = { {0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };//�v���C���[�̈ʒu
	int bomAngle[20] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	bool bomAlive[20] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
	int explosionCount[20] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	bool putFlag = false;
	int bomY[20] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };//�Ֆʂ̈ʒu
	int bomX[20] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };//�Ֆʂ̈ʒu
	int bomLv[20] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int lvCount[20] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	bool turnFlag[12] = { false, false,false ,false , false , false , false , false , false , false , false , false };
	bool nowExplosion[20] = { false, false, false,false,false, false, false,false,false, false, false,false,false, false, false,false,false, false, false,false };
	int playCount = 2400;

	bool fire = false;

	XMFLOAT3 effectPos[20]{};//�����G�t�F�N�g�p
	int effectTimer[20] = { 0, 0, 0 ,0,0, 0, 0 ,0, 0, 0, 0 ,0, 0, 0, 0 ,0, 0, 0, 0 ,0};
	bool effectFlag[20] = { false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false };

	bool wallFlag[20] = { false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false };

	int effectMode[20]{};

	bool delayFlag = false;
	int delayCount = 0;
};