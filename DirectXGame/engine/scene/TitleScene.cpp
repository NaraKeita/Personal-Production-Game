#include "TitleScene.h"
using namespace KamataEngine;

TitleScene::TitleScene() {}
TitleScene::~TitleScene() { 
	delete sprite_;
}

void TitleScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	// ビュープロジェクション
	camera_.Initialize();

	textureHandle_ = TextureManager::Load("title/titleResource1.png");
	textureBite_ = TextureManager::Load("title/titleResource2.png");

	sprite_ = Sprite::Create(textureHandle_, {0, 0});
	spriteBite_ = Sprite::Create(textureBite_, {0, 0});
	
	// BGMのロード（Appleと同じようにメンバ変数へ保存）
	bgmApple_ = audio_->LoadWave("bgm/appleBite.mp3"); // ファイル名は適宜
	bgmHandle_ = audio_->LoadWave("bgm/yuruyakanaasayake.mp3");    // ファイル名・パスは適宜
	voiceHandle_ = audio_->PlayWave(bgmHandle_, true, 1.0f); // ループ再生
}

void TitleScene::Update() {
	
	// スペースキーを押した瞬間にタイマー開始
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		spacePressTime_ = 0.0f;
		isTransition_ = true; // タイマー開始
		// BGM再生（ループしない）
		audio_->PlayWave(bgmApple_, false, 1.0f);
	}

	// タイマーが動いている間、時間を加算
	if (isTransition_) {
		spacePressTime_ += 1.0f / 60.0f; // 60FPS想定
		if (spacePressTime_ >= 2.0f) {
			finished_ = true;      // 3秒後に遷移
			isTransition_ = false; // タイマー停止
			audio_->StopWave(voiceHandle_);
		}
	}
	
}

void TitleScene::Draw() {
	Sprite::PreDraw();

	// スペースキー押下後はspriteBite_を描画
	if (isTransition_ && spriteBite_) {
		spriteBite_->Draw();
	} else if (sprite_) {
		sprite_->Draw();
	}

	Sprite::PostDraw();
}
