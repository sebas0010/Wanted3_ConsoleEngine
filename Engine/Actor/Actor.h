#pragma once

#include "Core.h"
#include "Math/Vector2.h"

// 물체가 하는 일 정의
// 위치 점령 -> Vector2
// 콘솔 창에 그리기 -> char
// 엔진의 이벤트 함수 호출
// BeginPlay/Tick/Draw

class Engine_API Actor
{
public:
	Actor();
	virtual ~Actor();

	// 이벤트 함수

	// 객체 생애주기(Lifetime)에 한번만 호출됨(초기화 목적)
	virtual void BeginPlay();

	// 프레임 마다 호출 (반복성 작업 / 지속성 작업)
	virtual void Tick(float deltaTime);

	// 그리기 함수
	virtual void Render();

	// BeginPlay 호출 여부 확인
	inline bool HasBeganPlay() const { return hasBeganPlay; }

private:
	// 개체의 위치
	Vector2 position;

	// 그릴 값.
	char image = ' ';

	// BeginPlay 호출이 되었는지 확인
	bool hasBeganPlay = false;
};