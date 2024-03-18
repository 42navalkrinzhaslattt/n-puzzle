#include "npuzzle.h"
int table_size = 0;
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

int	main(int ac, char **av)
{
	t_queue	*root;

	if (ac != 2)
		exit((write(2, INV_ARG_MSG, 26), INV_ARG_FLAG));
	root = malloc(sizeof(t_queue));
	root->next = NULL;
	root->prev = NULL;
	root->prev_oper = 0;
	root->depth = 0;
	parse_input(av[1], root);
	root->heuristic = get_manhattan_arr(root->arr);
	if ((get_inversion_arr(root->arr) + get_manhattan_distance(root->arr, root->empty_y, root->empty_x)) % 2 == 1)//can be optimized to O(n log n);
		exit((write(2, INV_INPUT_MSG, 21), INV_INPUT_FLAG));
	search_path(root);
}
