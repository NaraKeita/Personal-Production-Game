#include "SpringScene.h"
#include "TitleScene.h"
#include "kamataEngine.h"
#include "SpriteManager/GlobalSpriteManger.h"
#include <Windows.h>

using namespace KamataEngine;

// シーン（型）
enum class Scene {
	kUnknown = 0,
	kTitle,
	kGame,
};

// 現在シーン（型）
Scene scene = Scene::kUnknown;

void ChangeScene();
void UpdateScene();
void DrawScene();

TitleScene* titleScene = nullptr;
SpringScene* springScene = nullptr;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	KamataEngine::Initialize(L"LE3D_10_ナラ_ケイタ");

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	/*std::unique_ptr<SpringScene> springScene = std::make_unique<SpringScene>();
	springScene->Initialize();*/

	ImGuiManager* imGuiManager = ImGuiManager::GetInstance();

	// ゲームシーンの初期化
	titleScene = new TitleScene();
	titleScene->Initialize();
	scene = Scene::kTitle;

	while (true) {
		if (KamataEngine::Update()) {
			break;
		}

		// ImGui受付開始
		imGuiManager->Begin();

		// springScene->Update();

		ChangeScene();
		UpdateScene();

		imGuiManager->End();

		dxCommon->PreDraw();

		// springScene->Draw();
		DrawScene();

		imGuiManager->Draw();

		dxCommon->PostDraw();
	}

	// 各種解放
	delete titleScene;
	delete springScene;

	KamataEngine::Finalize();

	return 0;
}

// シーン切り替え
// シーン切り替え
void ChangeScene() {

	switch (scene) {
	case Scene::kTitle:
		if (titleScene->IsFinished()) {
			// シーン変更
			scene = Scene::kGame;
			// 旧シーンの開放
			delete springScene;
			springScene = nullptr;
			// 新シーンの生成と初期化
			springScene = new SpringScene;
			springScene->Initialize();
		}
		break;
	case Scene::kGame:
		if (springScene->IsFinished()) {
			// シーン変更
			scene = Scene::kTitle;
			// 旧シーンの開放
			delete titleScene;
			titleScene = nullptr;
			// 新シーンの生成と初期化
			titleScene = new TitleScene;
			titleScene->Initialize();
		}
		break;
	}
}

// 現在シーン更新
void UpdateScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Update();
		break;
	case Scene::kGame:
		springScene->Update();
		break;
	}
}

// 現在シーンの描画
void DrawScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Draw();
		break;
	case Scene::kGame:
		springScene->Draw();
		break;
	}
}