#include "npuzzle.h"


int	hash(int *arr, int size)
{
	int	i;
	int	j;
	int	sum;
	int	count;
	static int	*fact;

	if (!fact)
	{
		fact = malloc(size * sizeof(int));
		i = 0;
		fact[0] = 1;
		while (++i < size)
			fact[i] = i * fact[i - 1];
	}
	i = -1;
	sum = 0;
	while (++i < size)
	{
		j = i;
		count = 0;
		while (++j < size)
			if (arr[i] > arr[j])
				count++;
		sum += count * fact[size - i - 1];
	}
	return (sum);
}
