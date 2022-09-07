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

	void Update(MapChip* map);//�A�b�v�f�[�g

	void Draw();

	void DrawSprite();

	void Move(MapChip* map);//����

	void playerAngle();

	void PutBom(MapChip* map);

	void Explosion(MapChip* map);

	void ExplosionEffect(XMFLOAT3 position);//�����G�t�F�N�g

	XMFLOAT3 GetPos() { return pos; }

	void SetParticle(ParticleManager* particle) { this->particle = particle; }
private:

	const int MapValue = 8;//�}�b�v�T�C�Y
	int mapY = (pos.z / 4) + ((8 + 1) / 2);//�Ֆʂ̈ʒu
	int mapX = (pos.x / 4) + ((8 + 1) / 2);//�Ֆʂ̈ʒu

	Model* modelPlayer = nullptr;
	Object3d* objPlayer;

	XMFLOAT3 pos = { -8.0f,0.0f,-40.0f };//�v���C���[�̈ʒua
	XMFLOAT3 angle = { 0,0,0 };

	float moveSpeed = 4.0f;//�����̑��x

	int bomNo = 0;

	Model* modelBom = nullptr;
	Object3d* objBom[3];

	XMFLOAT3 bomPos[3] = { {0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };//�v���C���[�̈ʒu
	bool bomAlive[3] = {false, false, false};
	int explosionCount[3] = { 1,1,1 };
	bool putFlag = false;
	int bomY[3] = {0,0,0};//�Ֆʂ̈ʒu
	int bomX[3] = {0,0,0};//�Ֆʂ̈ʒu

	int effectTimer[3] = {10, 10, 10};
	ParticleManager* particle = nullptr;//�����G�t�F�N�g�p
};