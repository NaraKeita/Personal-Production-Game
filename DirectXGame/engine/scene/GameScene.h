#pragma once

#include "../2d/DisplayNumbar.h"
#include "../2d/RankManager.h"
#include "../3d/Apple.h"
#include "../3d/Ground.h"
#include "../3d/Player.h"
#include "../3d/PoisonApple.h"
#include "../3d/Skydome.h"
#include "../3d/Tree.h"
#include "KamataEngine.h"
#include "../scene/GameObject.h"

class GameScene {
public:
	// SpringScene();
	~GameScene();

	void Initialize();
	void Update();
	void Draw();

	// 終わりフラグのgetter
	bool IsFinished() const { return isFinished_; }

private:
	int score_ = 0;           // スコア
	uint32_t seAppleGet_ = 0; // 効果音
	int totalScore_ = 0;
	std::vector<Apple*> apples_;

	float timeLimit_ = 30.0f; // 制限時間（秒）
	bool finished_ = false;   // 終了フラグ

	float startCountdown_ = 3.0f; // ゲーム開始前のカウントダウン（秒）
	bool isStarted_ = false;      // ゲーム開始フラグ
	bool isPaused_ = false;       // 一時停止フラグ
	bool showStartText_ = false;  // スタート表示フラグ
	int showStartTextFrame_ = 0;  // スタート表示フレーム数

	bool isActive_ = true;
	void SetActive(bool active) { isActive_ = active; }

	int lastAppleScore_ = 0;  // 最後に取ったリンゴのスコア

	bool isEnd_ = false;      // 終了演出中か
	float endTimer_ = 0.0f;   // 終了演出用タイマー
	bool isFinished_ = false; // シーン遷移用

private:
	WorldTransform worldTransform_;
	Camera* camera_ = nullptr;

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
	DisplayNumbar* displayNumbar_ = nullptr;   // 時間やスコアに必要
	DisplayNumbar* countdownNumbar_ = nullptr; // カウントダウン用
	DisplayNumbar* scoreNumbar_ = nullptr;     // スコア表示用
	DisplayNumbar* timeNumbar_ = nullptr;      // 残り時間表示用

	RankManager* rankManager_ = nullptr; // ランキング管理

	// 共通インターフェースで扱うゲームオブジェクトリスト（非所有）
	std::vector<GameObject*> gameObjects_;

	// サウドデータハンドル
	uint32_t bgmHandle_ = 0; // BGM
	// 音声再生ハンドル
	uint32_t voiceHandle_ = 0;  

	// スタート表示
	Sprite* spriteStart_ = nullptr;
	uint32_t startHandle_ = 0;

	// 3秒のカウントダウン
	uint32_t countdownHandles_[4];
	Sprite* countdownSprites_[4];

	// タイトルのリソース表示
	Sprite* title_ = nullptr;

	// ESCのリソース
	Sprite* esc_ = nullptr;
	uint32_t escHandles_ = 0;

	// 一時停止のリソース表示
	Sprite* pause_ = nullptr;
	uint32_t pauseHandles_ = 0;

	// 30秒経ったら終了が出る
	Sprite* endSprite_ = nullptr;
	uint32_t endHandles_ = 0;

	int countIndex = 0;
};
