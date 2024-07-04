#include <Novice.h>

#include "Function.h"

#include <imgui.h>

const char kWindowTitle[] = "LD2A_02_ワダ_ケイタ";


Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) {
	Vector3 result;

	result.x = (1.0f - t) * v1.x + t * v2.x;
	result.y = (1.0f - t) * v1.y + t * v2.y;
	result.z = (1.0f - t) * v1.z + t * v2.z;

	return result;
}

void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2,
	const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 point[11];

	float t = 0;
	for (int i = 0; i < 11; i++) {
		Vector3 p0p1 = Lerp(controlPoint0, controlPoint1, t);
		Vector3 p1p2 = Lerp(controlPoint1, controlPoint2, t);

		point[i] = Lerp(p0p1, p1p2, t);

		point[i] = Transform(Transform(point[i], viewProjectionMatrix), viewportMatrix);

		t += 0.1f;
	}

	// 描画
	for (int i = 0; i < 10; i++) {
		Novice::DrawLine(int(point[i].x), int(point[i].y), int(point[int(i + 1)].x), int(point[int(i + 1)].y), color);
	}

}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// カメラ
	Camera camera{
		 { 1.0f,1.0f,1.0f },
		 { 0.0f,1.9f,-6.49f },
		 { 0.26f,0.0f,0.0f },
		0.05f,
		0.01f,
	};

	// ベジェ曲線コントロールポイント
	Vector3 controlPoint[3] = {
		{-0.0f, 0.58f, 1.0f },
		{1.76f, 1.0f, -0.3f },
		{0.94f, -0.7f, 2.3f },
	};
	unsigned int bezierColor = 0xFFFFFFFF;

	Sphere sphere[3];

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

		CameraOperation(camera, keys);

		sphere[0] = { controlPoint[0],0.01f };
		sphere[1] = { controlPoint[1],0.01f };
		sphere[2] = { controlPoint[2],0.01f };

		Matrix4x4 cameraMatrix = MakeAffineMatrix(camera.scale, camera.rotate, camera.translate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		//Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// グリッド描画
		DrawGrid(viewProjectionMatrix, viewportMatrix);

		DrawBezier(controlPoint[0], controlPoint[1], controlPoint[2], viewProjectionMatrix, viewportMatrix, bezierColor);

		DrawSphere(sphere[0], viewProjectionMatrix, viewportMatrix, BLACK);
		DrawSphere(sphere[1], viewProjectionMatrix, viewportMatrix, BLACK);
		DrawSphere(sphere[2], viewProjectionMatrix, viewportMatrix, BLACK);


		ImGui::Begin("camera");
		ImGui::DragFloat3("scale", &camera.scale.x, 0.01f);
		ImGui::DragFloat3("Translation", &camera.translate.x, 0.01f);
		ImGui::DragFloat3("rotate", &camera.rotate.x, 0.01f);
		ImGui::DragFloat("translateSpeed", &camera.translateSpeed, 0.01f);
		ImGui::DragFloat("rotateSpeed", &camera.rotateSpeed, 0.01f);
		ImGui::End();

		ImGui::Begin("point");

		ImGui::DragFloat3("point0", &controlPoint[0].x, 0.01f);
		ImGui::DragFloat3("point1", &controlPoint[1].x, 0.01f);
		ImGui::DragFloat3("point2", &controlPoint[2].x, 0.01f);

		ImGui::End();


		ImGui::Begin("sphere");

		ImGui::DragFloat3("sphere0", &sphere[0].center.x, 0.01f);
		ImGui::DragFloat3("sphere1", &sphere[1].center.x, 0.01f);
		ImGui::DragFloat3("sphere2", &sphere[2].center.x, 0.01f);

		ImGui::End();

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
