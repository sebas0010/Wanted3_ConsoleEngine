#include "DemoLevel.h"
#include "TestActor.h"
#include <iostream>

DemoLevel::DemoLevel()
{
	AddActor(new TestActor());

	// �׽�Ʈ�� �� ���� �б�.
	FILE* file = nullptr;
	fopen_s(&file, "../Assets/Map.txt", "rb");

	// ���� ó��.
	if (file == nullptr)
	{
		std::cout << "Failed to open Map.txt file.\n";
		__debugbreak();
		return;
	}

	// ���� ũ�� Ȯ��.
	// ���� ��ġ(File Position) Ŀ���� ���� ������ �̵�.
	fseek(file, 0, SEEK_END);
	
	// �̵��� ������ ��ġ ��ȯ.
	size_t fileSize = ftell(file);

	// ���� ��ġ Ŀ�� �ǵ�����.
	//fseek(file, 0, SEEK_SET);
	rewind(file);

	// ������ ������ ���� ���� �Ҵ�.
	//char* buffer = new char[fileSize + 1];
	char buffer[256] = { };

	// ���� ����������� �ݺ�.
	while (!feof(file))
	{
		// �� �پ� �б�.
		fgets(buffer, 256, file);

		// �� �� ���ڿ��� ���̰� ���ϱ�.
		int lineLength = (int)strlen(buffer);

		// �Ľ�(Parcing, �ؼ�).
		for (int ix = 0; ix < lineLength; ++ix)
		{
			char mapCharacter = buffer[ix];

			switch (mapCharacter)
			{
			case '#':
				std::cout << '#';
				break;
			case '.':
				std::cout << '.';
				break;
			case 'p':
				std::cout << 'p';
				break;
			case 'b':
				std::cout << 'b';
				break;
			case 't':
				std::cout << 't';
				break;
			}
		}

		// ����(����).
		std::cout << "\n";
	}

	// ���� �ݱ�.
	fclose(file);
}