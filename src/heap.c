#include "npuzzle.h"

void	free_arr(int **arr)
{
	for (int i = 0; i < table_size; i++)
	{
		free(arr[i]);
	}
	free(arr);
}

void	exit_search(t_queue	*end, t_queue *root, int heap_size)
{
	t_queue *temp;

	print_arr(end->arr);
	printf("SOLUTION!!!!!!!!!!\n");
	while (end->depth >= 0)
	{
//		print_arr(end->arr);
		if (end->prev_oper & UP)
			printf("UP\n");
		else if (end->prev_oper & DOWN)
			printf("DOWN\n");
		else if (end->prev_oper & RIGHT)
			printf("RIGHT\n");
		else if (end->prev_oper & LEFT)
			printf("LEFT\n");
		if (end->depth == 0)
			break ;
		end = end->prev;
	}
	printf("SOLUTION ENDS\n");
	while (root)
	{
		temp = root->next;
		free_arr(root->arr);
		free(root);
		root = temp;
	}
	for (int i = 0; i < heap_size; i++)
	{
		free_arr((end + i)->arr);
		free(end + i);
	}
	exit(0);
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

void	insert_node(t_heap **heap, t_heap *new, int heap_size)
{
	int		new_index;

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

	index = 0;
	heap[0] = heap[heap_size - 1];
	if (heap[2 * index + 1]->heuristic + heap[2 * index + 1]->depth < heap[2 * index + 2]->heuristic + heap[2 * index + 2]->depth)
		child_flag = 1;
	else
		child_flag = 2;
	while (heap[index]->heuristic + heap[index]->depth > heap[2 * index + child_flag]->heuristic + heap[2 * index + child_flag]->depth)
	{
		heap[index] = heap[2 * index + child_flag];
		index = 2 * index + child_flag;
		heap[index] = heap[heap_size];
		if (heap[2 * index + 1]->heuristic + heap[2 * index + 1]->depth < heap[2 * index + 2]->heuristic + heap[2 * index + 2]->depth)
			child_flag = 1;
		else
			child_flag = 2;
	}
}

void	search_path(t_heap *root)
{
	t_heap	*heap[HEAP_SIZE];
	t_heap	*traverse = NULL;
	t_heap	*next_state;
	int		heap_size = 0;
	int i = 0;

	heap[0] = root;
	++heap_size;
	while (heap[0]->heuristic != 0)
	{
//		printf("queue on %d iteration\n\n", i);
//		print_queue(queue);
//		printf("queue ends\n\n");
		if (!(heap[0]->prev_oper & DOWN) && heap[0]->empty_y != 0)
		{
			next_state = copy_state(heap[0], UP);
			change_state(next_state, UP);
			insert_node(heap, next_state, heap_size);
			++heap_size;
		}
		if (!(heap[0]->prev_oper & UP) && (heap[0]->empty_y != table_size - 1))
		{
			next_state = copy_state(heap[0], DOWN);
			change_state(next_state, DOWN);
			insert_node(heap, next_state, heap_size);
			++heap_size;
		}
		if (!(heap[0]->prev_oper & RIGHT) && heap[0]->empty_x != 0)
		{
			next_state = copy_state(heap[0], LEFT);
			change_state(next_state, LEFT);
			insert_node(heap, next_state, heap_size);
			++heap_size;
		}
		if (!(heap[0]->prev_oper & LEFT) && (heap[0]->empty_x != table_size - 1))
		{
			next_state = copy_state(heap[0], RIGHT);
			change_state(next_state, RIGHT);
			insert_node(heap, next_state, heap_size);
			++heap_size;
		}
		if (!traverse)
			traverse = root;
		else
		{
			traverse->next = heap[0];
			traverse = traverse->next;// start is in the root

		}
		delete_root(heap, heap_size);
		--heap_size;
		i++;
	}
	exit_search(heap[0], root, heap_size);
}
