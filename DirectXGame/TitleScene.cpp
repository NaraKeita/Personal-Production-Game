#include "TitleScene.h"

TitleScene::TitleScene() {}
TitleScene::~TitleScene() { delete sprite_; }

void TitleScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	// ビュープロジェクション
	camera_.Initialize();
	//textureHandle_ = TextureManager::Load("title.resource.png");
	//model_ = Model::CreateFromOBJ("titleTuree");
	//textureHandle_ = TextureManager::Load("title.png");
	sprite_ = Sprite::Create(textureHandle_, {0, 0});
	sprite_->SetSize({1280.0f, 720.0f});
}

void TitleScene::Update() {
	audio_->StopWave(voiceHandle_);
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		finished_ = true;
	}
}

void TitleScene::Draw() {
	Model::PreDraw();
	//model_->Draw(worldTransform_, camera_);
	Model::PostDraw();
	/*Sprite::PreDraw();
	if (sprite_) {
		sprite_->Draw();
	}
	Sprite::PostDraw();*/
}
