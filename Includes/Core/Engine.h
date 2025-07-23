#pragma once

#include "Core.h"
#include <Windows.h>


/*
 Todo:
 - 키 입력 관리.
 - 입력 확인 함수 (GetKey, GetKeyDown, GetKeyUp).

 - Entity 추가 (Actor).
 - 이벤트 함수 추가 (BeginPlay, Tick, Render).
 - Level 추가 (가상 공간에 배치된 물체(Actor) 관리 객체).
*/


class Engine_API Engine
{
	// 키 입력 확인을 위한 구조체
	struct KeyState
	{
		// 현재 프레임 키 눌림 여부
		bool isKeyDown = false;
		// 이전 프레임 키 눌림 여부
		bool previousKeyDown = false;
	};
public:

	// 생성자.
	Engine();

	// 소멸자.
	~Engine();

	// 엔진 실행 함수.
	void Run();

	// 키 확인 함수.
	bool GetKey(int keyCode);
	bool GetKeyDown(int keyCode);
	bool GetKeyUp(int keyCode);

	// 종료 함수.
	void Quit();

private:
	void ProcessInput();
	void Tick(float deltaTime = 0.0f);
	void Render();

private:
	// 엔진 종료 플래그.
	bool isQuit = false;
	KeyState keyStates[255] = { };
};