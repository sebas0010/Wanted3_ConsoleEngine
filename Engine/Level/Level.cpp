#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{
}

Level::~Level()
{
	// �޸� ����.
	for (Actor* actor : actors)
	{
		// null Ȯ�� �� ���� ����.
		//if (actor)
		//{
		//	// ���� �� �޸� ����.
		//	delete actor;
		//	actor = nullptr;
		//}

		SafeDelete(actor);
	}

	// std::vector ����.
	actors.clear();
}

// ������ ���͸� �߰��� �� ���.
void Level::AddActor(Actor* newActor)
{
	// ����ó��(�ߺ� ���� Ȯ��) �ʿ���.

	// push_back/emplace_back: �迭 �� �ڿ� ���ο� �׸� �߰��ϴ� �Լ�.
	actors.emplace_back(newActor);
	//actors.push_back(newActor);
}

// ���� �̺�Ʈ �Լ�.
void Level::BeginPlay()
{
	for (Actor* const actor : actors)
	{
		// �̹� ȣ��� ��ü�� �ǳʶٱ�.
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