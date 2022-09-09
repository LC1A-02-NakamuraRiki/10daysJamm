#pragma once

#include "../base/SafeDelete.h"
#include "../base/DirectXCommon.h"
#include <DirectXMath.h>
#include "../input/Input.h"
#include "../2d/Sprite.h"
#include "../3d/Object3d.h"
#include "../3d/FbxObject3d.h"
#include "../2d/DebugText.h"
#include "../Sound/Sound.h"
#include "../collision/Collision.h"
#include "../3d/ParticleManager.h"
#include "../3d/DebugCamera.h"
#include "../3d/DebugCamera.h"
#include "../Map/MapChip.h"
#include "../3d/LightGroop.h"
#include "../Player/Player.h"
#include "../enemy/enemy.h"
/// <summary>
/// ゲームシーン
/// </summary>
enum Mode
{
	TITLE,
	PLAY,
	CLEAR,
	GAMEOVER,
};

class GameScene
{
protected: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	LightGroop *light = nullptr;
private: // 静的メンバ変数
	static const int debugTextTexNumber = 0;

public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon *dxCommon, Sound *audio);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// パーティクル生成
	/// </summary>
	void ParticlesCreate(XMFLOAT3 Pos);

	bool GetStopFlag() { return stopFlag; }
private: // メンバ変数
	DirectXCommon *dxCommon = nullptr;
	Sound *audio = nullptr;
	DebugText debugText;
	
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	DebugCamera *camera = nullptr;
	Sprite *spriteTitle = nullptr;
	Sprite* spriteTitle1 = nullptr;
	Sprite* spriteTitle2 = nullptr;
	Sprite* spriteText1 = nullptr;
	Sprite* spriteText2 = nullptr;
	Sprite* spriteClear = nullptr;
	Sprite* spriteGAMEOVER = nullptr;
	Sprite* spriteBom = nullptr;
	Sprite* spriteBom2 = nullptr;
	Model *modelSkydome = nullptr;
	Object3d *objSkydome = nullptr;

	Model *modelGround = nullptr;
	Object3d *objGround = nullptr;

	ParticleManager *particle3d = nullptr;
	MapChip* map = nullptr;
	Player* player = nullptr;
	Enemy* enemy = nullptr;
	bool stopFlag;

	float ambientColor0[3] = { 0.6,0.6,0.6 };
	// 光線方向初期値

	float lightDir0[3] = { 0,1,0 };
	float lightDir1[3] = { 0,0,1 };
	float lightDir2[3] = { 0,0,-1 };
	float lightDir3[3] = { 1,0,0 };
	float lightDir4[3] = {-1,0,0 };
	float lightDir5[3] = { 0,-1,0 };
	
	float lightColor0[3] = { 1.75,1.75,1.4 };
	float lightColor1[3] = { 1.2,1.2,0.96 };
	float lightColor2[3] = { 1.2,1.2,0.96 };
	float lightColor3[3] = { 1.2,1.2,0.96 };
	float lightColor4[3] = { 1.2,1.2,0.96 };
	float lightColor5[3] = { 1.5,1.5,1.2 };

	int scene = 0;
	XMFLOAT2 pos = { 954.03,532.74 };
	XMFLOAT2 size = {8.47,10.3};

	XMFLOAT2 pos2 = { -800,-1625 };
	XMFLOAT2 size2 = { 3560,4330 };

	bool text1Draw = false;
	int  textCount = 0;

	bool bomSceneChange = false;
	int sceneChangeCount = 0;
	bool bomSceneChange2 = true;
	int sceneChangeCount2 = 0;
};