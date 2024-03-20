#include "npuzzle.h"

uint32_t	hash(int **arr)
{
	uint32_t	res = OFFSET_BASIS_32;

	for(int i = 0; i < table_size; i++)
	{
		for(int j = 0; j < table_size; j++)
		{
			res ^= (unsigned int)arr[i][j];
			res *= FNV_PRIME_32;
		}
	}
	res %= HASH_SIZE_3;
	return (res);
}

int	check_double(t_heap *traverse, int **arr)
{
	t_heap	*temp;
	int		counter;

	if (!traverse)
		return (1);
	temp = traverse;
	while (temp)
	{
		counter = 0;
		for (int i = 0; i < table_size; i++)
		{
			for (int j = 0; j < table_size; j++)
			{
				if (arr[i][j] == temp->arr[i][j])
					counter++;
			}
		}
		if (counter == table_size * table_size)
			return (0);
		temp = temp->next;
	}
	return (1);
}