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

void	exit_search(t_queue	**heap, t_heap **hashmap)
{
//	t_heap *temp;
//	t_heap *next;
	t_heap *end;
	char	res[100];
	int		pos = 0;

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
		if (end->depth == 0)
			break ;
		end = end->prev;
	}
	while (--pos >= 0)
		putchar(res[pos]);
	putchar('\n');
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
