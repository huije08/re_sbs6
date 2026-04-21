#include <stdio.h>
#include <Windows.h>

enum ColorType
{
	BLACK,
	DARKBLUE,
	DARKGREEN,
	DARKSKYBLUE,
	DARKRED,
	DARKPURPLE,
	DARKYELLOW,
	GRAY,
	DARKGRAY,
	BLUE,
	GREEN,
	SKYBLUE,
	RED,
	PURPLR,
	YELLOW,
	WHITE
};
enum State
{
	IDLE = 99,
	ATTACK,
	DIE

	//열거형은 값을 따로 설정할 수 있으며, 설정된 다음 값은
	// 그 전의 값에서 하나 증가된 값으로 설정됩니다.
};

void convert(enum State state)
{
	switch (state)
	{
	case IDLE:
		printf("Idle\n");
		break;
	case ATTACK:
		printf("Attack\n");
		break;
	case DIE:
		printf("Die\n");
		break;
	default:
		printf("Exception\n");
		break;
	}
}

int main()
{
#pragma region 열거형
	//관련된 상수의 갓을 이름으로 정의한 집합의 자료형

	// enum State state=IDLE;
	// printf("Enter a status:");
	// scanf_s("%d", &state);
	// printf("\n");
	// convert(state);
#pragma endregion

	int size = WHITE;
	for (int i = 0; i < size; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);

		if (i != 0 && i % 3 == 0)
		{
			system("pause");
		}
		printf("colorindex : %d\n", i);
	}




	return 0;
}