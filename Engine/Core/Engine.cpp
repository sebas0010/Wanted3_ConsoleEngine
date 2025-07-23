#include "Engine.h"
#include <iostream>
//#include <chrono>

// 2����.
// ��������.
// �ܼ� �Է� ó��(Ű����).
// Ÿ�̸�(�ð� ���).

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::Run()
{
	// �и� ������ ������ ���� �ð��� �˷���.
	//float currentTime = timeGetTime();
	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;
	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;

	// �ϵ���� �ð��� ���е�(���ļ�) ��������.
	// ���߿� �ʷ� ��ȯ�ϱ� ����.
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// Ÿ�� ������.
	float targetFrameRate = 60.0f;

	// Ÿ�� �� ������ �ð�.
	float oneFrameTime = 1.0f / targetFrameRate;

	// GameLoop.
	while (true)
	{
		// ���� ���� ���� Ȯ��.
		if (isQuit)
		{
			// ���� ����.
			break;
		}

		// ������ �ð� ���.
		// (���� �ð� - ���� �ð�) / ���ļ� = �ʴ���.
		QueryPerformanceCounter(&currentTime);

		// ������ �ð�.
		float deltaTime = 
			(currentTime.QuadPart - previousTime.QuadPart)
			/ (float)frequency.QuadPart;

		// �Է��� �ִ��� ����.
		ProcessInput();

		// ���� ������.
		if (deltaTime >= oneFrameTime)
		{
			Tick(deltaTime);
			Render();

			// �ð� ������Ʈ.
			previousTime = currentTime;

			// ���� �������� �Է� ���
			for (int ix = 0; ix < 255; ++ix)
			{
				keyStates[ix].previousKeyDown = keyStates[ix].isKeyDown;
			}
		}
	}
}

bool Engine::GetKey(int keyCode)
{
	return keyStates[keyCode].isKeyDown;
}

bool Engine::GetKeyDown(int keyCode)
{
	return !keyStates[keyCode].previousKeyDown && keyStates[keyCode].isKeyDown;
}

bool Engine::GetKeyUp(int keyCode)
{
	return keyStates[keyCode].previousKeyDown && !keyStates[keyCode].isKeyDown;
}

void Engine::Quit()
{
	// ���� �÷��� ����.
	isQuit = true;
}

void Engine::ProcessInput()
{
	// Ű �Է� Ȯ��
	for (int ix = 0; ix < 255; ++ix)
	{
		keyStates[ix].isKeyDown = GetAsyncKeyState(ix) & 0x8000;
	}
}

void Engine::Tick(float deltaTime)
{
	if (GetKeyDown(VK_ESCAPE)) Quit();


}

void Engine::Render()
{
}