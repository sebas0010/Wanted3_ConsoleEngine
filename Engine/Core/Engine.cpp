#include "Engine.h"
#include <iostream>
#include <Windows.h>

#include "Level/Level.h"
#include "Utils/Utils.h"
#include "Input.h"

// ���� ���� �ʱ�ȭ.
Engine* Engine::instance = nullptr;

BOOL WINAPI ConsoleMessageProcedure(DWORD CtrlType)
{
	switch (CtrlType)
	{
	case CTRL_CLOSE_EVENT:
		// Engine�� �޸� ����.
		//Engine::Get().~Engine();
		Engine::Get().CleanUp();
		return false;
	}

	return false;
}

Engine::Engine()
{
	instance = this;

	// �ܼ� Ŀ�� ����.
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;

	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&info
	);

	// �ܼ� â �̺�Ʈ ���.
	SetConsoleCtrlHandler(ConsoleMessageProcedure, TRUE);
}

Engine::~Engine()
{
	CleanUp();
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
		input.ProcessInput();

		// ���� ������.
		if (deltaTime >= oneFrameTime)
		{
			BeginPlay();
			Tick(deltaTime);
			Render();

			// �ð� ������Ʈ.
			previousTime = currentTime;

			// ���� �������� �Է��� ���.
			input.SavePreviouseKeyStates();
		}
	}

	// ����(�ؽ�Ʈ ���� ������� ��������).
	Utils::SetConsoleTextColor(
		FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
	);
}

void Engine::AddLevel(Level* newLevel)
{
	// ������ �ִ� ������ ����.
	if (mainLevel)
	{
		delete mainLevel;
	}

	mainLevel = newLevel;
}

void Engine::CleanUp()
{
	// ���� ����.
	SafeDelete(mainLevel);
	//if (mainLevel)
	//{
	//	delete mainLevel;
	//	mainLevel = nullptr;
	//}
}

void Engine::Quit()
{
	// ���� �÷��� ����.
	isQuit = true;
}

Engine& Engine::Get()
{
	return *instance;
}

void Engine::BeginPlay()
{
	if (mainLevel)
	{
		mainLevel->BeginPlay();
	}
}

void Engine::Tick(float deltaTime)
{
	//std::cout 
	//	<< "DeltaTime: " << deltaTime 
	//	<< ", FPS: " <<  (1.0f / deltaTime)
	//	<< "\n";

	//if (GetKeyDown('A'))
	//{
	//	std::cout << "KeyDown\n";
	//}
	//if (GetKey('A'))
	//{
	//	std::cout << "Key\n";
	//}
	//if (GetKeyUp('A'))
	//{
	//	std::cout << "KeyUp\n";
	//}

	// ���� ������Ʈ.
	if (mainLevel)
	{
		mainLevel->Tick(deltaTime);
	}

	//if (GetKeyDown(VK_ESCAPE))
	//{
	//	Quit();
	//}
}

void Engine::Render()
{
	//SetConsoleTextAttribute(
	//	GetStdHandle(STD_OUTPUT_HANDLE),
	//	FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
	//);

	Utils::SetConsoleTextColor(
		FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
	);

	if (mainLevel)
	{
		mainLevel->Render();
	}
}