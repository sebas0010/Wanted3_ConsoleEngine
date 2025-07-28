#include "SokobanLevel.h"
#include "Math/Vector2.h"

#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"

#include <iostream>

SokobanLevel::SokobanLevel()
{
	ReadMapFile("Map.txt");
}

void SokobanLevel::ReadMapFile(const char* filename)
{
	// ���� �ּ� ��� �ϼ�.
	char filepath[256] = { };
	sprintf_s(filepath, 256, "../Assets/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, filepath, "rb");

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

	if (fileSize != readSize)
	{
		std::cout << "fileSize is not matched with readSize.\n";
	}

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

			// @Todo: �׽�Ʈ�뵵. ���߿� �����ؾ���.
			std::cout << "\n";
			continue;
		}

		// �� ���� ���� ó��.
		switch (mapCharacter)
		{
		case '#':
			AddActor(new Wall(position));
			//std::cout << "#";
			break;
		case '.':
			AddActor(new Ground(position));
			//std::cout << ".";
			break;
		case 'p':
			// Player ���� ����.
			AddActor(new Player(position));
			//std::cout << "p";
			break;
		case 'b':
			AddActor(new Box(position));
			//std::cout << "b";
			break;
		case 't':
			AddActor(new Target(position));
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