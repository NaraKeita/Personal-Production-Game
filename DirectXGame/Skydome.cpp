#include "Skydome.h"

void Skydome::Initialize(Model* model, const Vector3& position) {
	// NULLポインタをチェックする
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	worldTransform_.translation_ = position;
	
	// ワールド変換の初期化
	worldTransform_.Initialize();
}

void Skydome::Update() {
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void Skydome::Draw(Camera& camera) { model_->Draw(worldTransform_, camera); }
