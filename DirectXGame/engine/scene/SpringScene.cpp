#include "SpringScene.h"
#include "../calculation/Collision.h"
#include <KamataEngine.h>
#include <cmath>

using namespace KamataEngine;

SpringScene::~SpringScene() {
	// 自キャラの開放
	delete player_;
	delete skydome_;
	delete ground_;
	delete tree_;
	delete apple_;
	delete poisonApple_;
	delete displayNumbar_;

}

void SpringScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 生成
	camera_ = new Camera();
	player_ = new Player();
	skydome_ = new Skydome();
	ground_ = new Ground();
	tree_ = new Tree();
	apple_ = new Apple();
	poisonApple_ = new PoisonApple();
	displayNumbar_ = new DisplayNumbar();
	scoreNumbar_ = new DisplayNumbar();
	timeNumbar_ = new DisplayNumbar();

	// スコア設定
	apple_->score_ = 0;
	
	// 初期化
	camera_->Initialize();
	worldTransform_.Initialize();
	player_->Initialize(camera_);
	skydome_->Initialize(camera_);
	ground_->Initialize(camera_);
	tree_->Initialize(camera_);
	// リンゴを複数出すために必要
	for (int i = 0; i < 3; ++i) {
		Apple* apple = new Apple();
		apple->Initialize(camera_);
		apple->SetPlayer(player_);
		// スコア加算コールバック
		apple->SetOnGetApple([this](int /*score*/) { ++totalScore_; });
		apples_.push_back(apple);
	}
	poisonApple_->Initialize(camera_);
	poisonApple_->SetPlayer(player_);
	displayNumbar_->Initialize();
	scoreNumbar_->Initialize();
	timeNumbar_->Initialize();

	countdownHandles_[0] = TextureManager::Load("NumberSystem/start/count3.png"); // 3秒
	countdownHandles_[1] = TextureManager::Load("NumberSystem/start/count2.png"); // 2秒
	countdownHandles_[2] = TextureManager::Load("NumberSystem/start/count1.png"); // 1秒
	countdownHandles_[3] = TextureManager::Load("NumberSystem/start/start.png");  // START!

	endHandles_ = TextureManager::Load("spriteEnd.png");
	endSprite_ = Sprite::Create(endHandles_, {570.0f, 100.0f});

	bgmHandle_ = audio_->LoadWave("bgm/fruitsparfait.mp3");
	voiceHandle_ = audio_->PlayWave(bgmHandle_, true, 0.3f); // ループ再生

	// 始まる前のカウント
	for (int i = 0; i < 4; i++) {
		countdownSprites_[i] = Sprite::Create(countdownHandles_[i], {600.0f, 200.0f});
	}

	// スコア表示位置（左寄りに置いている）
	for (int i = 0; i < 5; i++) {
		scoreNumbar_->sprite_[i]->SetPosition({295.5f + 32.0f * i, 5.0f});
	}

	// 残り時間表示位置（真ん中に置いている）
	for (int i = 0; i < 2; i++) {
		timeNumbar_->sprite_[i]->SetPosition({600.0f + 32.0f * i, 5.0f});
	}

	apple_->SetOnGetApple([this](int score) { lastAppleScore_ = score; });

	// 軸方向
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetCamera(camera_);

}

void SpringScene::Update() { 
	if (!isActive_) return;
	// ゲーム開始前のカウントダウン （ 3秒 ）
	if (!isStarted_) {
		startCountdown_ -= 1.0f / 60.0f;
		if (startCountdown_ <= 0.0f) {
			isStarted_ = true;
			startCountdown_ = 0.0f;
		}
		
		return;
	}

	// 終了演出中
	if (isEnd_) {
		endTimer_ += 1.0f / 60.0f;
		if (endTimer_ >= 5.0f) {
			isFinished_ = true; // 3秒経過でタイトルに戻す
			audio_->StopWave(voiceHandle_);
		}
		return;
	}

	player_->Update();                                                      // プレイヤー
	skydome_->Update();                                                     // 背景（横に回転している）
	tree_->Update();                                                        // 木（揺れている）
	for (auto& apple : apples_) {
		apple->Update();                                                    // 普通のリンゴ（スコアが加算される）
	} 
	poisonApple_->Update();                                                 // デバフリンゴ
	displayNumbar_->Update();                                               // ↓スコアや時間を動かすのに必要
	scoreNumbar_->SetNumber(totalScore_);                                   // スコア
	timeNumbar_->SetTimerNumber(static_cast<int>(std::ceil(timeLimit_)));   // 時間制限

	// 1フレームあたりの経過時間
	timeLimit_ -= 1.0f / 60.0f; //（30秒）

	// 0秒になったらプレイヤーとリンゴの動きが止まる
	if (timeLimit_ <= 0.0f) {
		timeLimit_ = 0.0f;
		Player* mutablePlayer = const_cast<Player*>(player_);
		mutablePlayer->SetSpeed(0.0f); 
		apple_->SetActive(false);
		poisonApple_->SetActive(false);

		// 終了演出開始
		isEnd_ = true;
		endTimer_ = 0.0f;
	}
	
	displayNumbar_->SetNumber(totalScore_);
}

void SpringScene::Draw() {  
    // DirectXCommonのインスタンスを取得  
    DirectXCommon* dxCommon = DirectXCommon::GetInstance();  

	//dxCommon->ClearDepthBuffer();  

    // 3Dモデル描画前処理
	Model::PreDraw();

    player_->Draw();                 // プレイヤー
	skydome_->Draw();                // 背景
	ground_->Draw();                 // 地面
	tree_->Draw();                   // リンゴの木
	for (auto& apple : apples_) {
		apple->Draw();               // リンゴ
	} 
	poisonApple_->Draw();            // デバフリンゴ

    // 3Dモデル描画後処理  
    Model::PostDraw();  

	Sprite::PreDraw(dxCommon->GetCommandList());

	if (!isStarted_) {
		int countIndex = 0;
		if (startCountdown_ > 2.0f) {
			countIndex = 0; // 3
		} else if (startCountdown_ > 1.0f) {
			countIndex = 1; // 2
		} else if (startCountdown_ > 0.0f) {
			countIndex = 2; // 1
		} else {
			countIndex = 3; // START!
		}
		countdownSprites_[countIndex]->Draw();
	} else {
		scoreNumbar_->Draw();
		timeNumbar_->Draw();
		if (timeLimit_ <= 0.0f && endSprite_) {
			endSprite_->Draw();                           // 終了の文字
			
		}
	}

	Sprite::PostDraw();
}


