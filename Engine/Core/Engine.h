#pragma once

#include "Core.h"
#include <Windows.h>

/*
* Todo: 2025�� 7�� 25�� �۾��� ��.
  - ������ �̱���(singleton)���� �����.
*/

class Level;
class Engine_API Engine
{
	// Ű�Է� Ȯ���� ���� ����ü ����.
	struct KeyState
	{
		// ���� �����ӿ� Ű�� ���ȴ��� ����.
		bool isKeyDown = false;

		// ���� �����ӿ� Ű�� ���ȴ��� ����.
		bool previouseKeyDown = false;
	};

public:

	// ������.
	Engine();

	// �Ҹ���.
	~Engine();

	// ���� ���� �Լ�.
	void Run();

	// ���� �߰� �Լ�.
	void AddLevel(Level* newLevel);

	// Ű Ȯ�� �Լ�.
	bool GetKey(int keyCode);
	bool GetKeyDown(int keyCode);
	bool GetKeyUp(int keyCode);

	// ���� �Լ�.
	void Quit();

	// �̱��� ���� �Լ�.
	static Engine& Get();

private:
	void ProcessInput();

	void BeginPlay();
	void Tick(float deltaTime = 0.0f);
	void Render();

private:
	// ���� ���� �÷���.
	bool isQuit = false;

	// Ű �Է� ���� ���� ����.
	KeyState keyStates[256] = { };

	// ���� ����.
	Level* mainLevel = nullptr;

	// �̱��� ����.
	static Engine* instance;
};