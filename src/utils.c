#include "npuzzle.h"

void	print_state(t_state *state, int size)
{
	int	*arr;

	arr =state->arr;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printf("%d", arr[i * size + j]);
			if (j != size - 1)
				printf(" ");
		}
		printf("\n");
	}
//	printf("empty at %d\n", state->empty);
}

t_state	*parse_input(char *filename, t_data *data)
{
	char	buf[1000];
	char	*ptr;
	int		fd;
	t_state	*res;

	if ((fd = open(filename, O_RDONLY)) == -1)
		exit((write(2, INV_FD_MSG, 22), INV_FD_FLAG));
	res = malloc(sizeof(t_state));
	buf[read(fd, buf, 999)] = 0;
	data->table_size = atoi(buf);
	res->arr = malloc((data->table_size * data->table_size) * sizeof(int));
	ptr = strchr(buf, '\n') + 1;
	for (int i = 0; i < data->table_size; i++)
	{
		for (int j = 0; j < data->table_size; j++)
		{
			if (atoi(ptr) == 0 || atoi(ptr) == data->table_size * data->table_size)
			{
				res->empty = i * data->table_size + j;
				res->arr[res->empty] = data->table_size * data->table_size;
			}
			else
				res->arr[i * data->table_size + j] = atoi(ptr);
			if (j != data->table_size - 1)
				ptr = strchr(ptr, ' ') + 1;
		}
		ptr = strchr(ptr, '\n') + 1;
	}
	data->nb_state_total = 0;
	data->nb_state_max = 0;
	data->nb_state_curr = 0;
	return (res);
}