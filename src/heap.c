#include "npuzzle.h"

void	free_arr(int **arr)
{
	for (int i = 0; i < table_size; i++)
	{
		free(arr[i]);
	}
	free(arr);
}


void	print_heap(t_heap **heap, int heap_size)
{
	for (int k = 0; k < heap_size; k++)
	{
		for (int i = 0; i < table_size; i++)
		{
			for (int m = 0; m < heap[k]->depth; m++)
			{
				printf("\t");
			}
			for (int j = 0; j < table_size; j++)
			{
				printf("%d", heap[k]->arr[i][j]);
				if (j != table_size - 1)
					printf(" ");
			}
			printf("\n");
		}
		for (int m = 0; m < heap[k]->depth; m++)
		{
			printf("\t");
		}
		printf("priority = %d + %d\n", heap[k]->heuristic, heap[k]->depth);
	}
}



t_heap	*copy_state(t_heap *old, int operation)
{
	t_heap *new_node;

	new_node = malloc(sizeof(t_heap));
	new_node->next = NULL;
	new_node->prev = old;
	new_node->prev_oper = operation;
	new_node->heuristic = old->heuristic;
	new_node->empty_y = old->empty_y;
	new_node->empty_x = old->empty_x;
	new_node->depth = old->depth + 1;
	new_node->arr = malloc(table_size * sizeof(int*));
	for (int i = 0; i < table_size; i++)
	{
		new_node->arr[i] = malloc(table_size * sizeof(int));
	}
	for (int i = 0; i < table_size; i++)
	{
		for (int j = 0; j < table_size; j++)
		{
			new_node->arr[i][j] = old->arr[i][j];
		}
	}
	return (new_node);
}

void	change_state(t_heap *new, int operation)
{
	int	old_distance;
	int	x_empty;
	int	y_empty;
	int	x_swap;
	int	y_swap;
	int	**arr;

	x_empty = new->empty_x;
	y_empty = new->empty_y;
	x_swap = x_empty;
	y_swap = y_empty;
	if (operation & UP)
		--y_swap;
	else if (operation & DOWN)
		++y_swap;
	else if (operation & LEFT)
		--x_swap;
	else
		++x_swap;
	arr = new->arr;
	old_distance = get_manhattan_distance(arr, y_empty, x_empty) + get_manhattan_distance(arr, y_swap, x_swap);
	arr[y_empty][x_empty] = arr[y_swap][x_swap];
	arr[y_swap][x_swap] = table_size * table_size;
	new->empty_x = x_swap;
	new->empty_y = y_swap;
	new->heuristic += get_manhattan_distance(arr, y_empty, x_empty) + get_manhattan_distance(arr, y_swap, x_swap) - old_distance;
}

void print_grid(int **grid, int size, WINDOW *win)
{
	int lin = 0, col = 0;
	static int	save[2];

	if (COLS < 42 || LINES < 30)
	{
		mvwprintw(win, 0, 0, "WINDOW IS TOO SMOL:(");
		wrefresh(win);
		return ;
	}
	for (int i = 0; i < size; i++)
	{
		lin = 4 * i + LINES / 2 - 4 * size / 2;
		for (int j = 0; j < size; j++)
		{
			col = 6 * j + COLS / 2 - 4 * size / 2;
			if (j == 0)
				mvwprintw(win, lin, col - 3, "|");
			for (int k = 0; k < size - 1; k++)
			{
				mvwprintw(win, lin - 2, col - 1 + k, "-");
			}
//                      init_pair(1, COLOR_RED, COLOR_BLACK);
//                      wattron(win, COLOR_PAIR(1));
			// mvwprintw(win, 5 * i + LINES / 2 - 5 * size / 2, 5 * j + COLS / 2 - 5 * size / 2, "%i", grid[i][j]);
//			wattron(win, COLOR_PAIR(1));
			mvwprintw(win, 4 * i + LINES / 2 - 4 * size / 2, 6 * j + COLS / 2 - 4 * size / 2, "%i", grid[i][j]);
			if (grid[i][j] == 9)
			{
				mvwprintw(win, 4 * i + LINES / 2 - 4 * size / 2 - 1, 6 * j + COLS / 2 - 4 * size / 2, "-");
				mvwprintw(win, 4 * i + LINES / 2 - 4 * size / 2 + 1, 6 * j + COLS / 2 - 4 * size / 2, "-");
				mvwprintw(win, 4 * i + LINES / 2 - 4 * size / 2, 6 * j + COLS / 2 - 4 * size / 2 - 1, "|");
				mvwprintw(win, 4 * i + LINES / 2 - 4 * size / 2, 6 * j + COLS / 2 - 4 * size / 2 + 1, "|");
				if (save[0])
				{
					mvwprintw(win, save[0] - 1, save[1], " ");
					mvwprintw(win, save[0] + 1, save[1], " ");
					mvwprintw(win, save[0], save[1] - 1, " ");
					mvwprintw(win, save[0], save[1] + 1, " ");
				}
				save[0] = 4 * i + LINES / 2 - 4 * size / 2;
				save[1] = 6 * j + COLS / 2 - 4 * size / 2;
			}
//                      wattroff(win, COLOR_PAIR(1));
			// if (j < size - 1)
//			wattroff(win, COLOR_PAIR(1));
			mvwprintw(win, lin, col + 3, "|");
		}
	}
	for (int l = 0; l < size; l++) {
		col = 6 * l + COLS / 2 - 4 * size / 2;
		for (int k = 0; k < size - 1; k++)
		{
			mvwprintw(win, lin + 2, col - 1 + k, "-");
		}
	}
	wrefresh(win);
}

int	**costyl(int **arr, int flag)
{
	int	**new = malloc(table_size * sizeof(int*));

	for (int i = 0; i < table_size; i++)
		new[i] = malloc(table_size * sizeof(int));
	for (int i = 0; i < table_size; i++)
	{
		for (int j = 0; j < table_size; j++)
		{
			new[i][j] = arr[i][j];
		}
	}
	if (flag == 'u')
	{
		new[table_size - 1][table_size - 1] = new[table_size - 2][table_size - 1];
		new[table_size - 2][table_size - 1] = table_size * table_size;
	}
	else if (flag == 'l')
	{
		new[table_size - 1][table_size - 1] = new[table_size - 1][table_size - 2];
		new[table_size - 1][table_size - 2] = table_size * table_size;
	}
	return (new);
}

void	exit_search(t_queue	**heap, t_heap **hashmap)
{
//	t_heap *temp;
//	t_heap *next;
	t_heap *end;
	t_heap *save[10000];
	char	res[100];
	int		pos = 0;
	WINDOW	*win;

	initscr();
	win = newwin(100, 100, 0, 0);
	cbreak();
	noecho();
	curs_set(0);
	set_escdelay(0);
	keypad(win, TRUE);
	end = heap[0];
	while (end->depth >= 0)
	{
		if (end->prev_oper & UP)
			res[pos++] = 'u';
		else if (end->prev_oper & DOWN)
			res[pos++] = 'd';
		else if (end->prev_oper & RIGHT)
			res[pos++] = 'r';
		else if (end->prev_oper & LEFT)
			res[pos++] = 'l';
		save[pos - 1] = end;
		if (end->depth == 0)
			break ;
		end = end->prev;
	}
	int	save_pos = pos;
	--pos;
	print_grid(save[pos]->arr, table_size, win);
//	print_arr(save[pos]->arr);
	usleep(1000000);
//	print_arr(costyl(save[pos]->arr, res[pos]));
	print_grid(costyl(save[pos]->arr, res[pos]), table_size, win);
	usleep(1000000);

	while (--pos >= 0)
	{
//		print_arr(save[pos]->arr);
//		putchar(res[pos]);
		print_grid(save[pos]->arr, table_size, win);
//		putchar('\n');
		usleep(1000000);
	}
	delwin(win);
	endwin();
	while (--save_pos >= 0)
	{
		putchar(res[save_pos]);
	}
//	putchar('\n');
	free(hashmap);
	free(heap);
	exit(0);
//	for (int i = 0; i < HASH_SIZE_3; i++)
//	{
//		temp = hashmap[i];
//		while (temp)
//		{
//			next = temp->next;
//			free_arr(temp->arr);
//			free(temp);
//			temp = next;
//		}
//	}
//	free(hashmap);
//	free(heap);
//	exit(0);
}

int	check_heap(t_heap **heap, int heap_size)
{
	for (int i = 0; 2 * i + 1 < heap_size; i++)
	{
		if (heap[i]->heuristic + heap[i]->depth > heap[2 * i + 1]->heuristic + heap[2 * i + 1]->depth
			|| ((2 * i + 2 < heap_size) &&heap[i]->heuristic + heap[i]->depth > heap[2 * i + 2]->heuristic + heap[2 * i + 2]->depth))
			return (0);
	}
	return (1);
}

void	insert_node(t_heap **heap, t_heap *new, int heap_size)
{
	int		new_index;

	if (heap_size == 0)
	{
		heap[0] = new;
		return ;
	}
	new_index = heap_size;
	heap[new_index] = new;
	while (heap[(new_index - 1) / 2]->heuristic + heap[(new_index - 1) / 2]->depth > new->heuristic + new->depth)
	{
		heap[new_index] = heap[(new_index - 1) / 2];
		heap[(new_index - 1) / 2] = new;
		new_index = (new_index - 1) / 2;
	}
}

void	delete_root(t_heap **heap, int heap_size)
{
	int		index;
	int		child_flag;

	if (heap_size == 1)
		return ;
	index = 0;
	heap[0] = heap[heap_size - 1];
	if (2 * index + 2 < heap_size - 1)
	{
		if (heap[2 * index + 1]->heuristic + heap[2 * index + 1]->depth <
			heap[2 * index + 2]->heuristic + heap[2 * index + 2]->depth)
			child_flag = 1;
		else
			child_flag = 2;
	}
	while (2 * index + 2 < heap_size - 1 &&  heap[index]->heuristic + heap[index]->depth > heap[2 * index + child_flag]->heuristic + heap[2 * index + child_flag]->depth)
	{
		heap[index] = heap[2 * index + child_flag];
		index = 2 * index + child_flag;
		heap[index] = heap[heap_size - 1];
		if (2 * index + 2 >= heap_size - 1)
			break ;
		if (heap[2 * index + 1]->heuristic + heap[2 * index + 1]->depth < heap[2 * index + 2]->heuristic + heap[2 * index + 2]->depth)
			child_flag = 1;
		else
			child_flag = 2;
	}
	if (2 * index + 1 < heap_size - 1 && heap[index]->heuristic + heap[index]->depth > heap[2 * index + 1]->heuristic + heap[2 * index + 1]->depth)
	{
		heap[index] = heap[2 * index + 1];
		index = 2 * index + 1;
		heap[index] = heap[heap_size - 1];
	}
}

int		insert_hashmap(t_heap *temp, t_heap **hashmap)
{
	int	hash_index;
	int	counter;
	t_heap	*ptr;

	hash_index = hash(temp->arr);
	ptr = hashmap[hash_index];
	if (!ptr)
	{
		hashmap[hash_index] = temp;
		return (1);
	}
	while (ptr)
	{
//		if (temp == ptr)
//		{
//			print_arr(temp->arr);
//			printf("pidor\n");
//			exit(0);
//		}
		counter = 0;
		if (temp != ptr)
		{
			for (int i = 0; i < table_size; i++)
			{
				for (int j = 0; j < table_size; j++)
				{
					if (temp->arr[i][j] == ptr->arr[i][j])
						counter++;
				}
				if (counter == table_size * table_size)
					return (0);
			}
		}
		if (!ptr->next)
		{
			ptr->next = temp;
			break ;
		}
		ptr = ptr->next;
	}
	return (1);
}

void	generate_next_state(t_heap *temp, t_heap **heap, t_heap **hashmap, int *heap_size, int heap_limit, int operation)
{
	t_heap *next_state;

	if (*heap_size == heap_limit - 1)
	{
		printf("HEAP SIZE IS NOT ENOUGH\n");
		exit (0);
	}
	next_state = copy_state(temp, operation);
	change_state(next_state, operation);
	if (next_state->heuristic == 0)
	{
		heap[*heap_size] = heap[0];
		heap[0] = next_state;
		exit_search(heap, hashmap);
	}
	if (insert_hashmap(next_state, hashmap))
	{
		insert_node(heap, next_state, *heap_size);
		++(*heap_size);
	}
	else
	{
		free_arr(next_state->arr);
		free(next_state);
	}
}

void	search_path(t_heap *root)
{
	t_heap	**heap;
	t_heap	**hashmap = NULL;
	t_heap	*temp;
	int		heap_size = 0;
	int		heap_limit = 0;
	int		i = 0;

	if (table_size == 3)
	{
		heap_limit = HEAP_LIMIT_3;
		hashmap = calloc(HASH_SIZE_3, sizeof(t_heap*));
	}
	else
	{
		heap_limit = HEAP_LIMIT_4;
		hashmap = calloc(HASH_SIZE_4, sizeof(t_heap*));
	}
	heap = malloc(heap_limit * sizeof(t_heap*));
	heap[0] = root;
	++heap_size;
	insert_hashmap(heap[0], hashmap);
	while (heap[0]->heuristic != 0)
	{
		i++;
		temp = heap[0];
		delete_root(heap, heap_size);
		--heap_size;
		if (!(temp->prev_oper & DOWN) && temp->empty_y != 0)
			generate_next_state(temp, heap, hashmap, &heap_size, heap_limit, UP);
		if (!(temp->prev_oper & UP) && (temp->empty_y != table_size - 1))
			generate_next_state(temp, heap, hashmap, &heap_size, heap_limit, DOWN);
		if (!(temp->prev_oper & RIGHT) && temp->empty_x != 0)
			generate_next_state(temp, heap, hashmap, &heap_size, heap_limit, LEFT);
		if (!(temp->prev_oper & LEFT) && (temp->empty_x != table_size - 1))
			generate_next_state(temp, heap, hashmap, &heap_size, heap_limit, RIGHT);
	}
	exit_search(heap, hashmap);
}
