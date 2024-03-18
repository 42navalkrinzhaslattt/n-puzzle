#include "npuzzle.h"

void	free_arr(int **arr)
{
	for (int i = 0; i < table_size; i++)
	{
		free(arr[i]);
	}
	free(arr);
}

void	print_queue(t_queue *root)
{
	static int iteration;

	while (root)
	{
		print_arr(root->arr);
		printf("distance is %d + %d\n", root->heuristic, root->depth);
		root = root->next;
	}
	if (iteration == 2)
		exit(0);
	iteration++;
}

void	exit_search(t_queue	*end)
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
	while (end)
	{
		temp = end->next;
		free_arr(end->arr);
		free(end);
		end = temp;
	}
	exit(0);
}

void	change_state(t_queue *new, int operation)
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


t_queue *copy_node(t_queue *old, int operation)
{
	t_queue *new_node;

	new_node = malloc(sizeof(t_queue));
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

void	add_node(t_queue **queue, int operation)
{
	t_queue	*new_node;
	t_queue	*temp;

	new_node = copy_node(*queue, operation);
	change_state(new_node, operation);
	if (new_node->heuristic == 0)
	{
		new_node->next = (*queue)->next;
		(*queue)->next = new_node;
		exit_search(new_node);
		return ;
	}
	temp = *queue;
	while (temp->next && new_node->heuristic + new_node->depth > temp->next->heuristic + temp->next->depth)
		temp = temp->next;
	if (temp->next)
	{
		new_node->next = temp->next;
		temp->next = new_node;
	}
	else
		temp->next = new_node;
//	print_arr(new_node->arr);
//	printf("new distance is %d + %d\n", new_node->heuristic, new_node->depth);
}

void	search_path(t_queue *root)
{
	t_queue *queue;
	int i	= 0;

	queue = root;
	while (queue->heuristic != 0)
	{
//		printf("queue on %d iteration\n\n", i);
//		print_queue(queue);
//		printf("queue ends\n\n");
		if (!(queue->prev_oper & DOWN) && queue->empty_y != 0)
			add_node(&queue, UP);
		if (!(queue->prev_oper & UP) && (queue->empty_y != table_size - 1))
			add_node(&queue, DOWN);
		if (!(queue->prev_oper & RIGHT) && queue->empty_x != 0)
			add_node(&queue, LEFT);
		if (!(queue->prev_oper & LEFT) && (queue->empty_x != table_size - 1))
			add_node(&queue, RIGHT);
		queue = queue->next;
		i++;
	}
	exit_search(queue);
}