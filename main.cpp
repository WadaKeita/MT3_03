#include <Novice.h>

#include "Function.h"

#include <imgui.h>

const char kWindowTitle[] = "LD2A_02_ワダ_ケイタ";


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


	Vector3 translates[3] = {
		{0.2f, 1.0f, 0.0f},
		{0.4f, 0.0f, 0.0f},
		{0.3f, 0.0f, 0.0f},
	};
	Vector3 rotates[3] = {
		{0.0f, 0.0f, -6.8f},
		{0.0f, 0.0f, -1.4f},
		{0.0f, 0.0f, 0.0f},
	};
	Vector3 scales[3] = {
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
	};


	Sphere sphere[3];
	sphere[0].radius = 0.1f;
	sphere[1].radius = 0.1f;
	sphere[2].radius = 0.1f;

	sphere[0].center = { 0,0,0 };
	sphere[1].center = { 0,0,0 };
	sphere[2].center = { 0,0,0 };

	unsigned int sphere_color[3];
	sphere_color[0] = RED;
	sphere_color[1] = GREEN;
	sphere_color[2] = BLUE;


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

		Matrix4x4 localMatrix[3];
		localMatrix[0] = MakeAffineMatrix(scales[0], rotates[0], translates[0]);
		localMatrix[1] = MakeAffineMatrix(scales[1], rotates[1], translates[1]);
		localMatrix[2] = MakeAffineMatrix(scales[2], rotates[2], translates[2]);

		Matrix4x4 worldMatrix[3];
		worldMatrix[0] = localMatrix[0];
		worldMatrix[1] = Multiply(localMatrix[1], worldMatrix[0]);
		worldMatrix[2] = Multiply(localMatrix[2], worldMatrix[1]);


		Matrix4x4 cameraMatrix = MakeAffineMatrix(camera.scale, camera.rotate, camera.translate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		//Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);


		Segment segment[2];
		segment[0].origin = GetWorldPosition(worldMatrix[0]);
		segment[0].diff = Subtract(GetWorldPosition(worldMatrix[1]), GetWorldPosition(worldMatrix[0]));

		segment[1].origin = GetWorldPosition(worldMatrix[1]);
		segment[1].diff = Subtract(GetWorldPosition(worldMatrix[2]), GetWorldPosition(worldMatrix[1]));

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// グリッド描画
		DrawGrid(viewProjectionMatrix, viewportMatrix);

		DrawSegment(segment[0], viewProjectionMatrix, viewportMatrix, WHITE);
		DrawSegment(segment[1], viewProjectionMatrix, viewportMatrix, WHITE);

		DrawSphere(sphere[0], Multiply(worldMatrix[0],viewProjectionMatrix), viewportMatrix, sphere_color[0]);
		DrawSphere(sphere[1], Multiply(worldMatrix[1], viewProjectionMatrix), viewportMatrix, sphere_color[1]);
		DrawSphere(sphere[2], Multiply(worldMatrix[2], viewProjectionMatrix), viewportMatrix, sphere_color[2]);


		ImGui::Begin("camera");
		ImGui::DragFloat3("scale", &camera.scale.x, 0.01f);
		ImGui::DragFloat3("Translation", &camera.translate.x, 0.01f);
		ImGui::DragFloat3("rotate", &camera.rotate.x, 0.01f);
		ImGui::DragFloat("translateSpeed", &camera.translateSpeed, 0.01f);
		ImGui::DragFloat("rotateSpeed", &camera.rotateSpeed, 0.01f);
		ImGui::End();


		ImGui::Begin("sphere");

		ImGui::DragFloat3("translates[0]", &translates[0].x, 0.01f);
		ImGui::DragFloat3("rotates[0]", &rotates[0].x, 0.01f);
		ImGui::DragFloat3("scales[0]", &scales[0].x, 0.01f);

		ImGui::DragFloat3("translates[1]", &translates[1].x, 0.01f);
		ImGui::DragFloat3("rotates[1]", &rotates[1].x, 0.01f);
		ImGui::DragFloat3("scales[1]", &scales[1].x, 0.01f);
		
		ImGui::DragFloat3("translates[2]", &translates[2].x, 0.01f);
		ImGui::DragFloat3("rotates[2]", &rotates[2].x, 0.01f);
		ImGui::DragFloat3("scales[2]", &scales[2].x, 0.01f);


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
