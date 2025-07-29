#pragma once

#include "Core.h"

class Engine_API Input
{
	//friend ����
	friend class Engine;
	
	// Ű�Է� Ȯ���� ���� ����ü ����.
	struct KeyState
	{
		// ���� �����ӿ� Ű�� ���ȴ��� ����.
		bool isKeyDown = false;

		// ���� �����ӿ� Ű�� ���ȴ��� ����.
		bool previouseKeyDown = false;
	};

public:
	Input();

	// Ű Ȯ�� �Լ�.
	bool GetKey(int keyCode);
	bool GetKeyDown(int keyCode);
	bool GetKeyUp(int keyCode);

	static Input& Get();

private:
	void ProcessInput();
	void SavePreviousKeyStates();

private:
	static Input* instance;

	// Ű �Է� ���� ���� ����.
	KeyState keyStates[256] = { };
};