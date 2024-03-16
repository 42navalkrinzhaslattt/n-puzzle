#include "npuzzle.h"

//len(B) = 1 or n - 1
//A|x|B|y|C
//A|y|B|x|C
//x|B|	|B|x
//xy   ->  yx
//|B|y	y|B|
//parity changes with each swap
//if add parity of manhatan distance of empty, parity is invariant
//ADD FORK mb not
//check stats with list and replace to array


void	exit_search(t_queue	*end, t_data *data)
{
	print_state(end->state, data->table_size);
	exit(0);
}

t_state	*copy_state(t_state *state, int size)
{
	int		*new_arr;
	int		*old_arr;
	t_state	*res;

	res = malloc(sizeof(t_state));
	res->empty = state->empty;
	new_arr = malloc(size * sizeof(int));
	old_arr = state->arr;
	while (--size >= 0)
		new_arr[size] = old_arr[size];
	res->arr = new_arr;
	return (res);
}

void	change_state(t_queue *new_node, t_queue *parent, int operation, int size)
{
	int	temp;
	int	old;

	printf("empty = %d\n operation = %d\n",new_node->state->empty, operation);
	old = get_manhattan_distance(new_node->state, new_node->state->empty, size) + get_manhattan_distance(new_node->state, new_node->state->empty + operation, size);
	temp = new_node->state->arr[new_node->state->empty];
	new_node->state->arr[new_node->state->empty] = new_node->state->arr[new_node->state->empty + operation];
	new_node->state->arr[new_node->state->empty + operation] = temp;
	new_node->state->empty += operation;
	printf("distance before = %d\n", parent->heuristic);
	new_node->heuristic = parent->heuristic + get_manhattan_distance(new_node->state, new_node->state->empty, size) + get_manhattan_distance(new_node->state, new_node->state->empty - operation, size) - old;//+ 1
	printf("distance = %d\n", new_node->heuristic);
}

void	add_node(t_queue **queue, t_data *data, int operation)
{
	t_queue	*new_node;
	t_queue	*temp;

	new_node = malloc(sizeof(t_queue));
	new_node->prev = *queue;
	new_node->prev_oper = operation;
	new_node->state = copy_state((*queue)->state, data->table_size);
	new_node->next = NULL;
	change_state(new_node, *queue, operation, data->table_size);
	temp = *queue;
	while (temp->next && new_node->heuristic > temp->next->heuristic)
		temp = temp->next;
	if (temp->next)
	{
		new_node->next = temp->next;
		temp->next = new_node;
	}
	else
		temp->next = new_node;
	data->nb_state_curr++;
	if (data->nb_state_max < data->nb_state_curr)
		data->nb_state_max++;
	data->nb_state_total++;
}

void	search_path(t_state *state, t_data *data)
{
	static t_queue *queue;

	if (!queue)
	{
		queue = malloc(sizeof(t_queue));
		queue->prev = NULL;
		queue->prev_oper = 0;
		queue->state = state;
		queue->next = NULL;
		queue->heuristic = get_manhattan_state(state, data->table_size);
		data->nb_state_curr = 1;
		data->nb_state_max = 1;
		data->nb_state_total = 1;
	}
	while (queue->heuristic != 0)		//if (get_manhattan_state(state, data->table_size) == 0)
	{
		//can be changed to bitmasking
		if (queue->prev_oper != data->table_size && queue->state->empty > data->table_size - 1)//up
			add_node(&queue, data, -data->table_size);
		if (queue->prev_oper != -data->table_size && queue->state->empty < data->table_size * (data->table_size - 1))//down
			add_node(&queue, data, data->table_size);
		if (queue->prev_oper != 1 && queue->state->empty % data->table_size != 0)//left
			add_node(&queue, data, -1);
		if (queue->prev_oper != -1 && queue->state->empty % data->table_size != data->table_size - 1)//right
			add_node(&queue, data, 1);
		queue = queue->next;//states can be deleted, only operations matters
	}
	exit_search(queue, data);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_state	*root;

	if (ac != 2)
		exit((write(2, INV_ARG_MSG, 26), INV_ARG_FLAG));
	root = parse_input(av[1], &data);
	print_state(root, data.table_size);
	if ((get_inversions(root, data.table_size) + get_manhattan_distance(root, root->empty, data.table_size)) % 2 == 1)//can be optimized to O(n log n);
		exit((write(2, INV_INPUT_MSG, 21), INV_INPUT_FLAG));
	printf("manhattan distance of grid: %d\n", get_manhattan_state(root, data.table_size));
	search_path(root, &data);
}
