#include "SokobanLevel.h"
#include "Math/Vector2.h"

#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"
#include "Utils/Utils.h"
#include <iostream>

SokobanLevel::SokobanLevel()
{
	//ReadMapFile("Map.txt");
	ReadMapFile("Stage1.txt");
	//ReadMapFile("Stage2.txt");
	//ReadMapFile("Stage3.txt");
}

void SokobanLevel::ReadMapFile(const char* filename)
{
	// ���� �ּ� ��� �ϼ�.
	char filepath[256] = { };
	sprintf_s(filepath, 256, "../Assets/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, filepath, "rt");

	// ����ó��.
	if (file == nullptr)
	{
		std::cout << "�� ���� �б� ����: " << filename << "\n";
		__debugbreak();
		return;
	}

	// �Ľ�(Parcing, �ؼ�).
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	// Ȯ���� ���� ũ�⸦ Ȱ���� ���� �Ҵ�.
	char* buffer = new char[fileSize + 1];
	//buffer[fileSize] = '\0';
	memset(buffer, 0, fileSize + 1);
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	//if (fileSize != readSize)
	//{
	//	std::cout << "fileSize is not matched with readSize.\n";
	//}

	// �迭 ��ȸ�� ���� �ε��� ����.
	int index = 0;

	// ���ڿ� ���� ��.
	int size = (int)readSize;

	// x, y ��ǥ.
	Vector2 position;

	// ���� �迭 ��ȸ.
	while (index < size)
	{
		// �� ���� Ȯ��.
		char mapCharacter = buffer[index];
		++index;

		// ���� ���� ó��.
		if (mapCharacter == '\n')
		{
			// ���� �ٷ� �ѱ�鼭, x ��ǥ �ʱ�ȭ.
			++position.y;
			position.x = 0;

			// �׽�Ʈ�뵵. ���߿� �����ؾ���.
			//std::cout << "\n";
			continue;
		}

		// �� ���� ���� ó��.
		switch (mapCharacter)
		{
		case '#':
		case '1':
			AddActor(new Wall(position));
			//std::cout << "#";
			break;
		case '.':
			AddActor(new Ground(position));
			//std::cout << ".";
			break;
		case 'p':

			// ���� ���� ����.
			AddActor(new Ground(position));

			// Player ���� ����.
			AddActor(new Player(position));
			//std::cout << "p";
			break;
		case 'b':

			// ���� ���� ����.
			AddActor(new Ground(position));
			AddActor(new Box(position));
			//std::cout << "b";
			break;
		case 't':
			AddActor(new Target(position));

			// ��ǥ ���� ���� ó��.
			++targetScore;
			//std::cout << "t";
			break;
		}

		// x ��ǥ ���� ó��.
		++position.x;
	}

	// ���� ����.
	delete[] buffer;

	// ���� �ݱ�.
	fclose(file);
}

bool SokobanLevel::CheckGameClear()
{
	// �ڽ��� Ÿ�� ��ġ�� ��� �Ű������� Ȯ��.
	int currentScore = 0;

	// Ÿ�� ���� ���Ϳ� ����.
	std::vector<Actor*> targetActors;
	std::vector<Actor*> boxActors;
	for (Actor* const actor : actors)
	{
		// Ÿ�� �������� Ȯ��.
		if (actor->As<Target>())
		{
			targetActors.emplace_back(actor);
			continue;
		}

		// �ڽ� �������� Ȯ��.
		if (actor->As<Box>())
		{
			boxActors.emplace_back(actor);
		}
	}

	// �ڽ��� Ÿ�� ���� ��ġ ��.
	for (Actor* const targetActor : targetActors)
	{
		for (Actor* const boxActor : boxActors)
		{
			// �� ������ ��ġ�� ������ ���� ���� ó��.
			if (targetActor->Position() == boxActor->Position())
			{
				// ���� ����.
				++currentScore;
			}
		}
	}

	return currentScore == targetScore;
}

bool SokobanLevel::CanPlayerMove(
	const Vector2& playerPosition, 
	const Vector2& newPosition)
{
	// ���� Ŭ���� ���� Ȯ�� �� ���� ó��.
	if (isGameClear)
	{
		return false;
	}

	// �ڽ� ó��.
	std::vector<Box*> boxActors;
	for (Actor* const actor : actors)
	{
		Box* box = actor->As<Box>();
		if (box)
		{
			boxActors.emplace_back(box);
		}
	}

	// �̵��Ϸ��� ��ġ�� �ڽ��� �ִ��� Ȯ��.
	Box* searchedBox = nullptr;
	for (Box* const boxActor : boxActors)
	{
		// �÷��̾ �̵��Ϸ��� ��ġ�� �ڽ��� ��ġ�� ������ ��.
		if (boxActor->Position() == newPosition)
		{
			// ���� ��ġ�� �ִ� �ڽ� ���� �� ���� ����.
			searchedBox = boxActor;
			break;
		}
	}

	// �̵��Ϸ��� ��ġ�� �ڽ��� �ִ� ��� ó��.
	if (searchedBox)
	{
		// #1: �ڽ��� �̵���Ű���� ��ġ�� �ٸ� �ڽ��� �� �ִ��� Ȯ��.
		Vector2 direction = newPosition - playerPosition;
		Vector2 nextPosition = searchedBox->Position() + direction;

		for (Box* const otherBox : boxActors)
		{
			// ���� �ڽ��� �ǳʶٱ�.
			if (otherBox == searchedBox)
			{
				continue;
			}

			// �ڽ��� �̵���Ű���� ��ġ�� �ٸ� �ڽ��� �ִ��� Ȯ��.
			if (otherBox->Position() == nextPosition)
			{
				// �÷��̾� �̵� ����.
				return false;
			}
		}

		for (Actor* const actor : actors)
		{
			if (actor->Position() == nextPosition)
			{
				// #2: �ڽ��� ������, ���� ���� ������ Ȯ��.
				if (actor->As<Wall>())
				{
					// �÷��̾� �̵� ����.
					return false;
				}

				// #3: �̵� ������ ���(�׶���, Ÿ��)���� �ڽ� �̵� ó��.
				if (actor->As<Ground>() || actor->As<Target>())
				{
					// �ڽ� �̵� ó��.
					searchedBox->SetPosition(nextPosition);

					// ���� Ŭ���� ���� Ȯ��.
					isGameClear = CheckGameClear();

					// �÷��̾� �̵� ����.
					return true;
				}
			}
		}
	}

	// �÷��̾ �̵��Ϸ��� ��ġ�� �ڽ��� ���� ���.
	for (Actor* const actor : actors)
	{
		if (actor->Position() == newPosition)
		{
			// ���̸� �̵� �Ұ�.
			if (actor->As<Wall>())
			{
				return false;
			}

			// �׶��� or Ÿ��.
			return true;
		}
	}

	// ???.
	return false;
}

void SokobanLevel::Render()
{
	super::Render();
	
	if (isGameClear)
	{
		Utils::SetConsolePosition({ 30, 0 });
		Utils::SetConsoleTextColor(
			static_cast<WORD>(Color::White)
		);

		std::cout << "Game Clear!";
	}
}
