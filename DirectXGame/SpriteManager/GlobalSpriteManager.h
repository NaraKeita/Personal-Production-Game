#pragma once
#include "SpriteManger.h"

//#include <memory>
//
//inline std::unique_ptr<SpriteManager> globalSpriteManager = std::make_unique<SpriteManager>();
inline SpriteManager& GlobalSpriteManager() {
	static SpriteManager instance;
	return instance;
}