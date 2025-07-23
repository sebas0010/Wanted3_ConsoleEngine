#include "Actor.h"

Actor::Actor()
{

}
Actor::~Actor()
{

}
// 객체 생애주기(Lifetime)에 한번만 호출됨(초기화 목적)
void Actor::BeginPlay()
{
	hasBeganPlay = true;
}

// 프레임 마다 호출 (반복성 작업 / 지속성 작업)
void Actor::Tick(float deltaTime)
{

}

// 그리기 함수
void Actor::Render()
{

}