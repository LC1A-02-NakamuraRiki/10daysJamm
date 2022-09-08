#include "../Scene/GameScene.h"
#include "../collision/Collision.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include "../3d/FbxLoader.h"
#include "../3d/FbxObject3d.h"
#include "../input/Input.h"

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(spriteTitle);
	safe_delete(spriteClear);
	safe_delete(spriteGAMEOVER);
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

void GameScene::Initialize(DirectXCommon *dxCommon, Sound *audio)
{
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;

	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera);

	// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// �f�o�b�O�e�L�X�g������
	debugText.Initialize(debugTextTexNumber);

	particle3d = ParticleManager::Create(dxCommon->GetDevice(), camera);
	
	//�X�v���C�g
	// �e�N�X�`���ǂݍ���
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
	//// �w�i�X�v���C�g����
	spriteTitle = Sprite::Create(18, { 0.0f,0.0f });
	spriteClear = Sprite::Create(19, { 0.0f,0.0f });
	spriteGAMEOVER = Sprite::Create(20, { 0.0f,0.0f });

	// 3D�I�u�W�F�N�g����
	modelSkydome = Model::CreateFromObject("skydome", false);
	objSkydome = Object3d::Create(modelSkydome);
	objSkydome->SetScale({5.0f,5.0f,5.0f});
	modelGround = Model::CreateFromObject("ground", true);
	objGround = Object3d::Create(modelGround);
	objGround->SetScale({ 5.0f,2.0f ,5.0f });

	// �f�o�C�X���Z�b�g
	FbxObject3d::SetDevice(dxCommon->GetDevice());
	// �J�������Z�b�g
	FbxObject3d::SetCamera(camera);
	// �O���t�B�b�N�X�p�C�v���C������
	FbxObject3d::CreateGraphicsPipeline();
	light = LightGroop::Create();
	
	Object3d::SetLightGroup(light);

	map = new MapChip;
	map->Initialize();
	player = new Player;
	player->Initialize(map);
	enemy = new Enemy;
	enemy->Initialize(7, 0, 1, 0 );
	enemy->Initialize(7, 1, 1, 1 );
	enemy->Initialize(7, 2, 1, 2 );
	enemy->Initialize(7, 3, 1, 3 );
	enemy->Initialize(7, 4, 1, 4 );
	enemy->Initialize(7, 5, 1, 5 );
	enemy->Initialize(7, 6, 1, 6 );
	enemy->Initialize(7, 7, 1, 7 );
	enemy->Initialize(0, 0, 0, 8 );
	enemy->Initialize(1, 0, 0, 9 );
	enemy->Initialize(2, 0, 0, 10);
	enemy->Initialize(3, 0, 0, 11);
	player->SetParticle(particle3d);
}

void GameScene::Update()
{
	debugText.Print(20, 20, 2.0f, "END : ESC");
	if (scene == TITLE)
	{
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE))
		{
			map->InitializeValue();
			player->InitializeValue();
			enemy->EndInitialize();
			scene = PLAY;
		}
	}
	else if (scene == PLAY)
	{
		if (player->GetPlayCount() / 60 < 0)
		{
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

		//���C�g
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
			map->InitializeValue();
			player->InitializeValue();
			enemy->EndInitialize();
			scene = PLAY;
		}
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE))
		{
			scene = TITLE;
		}
	}
}

void GameScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList *cmdList = dxCommon->GetCommandList();

#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	// �w�i�X�v���C�g�`��
	//-------------------------------------------------------------//

	//-------------------------------------------------------------//
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
	// �[�x�o�b�t�@�N���A
	dxCommon->ClearDepthBuffer();
#pragma endregion
	
#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�W�F�N�g�`��O����
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
	// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

	particle3d->Draw(cmdList);
#pragma endregion

	
#pragma region �O�i�X�v���C�g�`��
	//// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	//-------------------------------------------------------------//
	
	if (scene == TITLE)
	{
		spriteTitle->Draw();
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
	// �f�o�b�O�e�L�X�g�̕`��
	debugText.DrawAll(cmdList);
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion
}

void GameScene::ParticlesCreate(XMFLOAT3 Pos)
{
	for (int i = 0; i < 1; i++)
	{
		//X,Y,Z�S��{-5.0f,+5.0f}�Ń����_���ɕ��z
		const float md_pos = 0.5f;
		XMFLOAT3 pos = Pos;
		pos.x += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.y += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.z += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		////X,Y,Z�S��{-0.05f,+0.05f}�Ń����_���ɕ��z
		const float md_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		//�d�͂Ɍ����Ă�Y�̂�{-0.001f,0}�Ń����_�����z
		XMFLOAT3 acc{};
		const float md_acc = 0.001f;
		acc.y = (float)rand() / RAND_MAX * md_acc;

		int time = 60;
		float s_scale = 1.0f;
		float e_scale = 1.0f;
		XMFLOAT4 color = { 1,1,1,1 };
		// �ǉ�
		particle3d->Add(time, pos, vel, acc, s_scale, e_scale, color);
	}
}
