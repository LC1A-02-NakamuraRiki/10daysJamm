#pragma once

class Enemy
{
	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

	/// <summary>
	/// 壁に当たる
	/// </summary>
	void HitWall();

	/// <summary>
	/// 頭上カウント増加
	/// </summary>
	void CountUp();

	/// <summary>
	/// 消滅させる
	/// </summary>
	void Vanish();

private:
	// 移動のパターン
	int movePatern = 2;
	// 移動量
	int move = 1;
	// 頭上カウント
	int count = 2;
	// スコア
	int score = 1000;
	// タイムボーナス
	float timeBonus = 10.0 * 60;
	// 生存フラグ
	bool alive = false;
};