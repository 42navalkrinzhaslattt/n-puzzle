#include "npuzzle.h"

int	get_inversions(t_state *state, int size)
{
	int	*arr;
	int	arr_size;
	int	res;

	res = 0;
	arr = state->arr;
	arr_size = size * size;
	for (int i = 0; i < arr_size; i++)
	{
		for (int j = i + 1; j < arr_size; j++)
		{
			if (arr[i] > arr[j])
				++res;
		}
	}
	return (res);
}

int	get_manhattan_distance(t_state *state, int index, int size)
{
	return (abs((state->arr[index] - 1) / size - index / size) + abs((state->arr[index] - 1) % size - index % size));
}

int	get_manhattan_state(t_state *state, int size)
{
	int	*arr;
	int	res;
	int	arr_size;

	res = 0;
	arr = state->arr;
	arr_size = size * size;
	for (int i = 0; i < arr_size; i++)
	{
		res += get_manhattan_distance(state, i, size);
	}
	return (res);
}
