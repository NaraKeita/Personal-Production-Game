#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include "Skydome.h"
#include "Ground.h"
#include "Tree.h"
#include "Apple.h"
#include "PoisonApple.h"
#include "DisplayNumbar.h"

using namespace KamataEngine;

class SpringScene {
public:
	//SpringScene();
	~SpringScene();

	void Initialize();
	void Update();
	void Draw();
	std::vector<Apple*> apples_;

	// デスフラグのgetter
	bool IsFinished() const { return finished_; }

private:
	int score_ = 0;           // スコア
	uint32_t seAppleGet_ = 0; // 効果音

	float timeLimit_ = 30.0f; // 制限時間（秒）
	bool finished_ = false;   // 終了フラグ

    float startCountdown_ = 3.0f; // ゲーム開始前のカウントダウン（秒）
	bool isStarted_ = false;      // ゲーム開始フラグ
	bool showStartText_ = false;  // スタート表示フラグ
	int showStartTextFrame_ = 0;  // スタート表示フレーム数

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	// 自キャラ
	Player* player_ = nullptr;
	// 天球
	Skydome* skydome_ = nullptr;
	// 地面
	Ground* ground_ = nullptr;
	// 木
	Tree* tree_ = nullptr;
	// リンゴ
	Apple* apple_ = nullptr;
	// 毒リンゴ
	PoisonApple* poisonApple_ = nullptr;
	// 数字の表示
	DisplayNumbar* displayNumbar_ = nullptr; 
	DisplayNumbar* countdownNumbar_ = nullptr; // カウントダウン用
	
	DisplayNumbar* scoreNumbar_ = nullptr; // スコア表示用
	DisplayNumbar* timeNumbar_ = nullptr;  // 残り時間表示用

	WorldTransform worldTransform_;
	
	Camera* camera_ = nullptr;

	Sprite* spriteStart_ = nullptr;
	uint32_t startHandle_ = 0;

};
