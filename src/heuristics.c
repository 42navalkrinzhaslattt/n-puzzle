#include "npuzzle.h"

int	get_inversion_arr(int **arr)
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

int	change_inversion(int **arr, int empty_x, int empty_y, int swap_x, int swap_y)
{
	int empty_res = 0;
	int swap_res = 0;

	if (empty_y < swap_y)
		empty_res += table_size;
	else
		empty_res -= table_size;
	if (empty_y < swap_y)
	{
		for (int i = empty_x + 1; i < table_size; i++)
		{
			if (arr[empty_y][i] > arr[swap_y][swap_x])
				++swap_res;
			else
				--swap_res;
		}
		for (int i = 0; i < swap_x; i++)
		{
			if (arr[swap_y][i] > arr[swap_y][swap_x])
				++swap_res;
			else
				--swap_res;
		}
	}
	else
	{
		for (int i = swap_x + 1; i < table_size; i++)
		{
			if (arr[swap_y][i] < arr[swap_y][swap_x])
				++swap_res;
			else
				--swap_res;
		}
		for (int i = 0; i < empty_x; i++)
		{
			if (arr[empty_y][i] < arr[swap_y][swap_x])
				++swap_res;
			else
				--swap_res;
		}
	}
	return (empty_res + swap_res);
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
