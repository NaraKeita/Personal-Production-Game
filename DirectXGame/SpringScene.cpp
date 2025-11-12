#include "SpringScene.h"
#include "Collision.h"
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
	apple_->Initialize(camera_);
	apple_->SetPlayer(player_);
	poisonApple_->Initialize(camera_);
	poisonApple_->SetPlayer(player_);
	displayNumbar_->Initialize();
	scoreNumbar_->Initialize();
	timeNumbar_->Initialize();

	countdownHandles_[0] = TextureManager::Load("NumberSystem/start/count3.png"); // 3秒
	countdownHandles_[1] = TextureManager::Load("NumberSystem/start/count2.png"); // 2秒
	countdownHandles_[2] = TextureManager::Load("NumberSystem/start/count1.png"); // 1秒
	countdownHandles_[3] = TextureManager::Load("NumberSystem/start/start.png");  // START!

	// 始まる前のカウント
	for (int i = 0; i < 4; i++) {
		countdownSprites_[i] = Sprite::Create(countdownHandles_[i], {600.0f, 200.0f});
	}

	// スコア表示位置（左上に置いている）
	for (int i = 0; i < 5; i++) {
		scoreNumbar_->sprite_[i]->SetPosition({100.0f + 32.0f * i, 5.0f});
	}

	// 残り時間表示位置（真ん中に置いている）
	for (int i = 0; i < 2; i++) {
		timeNumbar_->sprite_[i]->SetPosition({600.0f + 32.0f * i, 5.0f});
	}

	// 軸方向
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetCamera(camera_);

}

void SpringScene::Update() { 
	// ゲーム開始前のカウントダウン （ 3秒 ）
	if (!isStarted_) {
		startCountdown_ -= 1.0f / 60.0f;
		if (startCountdown_ <= 0.0f) {
			isStarted_ = true;
			startCountdown_ = 0.0f;
		}
		
		return;
	}

	player_->Update(); 
	skydome_->Update();
	tree_->Update();
	apple_->Update();
	poisonApple_->Update();
	displayNumbar_->Update();
	scoreNumbar_->SetNumber(apple_->score_);                                // スコア
	timeNumbar_->SetTimerNumber(static_cast<int>(std::ceil(timeLimit_)));   // 時間制限

	// 1フレームあたりの経過時間
	timeLimit_ -= 1.0f / 60.0f; //（30秒）

	if (timeLimit_ <= 0.0f) {
		timeLimit_ = 0.0f;
		finished_ = true;
	}

	displayNumbar_->SetNumber(apple_->score_);

	
}

void SpringScene::Draw() {  
    // DirectXCommonのインスタンスを取得  
    DirectXCommon* dxCommon = DirectXCommon::GetInstance();  

	//dxCommon->ClearDepthBuffer();  

    // 3Dモデル描画前処理
	Model::PreDraw();

    player_->Draw();  
	skydome_->Draw();
	ground_->Draw();
	tree_->Draw();
	apple_->Draw();
	poisonApple_->Draw();

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
	}

	Sprite::PostDraw();
}


