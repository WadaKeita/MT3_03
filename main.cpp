#include <Novice.h>

#include "Function.h"

#include <imgui.h>

const char kWindowTitle[] = "LD2A_02_ワダ_ケイタ";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//const int kWindowWidth = 1280;
	//const int kWindowHeight = 720;

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		Vector2 v2a{ 0.2f, 1.0f };
		Vector2 v2b{ 2.4f, 3.1f };
		Vector2 v2c = v2a + v2b;
		Vector2 v2d = v2a - v2b;
		Vector2 v2e = v2a * 2.4f;
		Vector2 v2f = 2.4f * v2a;
		Vector2 v2g = v2a / 0.1f;
		Vector2 v2h = +v2a;
		Vector2 v2i = -v2a;

		Vector3 v3a{ 0.2f, 1.0f, 0.0f };
		Vector3 v3b{ 2.4f, 3.1f, 1.2f };
		Vector3 v3c = v3a + v3b;
		Vector3 v3d = v3a - v3b;
		Vector3 v3e = v3a * 2.4f;
		Vector3 v3f = 2.4f * v3a;
		Vector3 v3g = v3a / 0.1f;
		Vector3 v3h = +v3a;
		Vector3 v3i = -v3a;

		Vector3 rotate{ 0.4f,1.43f,-0.8f };
		Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
		Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
		Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
		Matrix4x4 rotateMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;

		///
		/// ↓更新処理ここから
		///


		ImGui::Begin("Vector2");
		ImGui::Text("vec2a      :%f, %f", v2a.x, v2a.y);
		ImGui::Text("vec2b      :%f, %f", v2b.x, v2b.y);
		ImGui::Text("add        :%f, %f", v2c.x, v2c.y);
		ImGui::Text("subtract   :%f, %f", v2d.x, v2d.y);
		ImGui::Text("Multiply   :%f, %f", v2e.x, v2e.y);
		ImGui::Text("Multiply2  :%f, %f", v2f.x, v2f.y);
		ImGui::Text("division   :%f, %f", v2g.x, v2g.y);
		ImGui::Text("plus       :%f, %f", v2h.x, v2h.y);
		ImGui::Text("minus      :%f, %f", v2i.x, v2i.y);
		ImGui::End();

		ImGui::Begin("Vector3");
		ImGui::Text("vec3a      :%f, %f, %f", v3a.x, v3a.y, v3a.z);
		ImGui::Text("vec3b      :%f, %f, %f", v3b.x, v3b.y, v3b.z);
		ImGui::Text("add        :%f, %f, %f", v3c.x, v3c.y, v3c.z);
		ImGui::Text("subtract   :%f, %f, %f", v3d.x, v3d.y, v3d.z);
		ImGui::Text("Multiply   :%f, %f, %f", v3e.x, v3e.y, v3e.z);
		ImGui::Text("Multiply2  :%f, %f, %f", v3f.x, v3f.y, v3f.z);
		ImGui::Text("division   :%f, %f, %f", v3g.x, v3g.y, v3g.z);
		ImGui::Text("plus       :%f, %f, %f", v3h.x, v3h.y, v3h.z);
		ImGui::Text("minus      :%f, %f, %f", v3i.x, v3i.y, v3i.z);
		ImGui::End();


		ImGui::Begin("Matrix4x4");
		ImGui::Text("matrix:\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %F, %f\n",
			rotateMatrix.m[0][0], rotateMatrix.m[0][1], rotateMatrix.m[0][2],
			rotateMatrix.m[0][3], rotateMatrix.m[1][0], rotateMatrix.m[1][1],
			rotateMatrix.m[1][2], rotateMatrix.m[1][3], rotateMatrix.m[2][0],
			rotateMatrix.m[2][1], rotateMatrix.m[2][2], rotateMatrix.m[2][3],
			rotateMatrix.m[3][0], rotateMatrix.m[3][1], rotateMatrix.m[3][2],
			rotateMatrix.m[3][3]);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///
		
		///
		/// ↓描画処理ここから
		///


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
