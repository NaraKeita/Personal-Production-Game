#include <Windows.h>
#include "SpringScene.h"
#include "kamataEngine.h"

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	KamataEngine::Initialize(L"LE3D_10_ナラ_ケイタ");

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	std::unique_ptr<SpringScene> springScene = std::make_unique<SpringScene>();
	springScene->Initialize();

	ImGuiManager* imGuiManager = ImGuiManager::GetInstance();

	while (true) {
		if (KamataEngine::Update()) {
			break;
		}

		// ImGui受付開始
		imGuiManager->Begin();

		springScene->Update();

		imGuiManager->End();

		dxCommon->PreDraw();

		springScene->Draw();

		imGuiManager->Draw();

		dxCommon->PostDraw();
	}

	KamataEngine::Finalize();

	return 0;
}
