#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include "../scene/GameObject.h"
#include <functional>

using namespace KamataEngine;

class FallingObject : public GameObject {
public:
	virtual ~FallingObject() = default;

	// 共通初期化。modelName は Model::CreateFromOBJ の引数、sePath は効果音パス（LoadWave 用）。
	void InitializeBase(const std::string& modelName, const std::string& sePath, Camera* camera);

	// 派生が当たり時の挙動を実装する
	virtual void OnHitPlayer() {}

	// Reset は派生で上書き可能
	virtual void ResetPosition();

	virtual void Update() override;
	virtual void Draw() override;

	void SetPlayer(Player* player) { player_ = player; }
	void SetActive(bool active) { isActive_ = active; }

	const Vector3& GetPosition() const { return worldTransform_.translation_; }
	float GetRadius() const { return radius_; }
	bool IsActive() const { return isActive_; }

protected:
	Audio* audio_ = nullptr;
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	Camera* camera_ = nullptr;
	bool isActive_ = true;
	bool isHitPlayer_ = false;
	Player* player_ = nullptr;
	uint32_t seHandle_ = 0;

	float fallSpeed_ = 0.1f;
	float radius_ = 1.0f;
};
