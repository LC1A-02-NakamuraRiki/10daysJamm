#include "../Scene/GameScene.h"
#include "../collision/Collision.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include "../3d/FbxLoader.h"
#include "../3d/FbxObject3d.h"
#include "../input/Input.h"
#include "../Effect/Effect.h"
#include<time.h>
#include<random>

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(spriteText1);
	safe_delete(spriteText2);
	safe_delete(spriteTitleScroll1);
	safe_delete(spriteTitleScroll2);
	safe_delete(spriteTitleScroll3);
	safe_delete(spriteTitleScroll4);
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
	for (int i = 0; i < 9; i++)
	{
		safe_delete(spriteNumber0[i]);
		safe_delete(spriteNumber1[i]);
		safe_delete(spriteNumber2[i]);
		safe_delete(spriteNumber3[i]);
		safe_delete(spriteNumber4[i]);
		safe_delete(spriteNumber5[i]);
		safe_delete(spriteNumber6[i]);
		safe_delete(spriteNumber7[i]);
		safe_delete(spriteNumber8[i]);
		safe_delete(spriteNumber9[i]);
	}
	
	safe_delete(spriteClearScore);
	safe_delete(spriteClearTextL1);
	safe_delete(spriteClearTextL2);
	safe_delete(spriteClearTextR1);
	safe_delete(spriteClearTextR2);
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

	if (!Sprite::LoadTexture(27, L"Resources//number2/0.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(28, L"Resources/number2/1.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(29, L"Resources/number2/2.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(30, L"Resources/number2/3.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(31, L"Resources/number2/4.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(32, L"Resources/number2/5.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(33, L"Resources/number2/6.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(34, L"Resources/number2/7.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(35, L"Resources/number2/8.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(36, L"Resources/number2/9.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(37, L"Resources/result_01.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(38, L"Resources/result_03.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(39, L"Resources/result_05.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(40, L"Resources/result_02.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(41, L"Resources/result_04.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(42, L"Resources/Back1.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(43, L"Resources/game_01.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(44, L"Resources/game_02.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(45, L"Resources/rogo.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(46, L"Resources/black1x1.png")) {
		assert(0);
		return;
	}
	//// 背景スプライト生成
	spriteBom = Sprite::Create(21, { 0.0f,0.0f });
	spriteBom2 = Sprite::Create(21, { 0.0f,0.0f });
	spriteTitleScroll1 = Sprite::Create(24, { 0.0f,0.0f });
	spriteTitleScroll2 = Sprite::Create(24, { 0.0f,0.0f });
	spriteTitleScroll3 = Sprite::Create(24, { 0.0f,0.0f });
	spriteTitleScroll4 = Sprite::Create(24, { 0.0f,0.0f });
	spriteTitleScroll1->SetSize(titleSize);
	spriteTitleScroll2->SetSize(titleSize);
	spriteTitleScroll3->SetSize(titleSize);
	spriteTitleScroll4->SetSize(titleSize);

	spriteTitleScroll1->SetPosition(titlePos1);
	spriteTitleScroll2->SetPosition(titlePos2);
	spriteTitleScroll3->SetPosition(titlePos3);
	spriteTitleScroll4->SetPosition(titlePos4);

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

	spriteNumber0[0] = Sprite::Create(27, { 0.0f,0.0f });
	spriteNumber0[0]->SetSize({ 742.0f,82.0f });
	spriteNumber0[0]->SetPosition({ 589.0, 810 });

	spriteNumber1[0] = Sprite::Create(28, { 0.0f,0.0f });
	spriteNumber1[0]->SetSize({ 120.0f,120.0f });
	spriteNumber1[0]->SetPosition({ 916.0, 506 });

	spriteNumber2[0] = Sprite::Create(29, { 0.0f,0.0f });
	spriteNumber2[0]->SetSize({ 120.0f,120.0f });
	spriteNumber2[0]->SetPosition({ 916.0, 506 });

	spriteNumber3[0] = Sprite::Create(30, { 0.0f,0.0f });
	spriteNumber3[0]->SetSize({ 120.0f,120.0f });
	spriteNumber3[0]->SetPosition({ 916.0, 506 });

	spriteNumber4[0] = Sprite::Create(31, { 0.0f,0.0f });
	spriteNumber4[0]->SetSize({ 120.0f,120.0f });
	spriteNumber4[0]->SetPosition({ 916.0, 506 });

	spriteNumber5[0] = Sprite::Create(32, { 0.0f,0.0f });
	spriteNumber5[0]->SetSize({ 120.0f,120.0f });
	spriteNumber5[0]->SetPosition({ 916.0, 506 });

	spriteNumber6[0] = Sprite::Create(33, { 0.0f,0.0f });
	spriteNumber6[0]->SetSize({ 120.0f,120.0f });
	spriteNumber6[0]->SetPosition({ 916.0, 506 });

	spriteNumber7[0] = Sprite::Create(34, { 0.0f,0.0f });
	spriteNumber7[0]->SetSize({ 120.0f,120.0f });
	spriteNumber7[0]->SetPosition({ 916.0, 506 });

	spriteNumber8[0] = Sprite::Create(35, { 0.0f,0.0f });
	spriteNumber8[0]->SetSize({ 120.0f,120.0f });
	spriteNumber8[0]->SetPosition({ 916.0, 506 });

	spriteNumber9[0] = Sprite::Create(36, { 0.0f,0.0f });
	spriteNumber9[0]->SetSize({ 120.0f,120.0f });
	spriteNumber9[0]->SetPosition({ 916.0, 506 });

	spriteNumber0s = Sprite::Create(27, { 0.0f,0.0f });
	spriteNumber0s->SetSize({ 60.0f,120.0f });
	spriteNumber0s->SetPosition({ 1660.0, 200 });
	spriteNumber0[0] = Sprite::Create(27, { 0.0f,0.0f });
	spriteNumber0[0]->SetSize({ 60.0f,120.0f });
	spriteNumber0[0]->SetPosition({ 1600.0, 200 });
	spriteNumber0[1] = Sprite::Create(27, { 0.0f,0.0f });
	spriteNumber0[1]->SetSize({ 60.0f,120.0f });
	spriteNumber0[1]->SetPosition({ 1540.0, 200 });


	spriteNumber0[2] = Sprite::Create(27, { 0.0f,0.0f });
	spriteNumber0[2]->SetSize({ 120.0f,120.0f });
	spriteNumber0[2]->SetPosition({ 1480.0, 200 });
	spriteNumber1[2] = Sprite::Create(28, { 0.0f,0.0f });
	spriteNumber1[2]->SetSize({ 120.0f,120.0f });
	spriteNumber1[2]->SetPosition({ 1480.0, 200 });
	spriteNumber2[2] = Sprite::Create(29, { 0.0f,0.0f });
	spriteNumber2[2]->SetSize({ 120.0f,120.0f });
	spriteNumber2[2]->SetPosition({ 1480.0, 200 });
	spriteNumber3[2] = Sprite::Create(30, { 0.0f,0.0f });
	spriteNumber3[2]->SetSize({ 120.0f,120.0f });
	spriteNumber3[2]->SetPosition({ 1480.0, 200 });
	spriteNumber4[2] = Sprite::Create(31, { 0.0f,0.0f });
	spriteNumber4[2]->SetSize({ 120.0f,120.0f });
	spriteNumber4[2]->SetPosition({ 1480.0, 200 });
	spriteNumber5[2] = Sprite::Create(32, { 0.0f,0.0f });
	spriteNumber5[2]->SetSize({ 120.0f,120.0f });
	spriteNumber5[2]->SetPosition({ 1480.0, 200 });
	spriteNumber6[2] = Sprite::Create(33, { 0.0f,0.0f });
	spriteNumber6[2]->SetSize({ 120.0f,120.0f });
	spriteNumber6[2]->SetPosition({ 1480.0, 200 });
	spriteNumber7[2] = Sprite::Create(34, { 0.0f,0.0f });
	spriteNumber7[2]->SetSize({ 120.0f,120.0f });
	spriteNumber7[2]->SetPosition({ 1480.0, 200 });
	spriteNumber8[2] = Sprite::Create(35, { 0.0f,0.0f });
	spriteNumber8[2]->SetSize({ 120.0f,120.0f });
	spriteNumber8[2]->SetPosition({ 1480.0, 200 });
	spriteNumber9[2] = Sprite::Create(36, { 0.0f,0.0f });
	spriteNumber9[2]->SetSize({ 120.0f,120.0f });
	spriteNumber9[2]->SetPosition({ 1480.0, 200 });

	spriteNumber0[3] = Sprite::Create(27, { 0.0f,0.0f });
	spriteNumber0[3]->SetSize({ 120.0f,120.0f });
	spriteNumber0[3]->SetPosition({ 1420.0, 200 });
	spriteNumber1[3] = Sprite::Create(28, { 0.0f,0.0f });
	spriteNumber1[3]->SetSize({ 120.0f,120.0f });
	spriteNumber1[3]->SetPosition({ 1420.0, 200 });
	spriteNumber2[3] = Sprite::Create(29, { 0.0f,0.0f });
	spriteNumber2[3]->SetSize({ 120.0f,120.0f });
	spriteNumber2[3]->SetPosition({ 1420.0, 200 });
	spriteNumber3[3] = Sprite::Create(30, { 0.0f,0.0f });
	spriteNumber3[3]->SetSize({ 120.0f,120.0f });
	spriteNumber3[3]->SetPosition({ 1420.0, 200 });
	spriteNumber4[3] = Sprite::Create(31, { 0.0f,0.0f });
	spriteNumber4[3]->SetSize({ 120.0f,120.0f });
	spriteNumber4[3]->SetPosition({ 1420.0, 200 });
	spriteNumber5[3] = Sprite::Create(32, { 0.0f,0.0f });
	spriteNumber5[3]->SetSize({ 120.0f,120.0f });
	spriteNumber5[3]->SetPosition({ 1420.0, 200 });
	spriteNumber6[3] = Sprite::Create(33, { 0.0f,0.0f });
	spriteNumber6[3]->SetSize({ 120.0f,120.0f });
	spriteNumber6[3]->SetPosition({ 1420.0, 200 });
	spriteNumber7[3] = Sprite::Create(34, { 0.0f,0.0f });
	spriteNumber7[3]->SetSize({ 120.0f,120.0f });
	spriteNumber7[3]->SetPosition({ 1420.0, 200 });
	spriteNumber8[3] = Sprite::Create(35, { 0.0f,0.0f });
	spriteNumber8[3]->SetSize({ 120.0f,120.0f });
	spriteNumber8[3]->SetPosition({ 1420.0, 200 });
	spriteNumber9[3] = Sprite::Create(36, { 0.0f,0.0f });
	spriteNumber9[3]->SetSize({ 120.0f,120.0f });
	spriteNumber9[3]->SetPosition({ 1420.0, 200 });


	spriteNumber0[4] = Sprite::Create(27, { 0.0f,0.0f });
	spriteNumber0[4]->SetSize({ 120.0f,120.0f });
	spriteNumber0[4]->SetPosition({ 1360.0, 200 });
	spriteNumber1[4] = Sprite::Create(28, { 0.0f,0.0f });
	spriteNumber1[4]->SetSize({ 120.0f,120.0f });
	spriteNumber1[4]->SetPosition({ 1360.0, 200 });
	spriteNumber2[4] = Sprite::Create(29, { 0.0f,0.0f });
	spriteNumber2[4]->SetSize({ 120.0f,120.0f });
	spriteNumber2[4]->SetPosition({ 1360.0, 200 });
	spriteNumber3[4] = Sprite::Create(30, { 0.0f,0.0f });
	spriteNumber3[4]->SetSize({ 120.0f,120.0f });
	spriteNumber3[4]->SetPosition({ 1360.0, 200 });
	spriteNumber4[4] = Sprite::Create(31, { 0.0f,0.0f });
	spriteNumber4[4]->SetSize({ 120.0f,120.0f });
	spriteNumber4[4]->SetPosition({ 1360.0, 200 });
	spriteNumber5[4] = Sprite::Create(32, { 0.0f,0.0f });
	spriteNumber5[4]->SetSize({ 120.0f,120.0f });
	spriteNumber5[4]->SetPosition({ 1360.0, 200 });
	spriteNumber6[4] = Sprite::Create(33, { 0.0f,0.0f });
	spriteNumber6[4]->SetSize({ 120.0f,120.0f });
	spriteNumber6[4]->SetPosition({ 1360.0, 200 });
	spriteNumber7[4] = Sprite::Create(34, { 0.0f,0.0f });
	spriteNumber7[4]->SetSize({ 120.0f,120.0f });
	spriteNumber7[4]->SetPosition({ 1360.0, 200 });
	spriteNumber8[4] = Sprite::Create(35, { 0.0f,0.0f });
	spriteNumber8[4]->SetSize({ 120.0f,120.0f });
	spriteNumber8[4]->SetPosition({ 1360.0, 200 });
	spriteNumber9[4] = Sprite::Create(36, { 0.0f,0.0f });
	spriteNumber9[4]->SetSize({ 120.0f,120.0f });
	spriteNumber9[4]->SetPosition({ 1360.0, 200 });

	spriteNumber0[5] = Sprite::Create(27, { 0.0f,0.0f });
	spriteNumber0[5]->SetSize({ 120.0f,120.0f });
	spriteNumber0[5]->SetPosition({ 1300.0, 200 });
	spriteNumber1[5] = Sprite::Create(28, { 0.0f,0.0f });
	spriteNumber1[5]->SetSize({ 120.0f,120.0f });
	spriteNumber1[5]->SetPosition({ 1300, 200 });
	spriteNumber2[5] = Sprite::Create(29, { 0.0f,0.0f });
	spriteNumber2[5]->SetSize({ 120.0f,120.0f });
	spriteNumber2[5]->SetPosition({ 1300, 200 });
	spriteNumber3[5] = Sprite::Create(30, { 0.0f,0.0f });
	spriteNumber3[5]->SetSize({ 120.0f,120.0f });
	spriteNumber3[5]->SetPosition({ 1300, 200 });
	spriteNumber4[5] = Sprite::Create(31, { 0.0f,0.0f });
	spriteNumber4[5]->SetSize({ 120.0f,120.0f });
	spriteNumber4[5]->SetPosition({ 1300, 200 });
	spriteNumber5[5] = Sprite::Create(32, { 0.0f,0.0f });
	spriteNumber5[5]->SetSize({ 120.0f,120.0f });
	spriteNumber5[5]->SetPosition({ 1300, 200 });
	spriteNumber6[5] = Sprite::Create(33, { 0.0f,0.0f });
	spriteNumber6[5]->SetSize({ 120.0f,120.0f });
	spriteNumber6[5]->SetPosition({ 1300, 200 });
	spriteNumber7[5] = Sprite::Create(34, { 0.0f,0.0f });
	spriteNumber7[5]->SetSize({ 120.0f,120.0f });
	spriteNumber7[5]->SetPosition({ 1300, 200 });
	spriteNumber8[5] = Sprite::Create(35, { 0.0f,0.0f });
	spriteNumber8[5]->SetSize({ 120.0f,120.0f });
	spriteNumber8[5]->SetPosition({ 1300, 200 });
	spriteNumber9[5] = Sprite::Create(36, { 0.0f,0.0f });
	spriteNumber9[5]->SetSize({ 120.0f,120.0f });
	spriteNumber9[5]->SetPosition({ 1300, 200 });


	spriteNumber0[6] = Sprite::Create(27, { 0.0f,0.0f });
	spriteNumber0[6]->SetSize({ 120.0f,120.0f });
	spriteNumber0[6]->SetPosition({ 300, 200 });
	spriteNumber1[6] = Sprite::Create(28, { 0.0f,0.0f });
	spriteNumber1[6]->SetSize({ 120.0f,120.0f });
	spriteNumber1[6]->SetPosition({ 300, 200 });
	spriteNumber2[6] = Sprite::Create(29, { 0.0f,0.0f });
	spriteNumber2[6]->SetSize({ 120.0f,120.0f });
	spriteNumber2[6]->SetPosition({ 300, 200 });
	spriteNumber3[6] = Sprite::Create(30, { 0.0f,0.0f });
	spriteNumber3[6]->SetSize({ 120.0f,120.0f });
	spriteNumber3[6]->SetPosition({ 300, 200 });
	spriteNumber4[6] = Sprite::Create(31, { 0.0f,0.0f });
	spriteNumber4[6]->SetSize({ 120.0f,120.0f });
	spriteNumber4[6]->SetPosition({ 300, 200 });
	spriteNumber5[6] = Sprite::Create(32, { 0.0f,0.0f });
	spriteNumber5[6]->SetSize({ 120.0f,120.0f });
	spriteNumber5[6]->SetPosition({ 300, 200 });
	spriteNumber6[6] = Sprite::Create(33, { 0.0f,0.0f });
	spriteNumber6[6]->SetSize({ 120.0f,120.0f });
	spriteNumber6[6]->SetPosition({ 300, 200 });
	spriteNumber7[6] = Sprite::Create(34, { 0.0f,0.0f });
	spriteNumber7[6]->SetSize({ 120.0f,120.0f });
	spriteNumber7[6]->SetPosition({ 300, 200 });
	spriteNumber8[6] = Sprite::Create(35, { 0.0f,0.0f });
	spriteNumber8[6]->SetSize({ 120.0f,120.0f });
	spriteNumber8[6]->SetPosition({ 300, 200 });
	spriteNumber9[6] = Sprite::Create(36, { 0.0f,0.0f });
	spriteNumber9[6]->SetSize({ 120.0f,120.0f });
	spriteNumber9[6]->SetPosition({ 300, 200 });

	spriteNumber0[7] = Sprite::Create(27, { 0.0f,0.0f });
	spriteNumber0[7]->SetSize({ 120.0f,120.0f });
	spriteNumber0[7]->SetPosition({ 240, 200 });
	spriteNumber1[7] = Sprite::Create(28, { 0.0f,0.0f });
	spriteNumber1[7]->SetSize({ 120.0f,120.0f });
	spriteNumber1[7]->SetPosition({ 240, 200 });
	spriteNumber2[7] = Sprite::Create(29, { 0.0f,0.0f });
	spriteNumber2[7]->SetSize({ 120.0f,120.0f });
	spriteNumber2[7]->SetPosition({ 240, 200 });
	spriteNumber3[7] = Sprite::Create(30, { 0.0f,0.0f });
	spriteNumber3[7]->SetSize({ 120.0f,120.0f });
	spriteNumber3[7]->SetPosition({ 240, 200 });
	spriteNumber4[7] = Sprite::Create(31, { 0.0f,0.0f });
	spriteNumber4[7]->SetSize({ 120.0f,120.0f });
	spriteNumber4[7]->SetPosition({ 240, 200 });
	spriteNumber5[7] = Sprite::Create(32, { 0.0f,0.0f });
	spriteNumber5[7]->SetSize({ 120.0f,120.0f });
	spriteNumber5[7]->SetPosition({ 240, 200 });
	spriteNumber6[7] = Sprite::Create(33, { 0.0f,0.0f });
	spriteNumber6[7]->SetSize({ 120.0f,120.0f });
	spriteNumber6[7]->SetPosition({ 240, 200 });
	spriteNumber7[7] = Sprite::Create(34, { 0.0f,0.0f });
	spriteNumber7[7]->SetSize({ 120.0f,120.0f });
	spriteNumber7[7]->SetPosition({ 240, 200 });
	spriteNumber8[7] = Sprite::Create(35, { 0.0f,0.0f });
	spriteNumber8[7]->SetSize({ 120.0f,120.0f });
	spriteNumber8[7]->SetPosition({ 240, 200 });
	spriteNumber9[7] = Sprite::Create(36, { 0.0f,0.0f });
	spriteNumber9[7]->SetSize({ 120.0f,120.0f });
	spriteNumber9[7]->SetPosition({ 240, 200 });

	spriteNumber0[8] = Sprite::Create(27, { 0.0f,0.0f });
	spriteNumber0[8]->SetSize({ 120.0f,120.0f });
	spriteNumber0[8]->SetPosition({ 180, 200 });
	spriteNumber1[8] = Sprite::Create(28, { 0.0f,0.0f });
	spriteNumber1[8]->SetSize({ 120.0f,120.0f });
	spriteNumber1[8]->SetPosition({ 180, 200 });
	spriteNumber2[8] = Sprite::Create(29, { 0.0f,0.0f });
	spriteNumber2[8]->SetSize({ 120.0f,120.0f });
	spriteNumber2[8]->SetPosition({ 180, 200 });
	spriteNumber3[8] = Sprite::Create(30, { 0.0f,0.0f });
	spriteNumber3[8]->SetSize({ 120.0f,120.0f });
	spriteNumber3[8]->SetPosition({ 180, 200 });
	spriteNumber4[8] = Sprite::Create(31, { 0.0f,0.0f });
	spriteNumber4[8]->SetSize({ 120.0f,120.0f });
	spriteNumber4[8]->SetPosition({ 180, 200 });
	spriteNumber5[8] = Sprite::Create(32, { 0.0f,0.0f });
	spriteNumber5[8]->SetSize({ 120.0f,120.0f });
	spriteNumber5[8]->SetPosition({ 180, 200 });
	spriteNumber6[8] = Sprite::Create(33, { 0.0f,0.0f });
	spriteNumber6[8]->SetSize({ 120.0f,120.0f });
	spriteNumber6[8]->SetPosition({ 180, 200 });
	spriteNumber7[8] = Sprite::Create(34, { 0.0f,0.0f });
	spriteNumber7[8]->SetSize({ 120.0f,120.0f });
	spriteNumber7[8]->SetPosition({ 180, 200 });
	spriteNumber8[8] = Sprite::Create(35, { 0.0f,0.0f });
	spriteNumber8[8]->SetSize({ 120.0f,120.0f });
	spriteNumber8[8]->SetPosition({ 180, 200 });
	spriteNumber9[8] = Sprite::Create(36, { 0.0f,0.0f });
	spriteNumber9[8]->SetSize({ 120.0f,120.0f });
	spriteNumber9[8]->SetPosition({ 180, 200 });

	spriteClearScore = Sprite::Create(37, { 0.0f,0.0f });
	spriteClearScore->SetSize({ 1314.0f,580.0f });
	spriteClearScore->SetPosition({ 300.0, 40 });

	spriteClearTextL1 = Sprite::Create(38, { 0.0f,0.0f });
	spriteClearTextL1->SetSize({ 534.0f,134.0f });
	spriteClearTextL1->SetPosition({ 300.0, 680 });

	spriteClearTextL2 = Sprite::Create(39, { 0.0f,0.0f });
	spriteClearTextL2->SetSize({ 746.0f,266.0f });
	spriteClearTextL2->SetPosition({ 180.0, 600 });

	spriteClearTextR1 = Sprite::Create(40, { 0.0f,0.0f });
	spriteClearTextR1->SetSize({ 492.0f,127.0f });
	spriteClearTextR1->SetPosition({ 1140.0, 680 });

	spriteClearTextR2 = Sprite::Create(41, { 0.0f,0.0f });
	spriteClearTextR2->SetSize({ 746.0f,266.0f });
	spriteClearTextR2->SetPosition({ 1000.0, 600 });


	spritePlayBack = Sprite::Create(42, { 0.0f,0.0f });
	spritePlayBack->SetSize({ 1920 * 1.5,1920 * 1.5 });
	spritePlayBack->SetPosition({ 960, 960 });
	spritePlayBack->SetAnchorPoint({0.5,0.5});

	spritePlayTime = Sprite::Create(43, { 0.0f,0.0f });
	spritePlayTime->SetSize({ 344.0f,122.0f });
	spritePlayTime->SetPosition({ 80.0, 100 });

	spritePlayScore = Sprite::Create(44, { 0.0f,0.0f });
	spritePlayScore->SetSize({ 343.0f,103.0f });
	spritePlayScore->SetPosition({ 1460.0, 100 });

	spriteScorePluse = Sprite::Create(26, { 0.0f,0.0f });
	spriteScorePluse->SetSize({ 343.0f,103.0f });
	spriteScorePluse->SetPosition({ 1260.0, 300 });

	spriteRogo = Sprite::Create(45, { 0.0f,0.0f });
	spriteRogo->SetAnchorPoint({ 0.5f, 0.5f });
	spriteRogo->SetSize({ 1920.0f,1080.0f });
	spriteRogo->SetPosition({ 1920.0f / 2,1080.0f / 2 });

	spriteRogoBG = Sprite::Create(46, { 0.0f,0.0f });
	spriteRogoBG->SetAnchorPoint({ 0.5f, 0.5f });
	spriteRogoBG->SetSize({ 1920.0f,1080.0f });
	spriteRogoBG->SetPosition({ 1920.0f / 2,1080.0f / 2 });

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
	audio->PlayBGM("Resources/BGM/title_bgm.wav", true);
	
	spriteNumber0[2]->SetSize({ 60.0f,120.0f });
	spriteNumber1[2]->SetSize({ 60.0f,120.0f });
	spriteNumber2[2]->SetSize({ 60.0f,120.0f });
	spriteNumber3[2]->SetSize({ 60.0f,120.0f });
	spriteNumber4[2]->SetSize({ 60.0f,120.0f });
	spriteNumber5[2]->SetSize({ 60.0f,120.0f });
	spriteNumber6[2]->SetSize({ 60.0f,120.0f });
	spriteNumber7[2]->SetSize({ 60.0f,120.0f });
	spriteNumber8[2]->SetSize({ 60.0f,120.0f });
	spriteNumber9[2]->SetSize({ 60.0f,120.0f });
	spriteNumber0[3]->SetSize({ 60.0f,120.0f });
	spriteNumber1[3]->SetSize({ 60.0f,120.0f });
	spriteNumber2[3]->SetSize({ 60.0f,120.0f });
	spriteNumber3[3]->SetSize({ 60.0f,120.0f });
	spriteNumber4[3]->SetSize({ 60.0f,120.0f });
	spriteNumber5[3]->SetSize({ 60.0f,120.0f });
	spriteNumber6[3]->SetSize({ 60.0f,120.0f });
	spriteNumber7[3]->SetSize({ 60.0f,120.0f });
	spriteNumber8[3]->SetSize({ 60.0f,120.0f });
	spriteNumber9[3]->SetSize({ 60.0f,120.0f });
	spriteNumber0[4]->SetSize({ 60.0f,120.0f });
	spriteNumber1[4]->SetSize({ 60.0f,120.0f });
	spriteNumber2[4]->SetSize({ 60.0f,120.0f });
	spriteNumber3[4]->SetSize({ 60.0f,120.0f });
	spriteNumber4[4]->SetSize({ 60.0f,120.0f });
	spriteNumber5[4]->SetSize({ 60.0f,120.0f });
	spriteNumber6[4]->SetSize({ 60.0f,120.0f });
	spriteNumber7[4]->SetSize({ 60.0f,120.0f });
	spriteNumber8[4]->SetSize({ 60.0f,120.0f });
	spriteNumber9[4]->SetSize({ 60.0f,120.0f });
	spriteNumber0[5]->SetSize({ 60.0f,120.0f });
	spriteNumber1[5]->SetSize({ 60.0f,120.0f });
	spriteNumber2[5]->SetSize({ 60.0f,120.0f });
	spriteNumber3[5]->SetSize({ 60.0f,120.0f });
	spriteNumber4[5]->SetSize({ 60.0f,120.0f });
	spriteNumber5[5]->SetSize({ 60.0f,120.0f });
	spriteNumber6[5]->SetSize({ 60.0f,120.0f });
	spriteNumber7[5]->SetSize({ 60.0f,120.0f });
	spriteNumber8[5]->SetSize({ 60.0f,120.0f });
	spriteNumber9[5]->SetSize({ 60.0f,120.0f });
	spriteNumber0[6]->SetSize({ 60.0f,120.0f });
	spriteNumber1[6]->SetSize({ 60.0f,120.0f });
	spriteNumber2[6]->SetSize({ 60.0f,120.0f });
	spriteNumber3[6]->SetSize({ 60.0f,120.0f });
	spriteNumber4[6]->SetSize({ 60.0f,120.0f });
	spriteNumber5[6]->SetSize({ 60.0f,120.0f });
	spriteNumber6[6]->SetSize({ 60.0f,120.0f });
	spriteNumber7[6]->SetSize({ 60.0f,120.0f });
	spriteNumber8[6]->SetSize({ 60.0f,120.0f });
	spriteNumber9[6]->SetSize({ 60.0f,120.0f });
	spriteNumber0[7]->SetSize({ 60.0f,120.0f });
	spriteNumber1[7]->SetSize({ 60.0f,120.0f });
	spriteNumber2[7]->SetSize({ 60.0f,120.0f });
	spriteNumber3[7]->SetSize({ 60.0f,120.0f });
	spriteNumber4[7]->SetSize({ 60.0f,120.0f });
	spriteNumber5[7]->SetSize({ 60.0f,120.0f });
	spriteNumber6[7]->SetSize({ 60.0f,120.0f });
	spriteNumber7[7]->SetSize({ 60.0f,120.0f });
	spriteNumber8[7]->SetSize({ 60.0f,120.0f });
	spriteNumber9[7]->SetSize({ 60.0f,120.0f });
	spriteNumber0[8]->SetSize({ 60.0f,120.0f });
	spriteNumber1[8]->SetSize({ 60.0f,120.0f });
	spriteNumber2[8]->SetSize({ 60.0f,120.0f });
	spriteNumber3[8]->SetSize({ 60.0f,120.0f });
	spriteNumber4[8]->SetSize({ 60.0f,120.0f });
	spriteNumber5[8]->SetSize({ 60.0f,120.0f });
	spriteNumber6[8]->SetSize({ 60.0f,120.0f });
	spriteNumber7[8]->SetSize({ 60.0f,120.0f });
	spriteNumber8[8]->SetSize({ 60.0f,120.0f });
	spriteNumber9[8]->SetSize({ 60.0f,120.0f });

	
}

void GameScene::Update()
{
	debugText.Print(20, 20, 2.0f, "END : ESC");
	if (scene == ROGO)
	{
		spriteRogo->SetSize(rogoSize);
		spriteRogo->SetRotation(rogoRot);

		rogoSize.x += 1920 / 30;
		rogoSize.y += 1080 / 30;
		rogoRot += 72;

		if(rogoSize.x >= 1920 || rogoSize.y >= 1080)
		{
			rogoSize.x = 1920;
			rogoSize.y = 1080;
			rogoRot = 0;
		}

		audio->StopBGM();
		rogoTimer--;

		if (rogoTimer <= 0)
		{
			scene = TITLE;
			audio->PlayBGM("Resources/BGM/title_bgm.wav", true);
			rogoSceneChange = true;
		}
	}
	else if (scene == TITLE)
	{
		if (rogoSceneChange == true)
		{
			spriteRogo->SetSize(rogoSize);
			spriteRogoBG->SetSize(rogoSize);
			spriteRogo->SetRotation(rogoRot);
			spriteRogoBG->SetRotation(rogoRot);

			rogoSize.x -= 1920 / 30;
			rogoSize.y -= 1080 / 30;
			rogoRot -= 72;

			rogoSceneChangeCount--;

			if (rogoSceneChangeCount <= 0)
			{
				rogoSceneChange = false;

				rogoSize.x = 0;
				rogoSize.y = 0;
				rogoRot = 0;
			}
		}

		if (bomSceneChange4 == true)
		{
			sceneChangeCount4++;
			if (sceneChangeCount4 > 150)
			{
				bomSceneChange3 = false;
				for (int i = 0; i < 12; i++)
				{
					size2.x -= size2.x / 100;
					size2.y -= size2.y / 100;
					pos2.x += (size2.x / 100) / 2;
					pos2.y += (size2.y / 100) / 2;
				}

				spriteBom2->SetPosition(pos2);
				spriteBom2->SetSize(size2);
			}
			if (sceneChangeCount4 > 220)
			{
				pos = { 954.03,532.74 };
				size = { 8.47,10.3 };
				pos2 = { -800,-1625 };
				size2 = { 3560,4330 };
				bomSceneChange4 = false;
			}
		}
		titleScroll.x -= 1920 / 100;
		titleScroll.y += 1080 / 100;
		if (titleScroll.x <= -1920)
		{
			titleScroll.x = -1920 / 100;
		}
		if (titleScroll.y >= 1080)
		{
			titleScroll.y = 1080 / 100;
		}
		spriteTitleScroll1->SetPosition({ titlePos1.x + titleScroll.x,titlePos1.y + titleScroll.y });
		spriteTitleScroll2->SetPosition({ titlePos2.x + titleScroll.x,titlePos2.y + titleScroll.y });
		spriteTitleScroll3->SetPosition({ titlePos3.x + titleScroll.x,titlePos3.y + titleScroll.y });
		spriteTitleScroll4->SetPosition({ titlePos4.x + titleScroll.x,titlePos4.y + titleScroll.y });

		if (titleTextPatern1 == 0)
		{
			titleTextCount1++;
			titleTextValue.y--;
			if (titleTextCount1 > 40)
			{
				titleTextCount1 = 0;
				titleTextPatern1 = 1;
			}
		}
		if (titleTextPatern1 == 1)
		{
			titleTextCount1++;
			titleTextValue.y++;
			if (titleTextCount1 > 40)
			{
				titleTextCount1 = 0;
				titleTextPatern1 = 3;
			}
		}
		if (titleTextPatern1 == 3)
		{
			titleTextCount1++;
			titleTextValue.y--;
			if (titleTextCount1 > 40)
			{
				titleTextCount1 = 0;
				titleTextPatern1 = 4;
			}
		}
		if (titleTextPatern1 == 4)
		{
			titleTextCount1++;
			titleTextValue.y++;
			if (titleTextCount1 > 40)
			{
				titleTextCount1 = 0;
				titleTextPatern1 = 0;
			}
		}


		spriteTitle2->SetPosition({ titleTextPos.x + titleTextValue.x, titleTextPos.y + titleTextValue.y });

		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE)&& bomSceneChange4 == false)
		{
			
			sceneChangeCount3 = 0;

			audio->PlaySE("Resources/SE/title_dicided.wav", false);
			map->InitializeValue();
			player->InitializeValue();
			enemy->EndInitialize();
			bomSceneChange = true;
			text1Draw = true;
			textShake = true;
		}
		if (textShake)
		{
			XMFLOAT2 shakeValue;
			shakeCount++;
			std::random_device rnd1;
			std::mt19937 mt1(rnd1());
			std::uniform_int_distribution<>rand1(0, 10);//0~3の範囲
			shakeValue.x = rand1(mt1);

			std::random_device rnd2;
			std::mt19937 mt2(rnd2());
			std::uniform_int_distribution<>rand2(0, 10);//0~3の範囲
			shakeValue.y = rand2(mt2);

			spriteText1->SetPosition({ 589 + shakeValue.x, 830 + shakeValue.y });

		}
		if (shakeCount > 10)
		{
			spriteText1->SetPosition({ 589.0, 830 });
			textShake = false;
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
				text1Draw = false;
				textShake = false;
				shakeCount = 0;
				scene = PLAY;
			}
		}
	}
	else if (scene == PLAY)
	{
	spriteNumber0s->SetPosition({ 1660.0, 200 });
	spriteNumber0[0]->SetPosition({ 1600.0, 200 });
	spriteNumber0[1]->SetPosition({ 1540.0, 200 });

	spriteNumber0[2]->SetPosition({ 1480.0, 200 });
	spriteNumber1[2]->SetPosition({ 1480.0, 200 });
	spriteNumber2[2]->SetPosition({ 1480.0, 200 });
	spriteNumber3[2]->SetPosition({ 1480.0, 200 });
	spriteNumber4[2]->SetPosition({ 1480.0, 200 });
	spriteNumber5[2]->SetPosition({ 1480.0, 200 });
	spriteNumber6[2]->SetPosition({ 1480.0, 200 });
	spriteNumber7[2]->SetPosition({ 1480.0, 200 });
	spriteNumber8[2]->SetPosition({ 1480.0, 200 });
	spriteNumber9[2]->SetPosition({ 1480.0, 200 });

	spriteNumber0[3]->SetPosition({ 1420.0, 200 });
	spriteNumber1[3]->SetPosition({ 1420.0, 200 });
	spriteNumber2[3]->SetPosition({ 1420.0, 200 });
	spriteNumber3[3]->SetPosition({ 1420.0, 200 });
	spriteNumber4[3]->SetPosition({ 1420.0, 200 });
	spriteNumber5[3]->SetPosition({ 1420.0, 200 });
	spriteNumber6[3]->SetPosition({ 1420.0, 200 });
	spriteNumber7[3]->SetPosition({ 1420.0, 200 });
	spriteNumber8[3]->SetPosition({ 1420.0, 200 });
	spriteNumber9[3]->SetPosition({ 1420.0, 200 });

	spriteNumber0[4]->SetPosition({ 1360.0, 200 });
	spriteNumber1[4]->SetPosition({ 1360.0, 200 });
	spriteNumber2[4]->SetPosition({ 1360.0, 200 });
	spriteNumber3[4]->SetPosition({ 1360.0, 200 });
	spriteNumber4[4]->SetPosition({ 1360.0, 200 });
	spriteNumber5[4]->SetPosition({ 1360.0, 200 });
	spriteNumber6[4]->SetPosition({ 1360.0, 200 });
	spriteNumber7[4]->SetPosition({ 1360.0, 200 });
	spriteNumber8[4]->SetPosition({ 1360.0, 200 });
	spriteNumber9[4]->SetPosition({ 1360.0, 200 });

	spriteNumber0[5]->SetPosition({ 1300.0, 200 });
	spriteNumber1[5]->SetPosition({ 1300.0, 200 });
	spriteNumber2[5]->SetPosition({ 1300.0, 200 });
	spriteNumber3[5]->SetPosition({ 1300.0, 200 });
	spriteNumber4[5]->SetPosition({ 1300.0, 200 });
	spriteNumber5[5]->SetPosition({ 1300.0, 200 });
	spriteNumber6[5]->SetPosition({ 1300.0, 200 });
	spriteNumber7[5]->SetPosition({ 1300.0, 200 });
	spriteNumber8[5]->SetPosition({ 1300.0, 200 });
	spriteNumber9[5]->SetPosition({ 1300.0, 200 });

		backRotation-= 0.1;
		spritePlayBack->SetRotation(backRotation);

		if (enemy->GetScorePluse())
		{
			scorePluse = true;
			scorePlusePos = { 1160.0, 250 };
			enemy->SetScorePluse();

		}
		if (scorePluse == 1)
		{
			scorePlusePos.y --;
			spriteScorePluse->SetPosition(scorePlusePos);
			if (scorePlusePos.y < 100)
			{
				scorePluse = false;
			}
		}
		if (scorePluse == 0)
		{
			scorePlusePos = { 1460.0, 100 };
			spriteScorePluse->SetPosition(scorePlusePos);
		}

		if (bomSceneChange2 == true)
		{
			sceneChangeCount2++;
			if (sceneChangeCount2 > 150)
			{
				bomSceneChange = false;
				for (int i = 0; i < 12; i++)
				{
					size2.x -= size2.x / 100;
					size2.y -= size2.y / 100;
					pos2.x += (size2.x / 100) / 2;
					pos2.y += (size2.y / 100) / 2;
				}

				spriteBom2->SetPosition(pos2);
				spriteBom2->SetSize(size2);
			}
			if (sceneChangeCount2 > 220)
			{
				startCountFlag = true;
 				bomSceneChange = false;
				startCountFlag2 = true;
			}
		}


		if (startCountFlag2)
		{
			startCount++;
		}
		if (startCount > 180)
		{
			startCountFlag = false;
		}

		if (player->GetPlayCount() < 180)
		{
			endCountFlag = true;
		}
		else
		{
			endCountFlag = true;
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
			  spriteNumber0s->SetPosition({ 1100.0,300 });
			spriteNumber0[0]->SetPosition({ 1040.0,300 });
			spriteNumber0[1]->SetPosition({ 980.0, 300 });

			spriteNumber0[2]->SetPosition({ 920.0, 300 });
			spriteNumber1[2]->SetPosition({ 920.0, 300 });
			spriteNumber2[2]->SetPosition({ 920.0, 300 });
			spriteNumber3[2]->SetPosition({ 920.0, 300 });
			spriteNumber4[2]->SetPosition({ 920.0, 300 });
			spriteNumber5[2]->SetPosition({ 920.0, 300 });
			spriteNumber6[2]->SetPosition({ 920.0, 300 });
			spriteNumber7[2]->SetPosition({ 920.0, 300 });
			spriteNumber8[2]->SetPosition({ 920.0, 300 });
			spriteNumber9[2]->SetPosition({ 920.0, 300 });

			spriteNumber0[3]->SetPosition({ 860.0, 300 });
			spriteNumber1[3]->SetPosition({ 860.0, 300 });
			spriteNumber2[3]->SetPosition({ 860.0, 300 });
			spriteNumber3[3]->SetPosition({ 860.0, 300 });
			spriteNumber4[3]->SetPosition({ 860.0, 300 });
			spriteNumber5[3]->SetPosition({ 860.0, 300 });
			spriteNumber6[3]->SetPosition({ 860.0, 300 });
			spriteNumber7[3]->SetPosition({ 860.0, 300 });
			spriteNumber8[3]->SetPosition({ 860.0, 300 });
			spriteNumber9[3]->SetPosition({ 860.0, 300 });

			spriteNumber0[4]->SetPosition({ 800.0, 300 });
			spriteNumber1[4]->SetPosition({ 800.0, 300 });
			spriteNumber2[4]->SetPosition({ 800.0, 300 });
			spriteNumber3[4]->SetPosition({ 800.0, 300 });
			spriteNumber4[4]->SetPosition({ 800.0, 300 });
			spriteNumber5[4]->SetPosition({ 800.0, 300 });
			spriteNumber6[4]->SetPosition({ 800.0, 300 });
			spriteNumber7[4]->SetPosition({ 800.0, 300 });
			spriteNumber8[4]->SetPosition({ 800.0, 300 });
			spriteNumber9[4]->SetPosition({ 800.0, 300 });

			spriteNumber0[5]->SetPosition({ 740.0, 300 });
			spriteNumber1[5]->SetPosition({ 740.0, 300 });
			spriteNumber2[5]->SetPosition({ 740.0, 300 });
			spriteNumber3[5]->SetPosition({ 740.0, 300 });
			spriteNumber4[5]->SetPosition({ 740.0, 300 });
			spriteNumber5[5]->SetPosition({ 740.0, 300 });
			spriteNumber6[5]->SetPosition({ 740.0, 300 });
			spriteNumber7[5]->SetPosition({ 740.0, 300 });
			spriteNumber8[5]->SetPosition({ 740.0, 300 });
			spriteNumber9[5]->SetPosition({ 740.0, 300 });
			bomSceneChange = false;
			sceneChangeCount = 0;

			bomSceneChange3 = false;
			sceneChangeCount3 = 0;

			bomSceneChange4 = false;
			sceneChangeCount4 = 0;
			scene = CLEAR;
		}
		int mapY = (player->GetPos().z / 4) + ((8 + 1) / 2);
		int mapX = (player->GetPos().x / 4) + ((8 + 1) / 2);
		if (100000 <= enemy->GetScore())
		{
			score4 = enemy->GetScore() / 10000;
		}
		if (10000 <= enemy->GetScore())
		{
			score3 = enemy->GetScore() / 10000;
		}
		if (1000 <= enemy->GetScore())
		{
			score2 = enemy->GetScore() / 1000;
		}
		if (100 <= enemy->GetScore())
		{
			score1 = enemy->GetScore() / 100;
		}

		if (6000 <= player->GetPlayCount())
		{
			time3 = player->GetPlayCount() / 6000;
		}
		if (600 <= player->GetPlayCount())
		{
			time2 = player->GetPlayCount() / 600;
		}
		if (60 <= player->GetPlayCount())
		{
			time1 = player->GetPlayCount() / 60;
		}
		
		
		/*debugText.Print(20, 70, 2.0f, "score :  %d", enemy->GetScore());
		debugText.Print(20, 100, 2.0f, "faze :  %d", enemy->GetWave());
		debugText.Print(20, 130, 2.0f, "time :  %d", player->GetPlayCount() / 60);
		debugText.Print(20, 160, 2.0f, "a :  %d", player->GetLv(0));
		debugText.Print(20, 180, 2.0f, "b :  %f", player->GetBomPos(0).x);
		debugText.Print(20, 210, 2.0f, "e :  %f", enemy->GetPos(0).x);

		debugText.Print(20, 260, 2.0f, "epos :  %f %f", enemy->GetPos(0).x, enemy->GetPos(0).z);

		debugText.Print(20, 290, 2.0f, "ppos :  %f %f", player->GetPos().x, player->GetPos().z);*/
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
		enemy->Update(player, map, startCountFlag);
		player->Update(map, startCountFlag, startCountFlag);
		particle3d->Update();
		camera->Update();
		objSkydome->Update();
		objGround->Update();
		light->Update();
		stopFlag = map->GetStopFlag();

	}
	else if (scene == CLEAR)
	{
		startCountFlag = true;
		startCount = 0;
		startCountFlag2 = false;
		endCountFlag = false;

		titleScroll.x -= 1920 / 100;
		titleScroll.y += 1080 / 100;
		if (titleScroll.x <= -1920)
		{
			titleScroll.x = -1920 / 100;
		}
		if (titleScroll.y >= 1080)
		{
			titleScroll.y = 1080 / 100;
		}
		spriteTitleScroll1->SetPosition({ titlePos1.x + titleScroll.x,titlePos1.y + titleScroll.y });
		spriteTitleScroll2->SetPosition({ titlePos2.x + titleScroll.x,titlePos2.y + titleScroll.y });
		spriteTitleScroll3->SetPosition({ titlePos3.x + titleScroll.x,titlePos3.y + titleScroll.y });
		spriteTitleScroll4->SetPosition({ titlePos4.x + titleScroll.x,titlePos4.y + titleScroll.y });
		if (Input::GetInstance()->KeybordTrigger(DIK_LEFT) && bomSceneChange3 == false)
		{
			audio->PlaySE("Resources/SE/result_select.wav", false);
			shakeCount = 0;
			restart = 0;
			textShake = true;
		}
		else if (Input::GetInstance()->KeybordTrigger(DIK_RIGHT ) &&bomSceneChange3 == false)
		{
			audio->PlaySE("Resources/SE/result_select.wav", false);
			shakeCount = 0;
			restart = 1;
			textShake = true;
		}
		if (restart == 0)
		{
			if (textShake)
			{
				XMFLOAT2 shakeValue;
				shakeCount++;
				std::random_device rnd1;
				std::mt19937 mt1(rnd1());
				std::uniform_int_distribution<>rand1(0, 10);//0~3の範囲
				shakeValue.x = rand1(mt1);

				std::random_device rnd2;
				std::mt19937 mt2(rnd2());
				std::uniform_int_distribution<>rand2(0, 10);//0~3の範囲
				shakeValue.y = rand2(mt2);

				spriteClearTextL2->SetPosition({ 180 + shakeValue.x, 600 + shakeValue.y });

			}
			if (shakeCount > 10)
			{
				spriteClearTextL2->SetPosition({ 180.0, 600 });
				textShake = false;
			}
		}
		if (restart == 1)
		{
			
			if (textShake)
			{
				XMFLOAT2 shakeValue;
				shakeCount++;
				std::random_device rnd1;
				std::mt19937 mt1(rnd1());
				std::uniform_int_distribution<>rand1(0, 10);//0~3の範囲
				shakeValue.x = rand1(mt1);

				std::random_device rnd2;
				std::mt19937 mt2(rnd2());
				std::uniform_int_distribution<>rand2(0, 10);//0~3の範囲
				shakeValue.y = rand2(mt2);

				spriteClearTextR2->SetPosition({ 1000 + shakeValue.x, 600 + shakeValue.y });

			}
			if (shakeCount > 10)
			{
				spriteClearTextR2->SetPosition({ 1000.0, 600 });
				textShake = false;
			}
		}

		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && restart == 1 && bomSceneChange == false)
		{
			//scene = TITLE;
			audio->PlaySE("Resources/SE/title_dicided.wav", false);
			pos = { 954.03,532.74 };
			size = { 8.47,10.3 };

			pos2 = { -800,-1625 };
			size2 = { 3560,4330 };
			bomSceneChange = false;
			sceneChangeCount = 0;
			bomSceneChange2 = true;
			sceneChangeCount2 = 0;
			bomSceneChange4 = false;
			sceneChangeCount4 = 0;

			spriteBom->SetPosition(pos);
			spriteBom->SetSize(size);
			spriteBom2->SetPosition(pos2);
			spriteBom2->SetSize(size2);

			map->InitializeValue();
			player->InitializeValue();
			enemy->EndInitialize();
			enemy->Update(player, map, startCountFlag);
			bomSceneChange3 = true;
		}

		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && restart == 0 && bomSceneChange3 == false)
		{
			pos = { 954.03,532.74 };
			size = { 8.47,10.3 };
			pos2 = { -800,-1625 };
			size2 = { 3560,4330 };
			bomSceneChange = true;
			sceneChangeCount = 0;
			bomSceneChange2 = true;
			sceneChangeCount2 = 0;
			bomSceneChange4 = false;
			sceneChangeCount4 = 0;

			spriteBom->SetPosition(pos);
			spriteBom->SetSize(size);
			spriteBom2->SetPosition(pos2);
			spriteBom2->SetSize(size2);

			map->InitializeValue();
			player->InitializeValue();
			enemy->EndInitialize();
			enemy->Update(player, map, startCountFlag);
			bomSceneChange3 = true;
			
		}
		if (bomSceneChange3 == true)
		{
			sceneChangeCount3++;
			for (int i = 0; i < 12; i++)
			{
				size.x += size.x / 100;
				size.y += size.y / 100;
				pos.x -= (size.x / 100) / 2;
				pos.y -= (size.y / 100) / 2;
			}

			spriteBom->SetPosition(pos);
			spriteBom->SetSize(size);

			if (sceneChangeCount3 > 60)
			{
				
				
				if (restart == 1)
				{
					bomSceneChange4 = true;
					audio->StopBGM();
					audio->PlayBGM("Resources/BGM/title_bgm.wav", true);
					scene = TITLE;
				}
				if (restart == 0)
				{
					audio->StopBGM();
					audio->PlayBGM("Resources/BGM/game_bgm.wav", true);
					scene = PLAY;
				}
			}
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
	spritePlayBack->Draw();
	
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
		//objSkydome->Draw();
		//objGround->Draw();
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

	if (scene == ROGO)
	{
		spriteRogoBG->Draw();
		spriteRogo->Draw();
	}
	if (scene == TITLE)
	{

		spriteTitleScroll1->Draw();
		spriteTitleScroll2->Draw();
		spriteTitleScroll3->Draw();
		spriteTitleScroll4->Draw();
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

		if (rogoSceneChange == true)
		{
			spriteRogoBG->Draw();
			spriteRogo->Draw();
		}
		
		if (bomSceneChange4 == true)
		{
			spriteBom2->Draw();
		}
		if (bomSceneChange3 == true)
		{
			spriteBom->Draw();
		}
	}
	if (scene == PLAY)
	{

		spriteNumber0[0]->Draw();
		if (enemy->GetScore() != 0)
		{
			spriteNumber0[1]->Draw();
		}
		if (100 <= enemy->GetScore())
		{
			if (score1 - 10 * score2 == 0) { spriteNumber0[2]->Draw(); }
			if (score1 - 10 * score2 == 1) { spriteNumber1[2]->Draw(); }
			if (score1 - 10 * score2 == 2) { spriteNumber2[2]->Draw(); }
			if (score1 - 10 * score2 == 3) { spriteNumber3[2]->Draw(); }
			if (score1 - 10 * score2 == 4) { spriteNumber4[2]->Draw(); }
			if (score1 - 10 * score2 == 5) { spriteNumber5[2]->Draw(); }
			if (score1 - 10 * score2 == 6) { spriteNumber6[2]->Draw(); }
			if (score1 - 10 * score2 == 7) { spriteNumber7[2]->Draw(); }
			if (score1 - 10 * score2 == 8) { spriteNumber8[2]->Draw(); }
			if (score1 - 10 * score2 == 9) { spriteNumber9[2]->Draw(); }
		}
		if (1000 <= enemy->GetScore())
		{
			if (score2 - 10 * score3 == 0) { spriteNumber0[3]->Draw(); }
			if (score2 - 10 * score3 == 1) { spriteNumber1[3]->Draw(); }
			if (score2 - 10 * score3 == 2) { spriteNumber2[3]->Draw(); }
			if (score2 - 10 * score3 == 3) { spriteNumber3[3]->Draw(); }
			if (score2 - 10 * score3 == 4) { spriteNumber4[3]->Draw(); }
			if (score2 - 10 * score3 == 5) { spriteNumber5[3]->Draw(); }
			if (score2 - 10 * score3 == 6) { spriteNumber6[3]->Draw(); }
			if (score2 - 10 * score3 == 7) { spriteNumber7[3]->Draw(); }
			if (score2 - 10 * score3 == 8) { spriteNumber8[3]->Draw(); }
			if (score2 - 10 * score3 == 9) { spriteNumber9[3]->Draw(); }
		}
		if (10000 <= enemy->GetScore())
		{
			if (score3 - 10 * score4 == 0) { spriteNumber0[4]->Draw(); }
			if (score3 - 10 * score4 == 1) { spriteNumber1[4]->Draw(); }
			if (score3 - 10 * score4 == 2) { spriteNumber2[4]->Draw(); }
			if (score3 - 10 * score4 == 3) { spriteNumber3[4]->Draw(); }
			if (score3 - 10 * score4 == 4) { spriteNumber4[4]->Draw(); }
			if (score3 - 10 * score4 == 5) { spriteNumber5[4]->Draw(); }
			if (score3 - 10 * score4 == 6) { spriteNumber6[4]->Draw(); }
			if (score3 - 10 * score4 == 7) { spriteNumber7[4]->Draw(); }
			if (score3 - 10 * score4 == 8) { spriteNumber8[4]->Draw(); }
			if (score3 - 10 * score4 == 9) { spriteNumber9[4]->Draw(); }
		}
		if (100000 <= enemy->GetScore())
		{
			if (score4 == 0) { spriteNumber0[5]->Draw(); }
			if (score4 == 1) { spriteNumber1[5]->Draw(); }
			if (score4 == 2) { spriteNumber2[5]->Draw(); }
			if (score4 == 3) { spriteNumber3[5]->Draw(); }
			if (score4 == 4) { spriteNumber4[5]->Draw(); }
			if (score4 == 5) { spriteNumber5[5]->Draw(); }
			if (score4 == 6) { spriteNumber6[5]->Draw(); }
			if (score4 == 7) { spriteNumber7[5]->Draw(); }
			if (score4 == 8) { spriteNumber8[5]->Draw(); }
			if (score4 == 9) { spriteNumber9[5]->Draw(); }
		}


		if (0 <= player->GetPlayCount() && 600 >= player->GetPlayCount())
		{
			if (time1 == 0) { spriteNumber0[6]->Draw(); }
			if (time1 == 1) { spriteNumber1[6]->Draw(); }
			if (time1 == 2) { spriteNumber2[6]->Draw(); }
			if (time1 == 3) { spriteNumber3[6]->Draw(); }
			if (time1 == 4) { spriteNumber4[6]->Draw(); }
			if (time1 == 5) { spriteNumber5[6]->Draw(); }
			if (time1 == 6) { spriteNumber6[6]->Draw(); }
			if (time1 == 7) { spriteNumber7[6]->Draw(); }
			if (time1 == 8) { spriteNumber8[6]->Draw(); }
			if (time1 == 9) { spriteNumber9[6]->Draw(); }
		}
		if (600 <= player->GetPlayCount())
		{
			if (time1 - 10 * time2 == 0) { spriteNumber0[6]->Draw(); }
			if (time1 - 10 * time2 == 1) { spriteNumber1[6]->Draw(); }
			if (time1 - 10 * time2 == 2) { spriteNumber2[6]->Draw(); }
			if (time1 - 10 * time2 == 3) { spriteNumber3[6]->Draw(); }
			if (time1 - 10 * time2 == 4) { spriteNumber4[6]->Draw(); }
			if (time1 - 10 * time2 == 5) { spriteNumber5[6]->Draw(); }
			if (time1 - 10 * time2 == 6) { spriteNumber6[6]->Draw(); }
			if (time1 - 10 * time2 == 7) { spriteNumber7[6]->Draw(); }
			if (time1 - 10 * time2 == 8) { spriteNumber8[6]->Draw(); }
			if (time1 - 10 * time2 == 9) { spriteNumber9[6]->Draw(); }
		}
		if (600 <= player->GetPlayCount())
		{
			if (time2 - 10 * time3 == 0) { spriteNumber0[7]->Draw(); }
			if (time2 - 10 * time3 == 1) { spriteNumber1[7]->Draw(); }
			if (time2 - 10 * time3 == 2) { spriteNumber2[7]->Draw(); }
			if (time2 - 10 * time3 == 3) { spriteNumber3[7]->Draw(); }
			if (time2 - 10 * time3 == 4) { spriteNumber4[7]->Draw(); }
			if (time2 - 10 * time3 == 5) { spriteNumber5[7]->Draw(); }
			if (time2 - 10 * time3 == 6) { spriteNumber6[7]->Draw(); }
			if (time2 - 10 * time3 == 7) { spriteNumber7[7]->Draw(); }
			if (time2 - 10 * time3 == 8) { spriteNumber8[7]->Draw(); }
			if (time2 - 10 * time3 == 9) { spriteNumber9[7]->Draw(); }
		}
		if (6000 <= player->GetPlayCount())
		{
			if (time3 == 0) { spriteNumber0[8]->Draw(); }
			if (time3 == 1) { spriteNumber1[8]->Draw(); }
			if (time3 == 2) { spriteNumber2[8]->Draw(); }
			if (time3 == 3) { spriteNumber3[8]->Draw(); }
			if (time3 == 4) { spriteNumber4[8]->Draw(); }
			if (time3 == 5) { spriteNumber5[8]->Draw(); }
			if (time3 == 6) { spriteNumber6[8]->Draw(); }
			if (time3 == 7) { spriteNumber7[8]->Draw(); }
			if (time3 == 8) { spriteNumber8[8]->Draw(); }
			if (time3 == 9) { spriteNumber9[8]->Draw(); }
		}

		spritePlayTime->Draw();
		spritePlayScore->Draw();
		if (bomSceneChange2 == true)
		{
			spriteBom2->Draw();
		}
		if (bomSceneChange == true)
		{
			spriteBom->Draw();
		}

		if (startCount < 180 && startCount > 120)
		{
			spriteNumber1[0]->Draw();
		}
		else if (startCount < 120 && startCount > 60)
		{
			spriteNumber2[0]->Draw();
		}
		else if (startCount < 60 && startCount > 0)
		{
			spriteNumber3[0]->Draw();
		}

		if(endCountFlag==true)
		{
			if (player->GetPlayCount() / 60 == 3)
			{
				spriteNumber3[0]->Draw();
			}
			else if (player->GetPlayCount() / 60 == 2)
			{
				spriteNumber2[0]->Draw();
			}
			else if (player->GetPlayCount() / 60 == 1)
			{
				spriteNumber1[0]->Draw();
	
			}
		}
		if (scorePluse == 1)
		{
			spriteScorePluse->Draw();
		}
	}
	if (scene == CLEAR)
	{
		
		spriteTitleScroll1->Draw();
		spriteTitleScroll2->Draw();
		spriteTitleScroll3->Draw();
		spriteTitleScroll4->Draw();
		spriteClearScore->Draw();

		if (restart == 0)
		{
			spriteClearTextR1->Draw();
			spriteClearTextL2->Draw();
		}
		//debugText.Print(20, 60, 2.0f, "epos :  %d %d %d", enemy->GetScore() / 10000, enemy->GetScore() / 1000, enemy->GetScore() / 100);
		spriteNumber0s->Draw();
		if (enemy->GetScore() != 0)
		{
			spriteNumber0[0]->Draw();
			spriteNumber0[1]->Draw();
		}
		if (100 <= enemy->GetScore())
		{
			if (score1 - 10 * score2 == 0) { spriteNumber0[2]->Draw(); }
			if (score1 - 10 * score2 == 1) { spriteNumber1[2]->Draw(); }
			if (score1 - 10 * score2 == 2) { spriteNumber2[2]->Draw(); }
			if (score1 - 10 * score2 == 3) { spriteNumber3[2]->Draw(); }
			if (score1 - 10 * score2 == 4) { spriteNumber4[2]->Draw(); }
			if (score1 - 10 * score2 == 5) { spriteNumber5[2]->Draw(); }
			if (score1 - 10 * score2 == 6) { spriteNumber6[2]->Draw(); }
			if (score1 - 10 * score2 == 7) { spriteNumber7[2]->Draw(); }
			if (score1 - 10 * score2 == 8) { spriteNumber8[2]->Draw(); }
			if (score1 - 10 * score2 == 9) { spriteNumber9[2]->Draw(); }
		}
		if (1000 <= enemy->GetScore())
		{
			if (score2 - 10 * score3 == 0) { spriteNumber0[3]->Draw(); }
			if (score2 - 10 * score3 == 1) { spriteNumber1[3]->Draw(); }
			if (score2 - 10 * score3 == 2) { spriteNumber2[3]->Draw(); }
			if (score2 - 10 * score3 == 3) { spriteNumber3[3]->Draw(); }
			if (score2 - 10 * score3 == 4) { spriteNumber4[3]->Draw(); }
			if (score2 - 10 * score3 == 5) { spriteNumber5[3]->Draw(); }
			if (score2 - 10 * score3 == 6) { spriteNumber6[3]->Draw(); }
			if (score2 - 10 * score3 == 7) { spriteNumber7[3]->Draw(); }
			if (score2 - 10 * score3 == 8) { spriteNumber8[3]->Draw(); }
			if (score2 - 10 * score3 == 9) { spriteNumber9[3]->Draw(); }
		}
		if (10000 <= enemy->GetScore())
		{
			if (score3 - 10 * score4 == 0) { spriteNumber0[4]->Draw(); }
			if (score3 - 10 * score4 == 1) { spriteNumber1[4]->Draw(); }
			if (score3 - 10 * score4 == 2) { spriteNumber2[4]->Draw(); }
			if (score3 - 10 * score4 == 3) { spriteNumber3[4]->Draw(); }
			if (score3 - 10 * score4 == 4) { spriteNumber4[4]->Draw(); }
			if (score3 - 10 * score4 == 5) { spriteNumber5[4]->Draw(); }
			if (score3 - 10 * score4 == 6) { spriteNumber6[4]->Draw(); }
			if (score3 - 10 * score4 == 7) { spriteNumber7[4]->Draw(); }
			if (score3 - 10 * score4 == 8) { spriteNumber8[4]->Draw(); }
			if (score3 - 10 * score4 == 9) { spriteNumber9[4]->Draw(); }
		}
		if (100000 <= enemy->GetScore())
		{
			if (score4 == 0) { spriteNumber0[5]->Draw(); }
			if (score4 == 1) { spriteNumber1[5]->Draw(); }
			if (score4 == 2) { spriteNumber2[5]->Draw(); }
			if (score4 == 3) { spriteNumber3[5]->Draw(); }
			if (score4 == 4) { spriteNumber4[5]->Draw(); }
			if (score4 == 5) { spriteNumber5[5]->Draw(); }
			if (score4 == 6) { spriteNumber6[5]->Draw(); }
			if (score4 == 7) { spriteNumber7[5]->Draw(); }
			if (score4 == 8) { spriteNumber8[5]->Draw(); }
			if (score4 == 9) { spriteNumber9[5]->Draw(); }
		}
		if (restart == 1)
		{
			spriteClearTextR2->Draw();
			spriteClearTextL1->Draw();
		}
		if (bomSceneChange3 == true)
		{
			spriteBom->Draw();
		}

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
