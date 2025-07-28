#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{
}

Level::~Level()
{
	// 메모리 해제.
	for (Actor* actor : actors)
	{
		// null 확인 후 액터 제거.
		//if (actor)
		//{
		//	// 삭제 및 메모리 정리.
		//	delete actor;
		//	actor = nullptr;
		//}

		SafeDelete(actor);
	}

	// std::vector 정리.
	actors.clear();
}

// 레벨에 액터를 추가할 때 사용.
void Level::AddActor(Actor* newActor)
{
	// 예외처리(중복 여부 확인) 필요함.

	// push_back/emplace_back: 배열 맨 뒤에 새로운 항목 추가하는 함수.
	actors.emplace_back(newActor);
	//actors.push_back(newActor);
}

// 엔진 이벤트 함수.
void Level::BeginPlay()
{
	for (Actor* const actor : actors)
	{
		// 이미 호출된 개체는 건너뛰기.
		if (actor->HasBeganPlay())
		{
			continue;
		}

		actor->BeginPlay();
	}
}

void Level::Tick(float deltaTime)
{
	for (Actor* const actor : actors)
	{
		actor->Tick(deltaTime);
	}
}

void Level::Render()
{
	for (Actor* const actor : actors)
	{
		actor->Render();
	}
}