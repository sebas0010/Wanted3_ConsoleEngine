#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{

}
Level::~Level()
{

}

// ������ ���͸� �߰��� �� ���
void Level::AddActor(Actor* newActor)
{
	// ����ó��(�ߺ� ���� Ȯ��) �ʿ���
	actors.emplace_back(newActor);
	//actors.push_back(newActor);
}

// ���� �̺�Ʈ �Լ�
void Level::BeginPlay()
{
	for (Actor* const actor : actors)
	{
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