#include "SpringScene.h"
#include <cassert>
#include <math.h>
#include <KamataEngine.h>

using namespace KamataEngine;

SpringScene::~SpringScene() {
	// 自キャラの開放
	delete player_;
	delete skydome_;
	delete ground_;

	delete modelPlayer_;
	delete modelSkydome_;
	delete modelGround_;
}

void SpringScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	camera_.Initialize();

	// モデル
	modelPlayer_ = Model::CreateFromOBJ("player"); // プレイヤー
	modelSkydome_ = Model::CreateFromOBJ("skydome"); // 天球
	modelGround_ = Model::CreateFromOBJ("ground"); // 地面

	// ワールドトランスフォーム
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// 自キャラの生成
	player_ = new Player();
	// プレイヤーの位置
	Vector3 startPlayerPos = {0.0f, -2.0f, -20.0f};
	// 自キャラの初期化
	player_->Initialize(modelPlayer_, startPlayerPos);

	// 天球の生成
	skydome_ = new Skydome();
	// 天球の初期化
	skydome_->Initialize(modelSkydome_,worldTransform_.translation_);

	// 地面の生成
	ground_ = new Ground();
	// 地面の位置
	Vector3 startGroundPos = {0.0f, -5.0f, -20.0f};
	// 地面の初期化
	ground_->Initialize(modelGround_, startGroundPos);

	// 軸方向
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetCamera(&viewProjection_);

}

void SpringScene::Update() { 
	player_->Update(); 
}

void SpringScene::Draw() {  
    // DirectXCommonのインスタンスを取得  
    DirectXCommon* dxCommon = DirectXCommon::GetInstance();  
	dxCommon->ClearDepthBuffer();

    // 3Dモデル描画前処理
	Model::PreDraw();

    player_->Draw(camera_);  
	skydome_->Draw(camera_);
	ground_->Draw(camera_);

    // 3Dモデル描画後処理  
    Model::PostDraw();  
}

