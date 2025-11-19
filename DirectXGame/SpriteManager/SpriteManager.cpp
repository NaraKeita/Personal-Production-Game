#include "SpriteManger.h"


using namespace KamataEngine;

SpriteManager::~SpriteManager() {
	for (auto const& [id, sprite_info] : sprites_) {
		if (sprite_info.sprite != nullptr) {
			delete sprite_info.sprite; // スプライトオブジェクトを解放
		}
		TextureManager::Unload(sprite_info.textureHandle);
	}
	sprites_.clear(); // マップをクリア
	std::cout << "SpriteManager: All sprites and textures cleared." << std::endl;
}

uint32_t SpriteManager::CreateSprite(const char* filePath, const Vector2 initialPosition) {
	uint32_t id = ++SpriteCount_;

	uint32_t textureHandle = TextureManager::Load(filePath);
	Sprite* newSprite = Sprite::Create(textureHandle, initialPosition);

	// スプライトとその関連情報を構造体にまとめて保存
	SpriteInfo info;
	info.textureHandle = textureHandle;
	info.sprite = newSprite;
	sprites_[id] = info;

	std::cout << "SpriteManager: Created and added sprite '" << id << "'." << std::endl;
	return id;
}

Sprite* SpriteManager::GetSprite(uint32_t id) {
	return sprites_[id].sprite; 
}

// 指定されたスプライトを描画
void SpriteManager::DrawSprite(uint32_t id) {
	Sprite* sprite = GetSprite(id);
	if (sprite != nullptr) {
		sprite->Draw();
	}
}

bool SpriteManager::RemoveSprite(uint32_t id) {
	auto it = sprites_.find(id);
	if (it != sprites_.end()) {
		if (it->second.sprite != nullptr) {
			delete it->second.sprite; // スプライトオブジェクトを解放
		}
		TextureManager::Unload(it->second.textureHandle);	// 関連するテクスチャもアンロード
		sprites_.erase(it);									// マップからエントリを削除
		std::cout << "SpriteManager: Removed sprite '" << id << "' and its resources." << std::endl;
		return true;
	}
	std::cerr << "Warning: Attempted to remove non-existent sprite with ID '" << id << "'." << std::endl;
	return false;
}

void SpriteManager::SetSpritePosition(uint32_t id, const Vector2 newPosition) {
	Sprite* sprite = GetSprite(id);
	if (sprite != nullptr) {
		sprite->SetPosition(newPosition);
	}
}
