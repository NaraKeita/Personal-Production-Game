#include "SpringScene.h"
#include "Collision.h"
#include <KamataEngine.h>

using namespace KamataEngine;

SpringScene::~SpringScene() {
	// 自キャラの開放
	delete player_;
	delete skydome_;
	delete ground_;
	delete tree_;
	delete apple_;
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
	displayNumbar_ = new DisplayNumbar();

	// 初期化
	camera_->Initialize();
	worldTransform_.Initialize();
	player_->Initialize(camera_);
	skydome_->Initialize(camera_);
	ground_->Initialize(camera_);
	tree_->Initialize(camera_);
	apple_->Initialize(camera_);
	apple_->SetPlayer(player_);
	displayNumbar_->Initialize();

	// 軸方向
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetCamera(camera_);

}

void SpringScene::Update() { 
	player_->Update(); 
	skydome_->Update();
	ground_->Update();
	tree_->Update();
	apple_->Update();
	displayNumbar_->Update();

	//// 追加: 当たり判定と処理
	//if (apple_->IsActive() && CheckCollision(player_->GetPosition(), player_->GetRadius(), apple_->GetPosition(), apple_->GetRadius())) {
	//	apple_->SetActive(false); // リンゴを消す
	//	score_ += 10; // スコア加算（例: 10点）
	//	// 効果音再生
	//	audio_->PlayWave(seAppleGet_);   
	//}
}

void SpringScene::Draw() {  
    // DirectXCommonのインスタンスを取得  
    DirectXCommon* dxCommon = DirectXCommon::GetInstance();  

	Sprite::PreDraw(dxCommon->GetCommandList());

	displayNumbar_->Draw();

	Sprite::PostDraw();

	//dxCommon->ClearDepthBuffer();  

    // 3Dモデル描画前処理
	Model::PreDraw();

    player_->Draw();  
	skydome_->Draw();
	ground_->Draw();
	tree_->Draw();
	apple_->Draw();

    // 3Dモデル描画後処理  
    Model::PostDraw();  
}


