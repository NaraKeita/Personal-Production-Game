#pragma once
#include <KamataEngine.h>

class TitleScene {
public:
	
	TitleScene();
	~TitleScene();

	void Initialize();

	void Update();

	void Draw();

	// デスフラグのgetter
	bool IsFinished() const { return finished_; }

private:
	// 終了フラグ
	bool finished_ = false;
	// spaceを押した後の時間
	float spacePressTime_ = 0.0f;
	bool isTransition_ = false;

	// ビュープロジェクション
	KamataEngine::Camera camera_;

	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	
	KamataEngine::Sprite* sprite_ = nullptr;
	uint32_t textureHandle_ = 0;

	KamataEngine::Sprite* spriteBite_ = nullptr;
	uint32_t textureBite_ = 0;

	// サウドデータハンドル
	uint32_t bgmApple_ = 0;          // リンゴをかじる音
	uint32_t bgmHandle_ = 0;         // BGM
	// 音声再生ハンドル
	uint32_t voiceHandle_ = 0;  
	   
};
