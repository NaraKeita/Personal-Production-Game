#pragma once
#include "kamataEngine.h"

#include <iostream>
#include <map>
#include <string>

class SpriteManager {
public:
	SpriteManager() = default;

	~SpriteManager();

	uint32_t CreateSprite(const char* filePath, const KamataEngine::Vector2 initialPosition);

	KamataEngine::Sprite* GetSprite(const uint32_t id);

	void DrawSprite(const uint32_t id);

	bool RemoveSprite(const uint32_t id);

	void SetSpritePosition(const uint32_t, const KamataEngine::Vector2 newPosition);

private:
	struct SpriteInfo {
		uint32_t textureHandle;
		KamataEngine::Sprite* sprite;
	};
	std::map<uint32_t, SpriteInfo> sprites_;

	uint32_t SpriteCount_ = 0;
};