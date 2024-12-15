#include "MainScene.h"
#include "Shader.h"
#include "Mesh.h"
#include "App.h"
#include "Rasterization.h"
#include "ImageUtils.h"
#include "Window.h"
#include <GLFW/glfw3.h> 


constexpr int IMAGE_SIZE = 512;

int currentScene = 1;

void MainScene::OnLoad()
{
	LoadImage(&mImage, IMAGE_SIZE, IMAGE_SIZE);
	LoadTexture(&mTexture, IMAGE_SIZE, IMAGE_SIZE);
}

void MainScene::OnUnload()
{
	UnloadTexture(&mTexture);
	UnloadImage(&mImage);
}
void MainScene::OnUpdate(float dt)
{
	ClearColor(&mImage, BLACK);
	ClearDepth(&mImage, 1.0f);


		//1. Sphere:

		static float animTime = 0.0f;
		animTime += dt;
		
		if (animTime > 3.0)
		{
			animTime = 0.0f;
		}
		
		float angle = animTime * 3.0f;
		float radius = 5.0f * (1.0f - animTime / 3.0f);
		
		float xPos = radius * cos(angle);
		float yPos = radius * sin(angle);
		
		Matrix model = Translate(xPos, yPos, 5.0f + sinf(animTime) * 2.0f);
		Matrix view = LookAt({ 0.0f, 0.0f, 10.0f }, V3_ZERO, V3_UP);
		Matrix proj = Perspective(90.0f * DEG2RAD, 1.0f, 0.001f, 10.0f);
		Matrix mvp = model * view * proj;
		
		UniformData uniform;
		uniform.mvp = model * view * proj;
		uniform.world = model;
		uniform.normal = NormalMatrix(model);
		
		DrawMesh(&mImage, gMeshRobo, uniform);


		// 2. Cube

		//Matrix model = Translate(0.0f, -5.0f, 0.0f);
		//Matrix rotation = RotateY(TotalTime() * 3.0f);
		//Matrix view = LookAt({ 0.0f, 0.0f, 5.0f }, { 0.0f, 0.0f, 0.0f }, V3_UP);
		//Matrix proj = Perspective(90.0f * DEG2RAD, 1.0f, 0.001f, 100.0f);
		//
		//UniformData uniform;
		//uniform.mvp = rotation* model * view * proj;
		//uniform.world = model;
		//uniform.normal = NormalMatrix(model);
		//
		//uniform.lightPosition = { 0.0f, 0.0f, -10.0f };
		//
		//
		//DrawMesh(&mImage, gMeshRobo, uniform);

	

		//3. Phong(incomplete)

		//float tt = TotalTime();
		//float cutoff = cos(45.0f * DEG2RAD);
		//
		//Matrix translation = Translate(0.0f, -5.0f, 0.0f);
		//Matrix rotation = RotateY(TotalTime() * 00.0f * DEG2RAD);
		//Matrix scale = MatrixIdentity();
		//
		//Matrix model = scale * rotation * translation;
		//Matrix view = LookAt({ 0.0f, 0.0f, 10.0f }, V3_ZERO, V3_UP);
		//Matrix proj = Perspective(90.0f * DEG2RAD, 1.0f, 0.001f, 50.0f);
		//
		//UniformData uniform;
		//uniform.mvp = model * view * proj;
		//uniform.world = model;
		//uniform.normal = NormalMatrix(model);
		//
		//uniform.lightPosition = { 0.0f, 0.0f, 0.0f };
		//
		//DrawMesh(&mImage, gMeshRobo, uniform);

	

		//4. Spot Light
		//float tt = TotalTime();
		//float cutoff = cos(45.0f * DEG2RAD);
		//
		//Matrix translation = Translate(0.0f, -5.0f, 0.0f);
		//Matrix rotation = RotateY(TotalTime() * 00.0f * DEG2RAD);
		//Matrix scale = MatrixIdentity();
		//
		//Matrix model = scale * rotation * translation;
		//Matrix view = LookAt({ 0.0f, 0.0f, 10.0f }, V3_ZERO, V3_UP);
		//Matrix proj = Perspective(90.0f * DEG2RAD, 1.0f, 0.001f, 50.0f);
		//
		//UniformData uniform;
		//uniform.mvp = model * view * proj;
		//uniform.world = model;
		//uniform.normal = NormalMatrix(model);
		//
		//uniform.lightPosition = { 0.0f, 8.0f, 10.0f * sin(tt) };
		//
		//DrawMesh(&mImage, gMeshRobo, uniform);

	}

void MainScene::OnDraw()
{
	UpdateTexture(mTexture, mImage);

	BindTexture(mTexture);
	BindShader(&gShaderFSQ);
	SendInt("u_tex", 0);
	BindFsq();
	DrawFsq();
	UnbindShader();
	UnbindTexture(mTexture);
}
