#pragma once

#include "Core.h"
#include <Windows.h>


/*
 Todo:
 - Ű �Է� ����.
 - �Է� Ȯ�� �Լ� (GetKey, GetKeyDown, GetKeyUp).

 - Entity �߰� (Actor).
 - �̺�Ʈ �Լ� �߰� (BeginPlay, Tick, Render).
 - Level �߰� (���� ������ ��ġ�� ��ü(Actor) ���� ��ü).
*/


class Engine_API Engine
{
	// Ű �Է� Ȯ���� ���� ����ü
	struct KeyState
	{
		// ���� ������ Ű ���� ����
		bool isKeyDown = false;
		// ���� ������ Ű ���� ����
		bool previousKeyDown = false;
	};
public:

	// ������.
	Engine();

	// �Ҹ���.
	~Engine();

	// ���� ���� �Լ�.
	void Run();

	// Ű Ȯ�� �Լ�.
	bool GetKey(int keyCode);
	bool GetKeyDown(int keyCode);
	bool GetKeyUp(int keyCode);

	// ���� �Լ�.
	void Quit();

private:
	void ProcessInput();
	void Tick(float deltaTime = 0.0f);
	void Render();

private:
	// ���� ���� �÷���.
	bool isQuit = false;
	KeyState keyStates[255] = { };
};