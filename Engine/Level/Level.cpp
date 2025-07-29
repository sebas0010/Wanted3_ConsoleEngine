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
	
	// ���ʽ� ����.
	newActor->SetOwner(this);
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
	// �׸��� ���� ���� ���� �������� ���ġ(����).
	SortActorsBySortingOrder();

	// Render Pass.
	for (Actor* const actor : actors)
	{
		// �˻� (���� ��ġ�� ���� ���� ���� ���Ͱ� �ִ��� Ȯ��).
		Actor* searchedActor = nullptr;
		for (Actor* const otherActor : actors)
		{
			// ���� ���͸� ����.
			if (actor == otherActor)
			{
				continue;
			}

			// ��ġ�� ���� ���� Ȯ��.
			if (actor->Position() == otherActor->Position())
			{
				// ���� ���� �� �� ���� ����.
				if (actor->sortingOrder < otherActor->sortingOrder)
				{
					// ���� �� ���� ����.
					searchedActor = otherActor;
					break;
				}
			}
		}

		// � ���Ϳ� ���� ��ġ�� ���� ������ �� ���� ���Ͱ� ������,
		// �׸��� �ʰ� �ǳʶٱ�.
		if (searchedActor)
		{
			continue;
		}

		// ��ο� ��.
		actor->Render();
	}
}

void Level::SortActorsBySortingOrder()
{
	// ���� ����.
	for (int ix = 0; ix < (int)actors.size(); ++ix)
	{
		for (int jx = 0; jx < (int)actors.size() - 1; ++jx)
		{
			// sortingOrder ���� Ŭ���� �� �ʿ� ��ġ.
			if (actors[jx]->sortingOrder > actors[jx + 1]->sortingOrder)
			{
				// �� ���� ��ġ ��ȯ.
				std::swap(actors[jx], actors[jx + 1]);
			}
		}
	}
}