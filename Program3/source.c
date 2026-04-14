#include <stdio.h>


void shuffle(int array[], int size)
{
	int seed;
	int temp;

	for (int i = 0; i < size; i++)
	{
		seed = rand() % size;
		temp = array[i];
		array[i] = array[seed];
		array[seed] = temp;

	}

}

int main()
{
#pragma region 의사 난수
	// 0~32767사이의 난수값을 반환하는 함수

	// UTC기준으로 1970년 1월 1일 0시 0분 0초 부터 경과된
	// 시간을 초(sec)로 반환하는 함수입니다.

	// srand(time(NULL));
	// int random = rand() % 10 +1;
	// printf("%d", random);

#pragma endregion

#pragma region 셔플 함수
	int list[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	shuffle(list, 10);

	for (int i = 0; i < 10; i++)
	{
		printf("%d ", list[i]);
	}
#pragma endregion


	return 0;
}