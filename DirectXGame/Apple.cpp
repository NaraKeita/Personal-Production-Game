#include "Apple.h"

#include <cassert>

void Apple::Initialize(Model* model, const Vector3& position) {
	// NULLポインタをチェックする
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	worldTransform_.translation_ = position;
	worldTransform_.Initialize();

}

void Apple::Update() {
	
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void Apple::Draw(Camera& camera) { model_->Draw(worldTransform_, camera); }
