#include "../Scene/GameScene.h"
#include "../collision/Collision.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include "../3d/FbxLoader.h"
#include "../3d/FbxObject3d.h"
#include "../input/Input.h"
#include "../Effect/Effect.h"

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(spriteText1);
	safe_delete(spriteText2);
	safe_delete(spriteTitle);
	safe_delete(spriteTitle1);
	safe_delete(spriteTitle2);
	safe_delete(spriteClear);
	safe_delete(spriteGAMEOVER);
	safe_delete(spriteBom);
	safe_delete(spriteBom2);
	safe_delete(particle3d);
	safe_delete(objSkydome);
	safe_delete(modelSkydome);
	safe_delete(objGround);
	safe_delete(modelGround);
	safe_delete(light);
	safe_delete(map);
	safe_delete(player);
	safe_delete(enemy);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Sound* audio)
{
	// nullptrチェック
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;

	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);

	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	particle3d = ParticleManager::Create(dxCommon->GetDevice(), camera);

	//スプライト
	// テクスチャ読み込み
	if (!Sprite::LoadTexture(18, L"Resources/Title.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(19, L"Resources/Clear.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(20, L"Resources/GAMEOVER.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(21, L"Resources/tmp_01.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(22, L"Resources/title_01.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(23, L"Resources/title_02.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(24, L"Resources/title_back.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(25, L"Resources/text_01.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(26, L"Resources/text_02.png")) {
		assert(0);
		return;
	}
	//// 背景スプライト生成
	spriteBom = Sprite::Create(21, { 0.0f,0.0f });
	spriteBom2 = Sprite::Create(21, { 0.0f,0.0f });
	spriteTitle = Sprite::Create(24, { 0.0f,0.0f });
	spriteTitle1 = Sprite::Create(23, { 0,0 });
	spriteTitle1->SetSize({ 987.0f,428.0f });
	spriteTitle1->SetPosition({ 466.5, 110 });
	spriteTitle2 = Sprite::Create(22, { 0.0f,0.0f });
	spriteTitle2->SetSize({ 861.0f,212.0f });
	spriteTitle2->SetPosition({ 539.5, 210 });
	spriteText1 = Sprite::Create(25, { 0.0f,0.0f });
	spriteText1->SetSize({ 742.0f,82.0f });
	spriteText1->SetPosition({ 589.0, 810 });
	spriteText2 = Sprite::Create(26, { 0.0f,0.0f });
	spriteText2->SetSize({ 742.0f,82.0f });
	spriteText2->SetPosition({ 589.0, 810 });
	spriteClear = Sprite::Create(19, { 0.0f,0.0f });
	spriteGAMEOVER = Sprite::Create(20, { 0.0f,0.0f });

	// 3Dオブジェクト生成
	modelSkydome = Model::CreateFromObject("skydome", false);
	objSkydome = Object3d::Create(modelSkydome);
	objSkydome->SetScale({ 5.0f,5.0f,5.0f });
	modelGround = Model::CreateFromObject("ground", true);
	objGround = Object3d::Create(modelGround);
	objGround->SetScale({ 5.0f,2.0f ,5.0f });

	// デバイスをセット
	FbxObject3d::SetDevice(dxCommon->GetDevice());
	// カメラをセット
	FbxObject3d::SetCamera(camera);
	// グラフィックスパイプライン生成
	FbxObject3d::CreateGraphicsPipeline();
	light = LightGroop::Create();

	Object3d::SetLightGroup(light);

	map = new MapChip;
	map->Initialize();
	player = new Player;
	player->Initialize(map);
	Effect::SetParticleManager(particle3d);
	enemy = new Enemy;
	enemy->Initialize(7, 0, 1, 0);
	enemy->Initialize(7, 1, 1, 1);
	enemy->Initialize(7, 2, 1, 2);
	enemy->Initialize(7, 3, 1, 3);
	enemy->Initialize(7, 4, 1, 4);
	enemy->Initialize(7, 5, 1, 5);
	enemy->Initialize(7, 6, 1, 6);
	enemy->Initialize(7, 7, 1, 7);
	enemy->Initialize(0, 0, 0, 8);
	enemy->Initialize(1, 0, 0, 9);
	enemy->Initialize(2, 0, 0, 10);
	enemy->Initialize(3, 0, 0, 11);
	audio->PlayBGM("Resources/BGM/title_bgm.wav",true);
}

void GameScene::Update()
{
	debugText.Print(20, 20, 2.0f, "END : ESC");
	if (scene == TITLE)
	{
		textCount++;
		if (textCount <= 50)
		{
			text1Draw = true;
		}
		else if (textCount > 50)
		{
			text1Draw = false;
		}

		if (textCount > 100)
		{
			textCount = 0;
		}

		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE))
		{
			audio->PlaySE("Resources/SE/title_dicided.wav", false);
			map->InitializeValue();
			player->InitializeValue();
			enemy->EndInitialize();
			bomSceneChange = true;
		}

		
		if (bomSceneChange == true)
		{
			sceneChangeCount++;
			for (int i = 0; i < 12; i++)
			{
				size.x += size.x / 100;
				size.y += size.y / 100;
				pos.x -= (size.x / 100) / 2;
				pos.y -= (size.y / 100) / 2;
			}

			spriteBom->SetPosition(pos);
			spriteBom->SetSize(size);
			
			if (sceneChangeCount > 60)
			{
				audio->StopBGM();
				audio->PlayBGM("Resources/BGM/game_bgm.wav", true);
				scene = PLAY;
			}
		}
	}
	else if (scene == PLAY)
	{
	
		if (bomSceneChange2 == true)
		{
			bomSceneChange = false;
			sceneChangeCount2++;
			for (int i = 0; i < 12; i++)
			{
				size2.x -= size2.x / 100;
				size2.y -= size2.y / 100;
				pos2.x += (size2.x / 100) / 2;
				pos2.y += (size2.y / 100) / 2;
			}
				
				spriteBom2->SetPosition(pos2);
				spriteBom2->SetSize(size2);

			if (sceneChangeCount2 > 60)
			{
				bomSceneChange = false;
			}
		}

		if (player->GetFire())
		{
			audio->PlaySE("Resources/SE/game_fire.wav", false);
			player->SetFire();
		}
		if (player->GetMove())
		{
			audio->PlaySE("Resources/SE/game_move.wav", false);
			player->SetMove();
		}
		
		if (player->GetPlayCount() / 60 < 0)
		{
			audio->StopBGM();
			audio->PlayBGM("Resources/BGM/result_bgm.wav", true);
			scene = CLEAR;
		}
		int mapY = (player->GetPos().z / 4) + ((8 + 1) / 2);
		int mapX = (player->GetPos().x / 4) + ((8 + 1) / 2);

		debugText.Print(20, 70, 2.0f, "score :  %d", enemy->GetScore());
		debugText.Print(20, 100, 2.0f, "faze :  %d", enemy->GetWave());
		debugText.Print(20, 130, 2.0f, "time :  %d", player->GetPlayCount() / 60);

		/*debugText.Print(20, 50, 2.0f, "MOVE : W A S D");
		debugText.Print(20, 80, 2.0f, "VIEW : MOUSE or ArrowKey ");
		debugText.Print(20, 110, 2.0f, "SENSI CHANGE -/+  :  9/0 ");
		debugText.Print(20, 140, 2.0f, "NowSENSI :  %f", player->GetViewSpeed());*/

		//ライト
		light->SetAmbientColor(XMFLOAT3(ambientColor0));

		light->SetDirLightDir(0, XMVECTOR({ lightDir0[0], lightDir0[1], lightDir0[2], 0 }));
		light->SetDirLightColor(0, XMFLOAT3(lightColor0));

		light->SetDirLightDir(1, XMVECTOR({ lightDir1[0], lightDir1[1], lightDir1[2], 0 }));
		light->SetDirLightColor(1, XMFLOAT3(lightColor1));

		light->SetDirLightDir(2, XMVECTOR({ lightDir2[0], lightDir2[1], lightDir2[2], 0 }));
		light->SetDirLightColor(2, XMFLOAT3(lightColor2));

		light->SetDirLightDir(3, XMVECTOR({ lightDir3[0], lightDir3[1], lightDir3[2], 0 }));
		light->SetDirLightColor(3, XMFLOAT3(lightColor3));

		light->SetDirLightDir(4, XMVECTOR({ lightDir4[0], lightDir4[1], lightDir4[2], 0 }));
		light->SetDirLightColor(4, XMFLOAT3(lightColor4));

		light->SetDirLightDir(5, XMVECTOR({ lightDir5[0], lightDir5[1], lightDir5[2], 0 }));
		light->SetDirLightColor(5, XMFLOAT3(lightColor5));
		map->Update();
		enemy->Update(player, map);
		player->Update(map);
		particle3d->Update();
		camera->Update();
		objSkydome->Update();
		objGround->Update();
		light->Update();
		stopFlag = map->GetStopFlag();
	}
	else if (scene == CLEAR)
	{
		debugText.Print(20, 70, 2.0f, "score :  %d", enemy->GetScore());
		debugText.Print(20, 100, 2.0f, "faze :  %d", enemy->GetWave());
		debugText.Print(200, 700, 4.0f, "PlayScene[B]");
		if (Input::GetInstance()->KeybordTrigger(DIK_B))
		{
			audio->PlaySE("Resources/SE/title_dicided.wav", false);
			pos = { 954.03,532.74 };
			size = { 8.47,10.3 };

			pos2 = { -800,-1625 };
			size2 = { 3560,4330 };
			bomSceneChange = false;
			sceneChangeCount = 0;
			bomSceneChange2 = true;
			sceneChangeCount2 = 0;
			spriteBom->SetPosition(pos);
			spriteBom->SetSize(size);
			spriteBom2->SetPosition(pos2);
			spriteBom2->SetSize(size2);

			map->InitializeValue();
			player->InitializeValue();
			enemy->EndInitialize();
			audio->StopBGM();
			audio->PlayBGM("Resources/BGM/title_bgm.wav", true);
			scene = PLAY;
		}
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE))
		{
			scene = TITLE;
			audio->PlaySE("Resources/SE/title_dicided.wav", false);
			pos = { 954.03,532.74 };
			size = { 8.47,10.3 };

			pos2 = { -800,-1625 };
			size2 = { 3560,4330 };
			bomSceneChange = false;
			sceneChangeCount = 0;
			bomSceneChange2 = true;
			sceneChangeCount2 = 0;
			spriteBom->SetPosition(pos);
			spriteBom->SetSize(size);
			spriteBom2->SetPosition(pos2);
			spriteBom2->SetSize(size2);

			map->InitializeValue();
			player->InitializeValue();
			enemy->EndInitialize();
			audio->StopBGM();
			audio->PlayBGM("Resources/BGM/title_bgm.wav", true);
		}
	}
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	//-------------------------------------------------------------//

	//-------------------------------------------------------------//
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);
	//-------------------------------------------------------------//
	if (scene == PLAY)
	{
		objSkydome->Draw();
		objGround->Draw();
		map->Draw();
		player->Draw();
		enemy->Draw();
	}
	//-------------------------------------------------------------//
	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();

	particle3d->Draw(cmdList);
#pragma endregion


#pragma region 前景スプライト描画
	//// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	//-------------------------------------------------------------//

	if (scene == TITLE)
	{

		spriteTitle->Draw();
		spriteTitle1->Draw();
		spriteTitle2->Draw();
		if (text1Draw == true)
		{
			spriteText1->Draw();
		}
		if (text1Draw == false)
		{
			spriteText2->Draw();
		}
		if (bomSceneChange == true)
		{
			spriteBom->Draw();
		}
	}
	if (scene == PLAY)
	{
		if (bomSceneChange2 == true)
		{
			spriteBom2->Draw();
		}
	}
	if (scene == CLEAR)
	{
		spriteClear->Draw();
	}
	if (scene == GAMEOVER)
	{
		spriteGAMEOVER->Draw();
	}

	//-------------------------------------------------------------//
	// デバッグテキストの描画
	debugText.DrawAll(cmdList);
	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}

void GameScene::ParticlesCreate(XMFLOAT3 Pos)
{
	for (int i = 0; i < 1; i++)
	{
		//X,Y,Z全て{-5.0f,+5.0f}でランダムに分布
		const float md_pos = 0.5f;
		XMFLOAT3 pos = Pos;
		pos.x += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.y += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.z += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		////X,Y,Z全て{-0.05f,+0.05f}でランダムに分布
		const float md_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		//重力に見立ててYのみ{-0.001f,0}でランダム分布
		XMFLOAT3 acc{};
		const float md_acc = 0.001f;
		acc.y = (float)rand() / RAND_MAX * md_acc;

		int time = 60;
		float s_scale = 1.0f;
		float e_scale = 1.0f;
		XMFLOAT4 color = { 1,1,1,1 };
		// 追加
		particle3d->Add(time, pos, vel, acc, s_scale, e_scale, color);
	}
}
