#pragma once
#include <DirectXMath.h>
#include "../Map/MapChip.h"
#include "../2d/Sprite.h"
#include "../3d/ParticleManager.h"
class Player
{
protected: // エイリアス
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:

	void Initialize(MapChip* map);//最初の初期化

	void InitializeValue();//タイトル時の初期化

	void Update(MapChip* map);//アップデート

	void Draw();

	void DrawSprite();

	void Move(MapChip* map);//歩き

	void playerAngle();

	void PutBom(MapChip* map);

	void Explosion(MapChip* map);

	void ExplosionEffect(XMFLOAT3 position);//爆発エフェクト

	XMFLOAT3 GetPos() { return pos; }

	void SetParticle(ParticleManager* particle) { this->particle = particle; }
private:

	const int MapValue = 8;//マップサイズ
	int mapY = (pos.z / 4) + ((8 + 1) / 2);//盤面の位置
	int mapX = (pos.x / 4) + ((8 + 1) / 2);//盤面の位置

	Model* modelPlayer = nullptr;
	Object3d* objPlayer;

	XMFLOAT3 pos = { -8.0f,0.0f,-40.0f };//プレイヤーの位置a
	XMFLOAT3 angle = { 0,0,0 };

	float moveSpeed = 4.0f;//歩きの速度

	int bomNo = 0;

	Model* modelBom = nullptr;
	Object3d* objBom[3];

	XMFLOAT3 bomPos[3] = { {0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };//プレイヤーの位置
	bool bomAlive[3] = {false, false, false};
	int explosionCount[3] = { 1,1,1 };
	bool putFlag = false;
	int bomY[3] = {0,0,0};//盤面の位置
	int bomX[3] = {0,0,0};//盤面の位置

	int effectTimer[3] = {10, 10, 10};
	ParticleManager* particle = nullptr;//爆発エフェクト用
};