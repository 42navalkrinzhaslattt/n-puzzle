#include "npuzzle.h"

void	print_arr(int **arr)
{
	for (int i = 0; i < table_size; i++)
	{
		for (int j = 0; j < table_size; j++)
		{
			printf("%d", arr[i][j]);
			if (j != table_size - 1)
				printf(" ");
		}
		printf("\n");
	}
//	printf("empty at %d\n", state->empty);
}

void	parse_input(char *filename, t_queue *data)
{
	char	buf[1000];
	char	*ptr;
	int		fd;
	int		**arr;

	if ((fd = open(filename, O_RDONLY)) == -1)
		exit((write(2, INV_FD_MSG, 22), INV_FD_FLAG));
	buf[read(fd, buf, 999)] = 0;
	ptr = buf;
	if (buf[0] < '0' || buf[0] > '9')
		ptr = strchr(buf, '\n') + 1;
	table_size = atoi(ptr);
	arr = malloc(table_size * sizeof(int**));
	for (int i = 0; i < table_size; i++)
	{
		arr[i] = malloc(table_size * sizeof(int));
	}
	ptr = strchr(ptr, '\n') + 1;
	for (int i = 0; i < table_size; i++)
	{
		for (int j = 0; j < table_size; j++)
		{
			if (atoi(ptr) == 0 || atoi(ptr) == table_size * table_size)
			{
				data->empty_y = i;
				data->empty_x = j;
				arr[i][j] = table_size * table_size;
			}
			else
				arr[i][j] = atoi(ptr);
			while (*ptr && *ptr >= '0' && *ptr <= '9')
				ptr++;
			while (*ptr && *ptr == ' ')
				ptr++;
		}
		ptr = strchr(ptr, '\n') + 1;
	}
	data->arr = arr;
}