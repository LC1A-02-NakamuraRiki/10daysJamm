#pragma once

class Enemy
{
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �ړ�
	/// </summary>
	void Move();

	/// <summary>
	/// �ǂɓ�����
	/// </summary>
	void HitWall();

	/// <summary>
	/// ����J�E���g����
	/// </summary>
	void CountUp();

	/// <summary>
	/// ���ł�����
	/// </summary>
	void Vanish();

private:
	// �ړ��̃p�^�[��
	int movePatern = 2;
	// �ړ���
	int move = 1;
	// ����J�E���g
	int count = 2;
	// �X�R�A
	int score = 1000;
	// �^�C���{�[�i�X
	float timeBonus = 10.0 * 60;
	// �����t���O
	bool alive = false;
};