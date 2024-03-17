#include "npuzzle.h"

int	get_inversions(int **arr)
{
	int	res;

	res = 0;
	for (int i1 = 0; i1 < table_size; i1++)
	{
		for (int j1 = 0; j1 < table_size; j1++)
		{
			for (int j3 = j1 + 1; j3 < table_size; j3++)
			{
				if (arr[i1][j1] > arr[i1][j3])
					++res;
			}
			for (int i2 = i1 + 1; i2 < table_size; i2++)
			{
				for (int j2 = 0; j2 < table_size; j2++)
				{
					if (arr[i1][j1] > arr[i2][j2])
						++res;
				}
			}
		}
	}
	return (res);
}

int	get_manhattan_distance(int **arr, int y, int x)
{
	return (abs((arr[y][x] - 1) / table_size -  y) + abs((arr[y][x] - 1) % table_size -  x));
}

int	get_manhattan_arr(int **arr)
{
	int	res;

	res = 0;
	for (int i = 0; i < table_size; i++)
	{
		for (int j = 0; j < table_size; j++)
		{
			res += get_manhattan_distance(arr, i, j);
		}
	}
	return (res);
}
