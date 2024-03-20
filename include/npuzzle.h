#ifndef NPUZZLE_H
# define NPUZZLE_H
# define INV_ARG_MSG "Wrong number of arguments\n"
# define INV_FD_MSG "Bro gimme normal file\n"
# define INV_INPUT_MSG "Grid is not solvable\n"

# define INV_ARG_FLAG 1
# define INV_FD_FLAG 2
# define INV_INPUT_FLAG 3

# define UP 1
# define DOWN 2
# define LEFT 4
# define RIGHT 8

# define DEPTH_LIMIT 50
# define HEAP_LIMIT_3 17000
# define HEAP_LIMIT_4 30000000

# define HASH_SIZE_3 17000
# define HASH_SIZE_4 300000
# define OFFSET_BASIS_32  2166136261
# define FNV_PRIME_32  16777619

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

extern int		table_size;

typedef struct s_queue
{
	struct s_queue	*next;
	struct s_queue	*prev;
	int				prev_oper;//everything can be changed to char
	int				heuristic;
	int				empty_x;
	int				empty_y;
	int				depth;
	int				**arr;
}	t_queue;

typedef t_queue t_heap;

//heuristics.c
int	get_inversion_arr(int **arr);
int	get_manhattan_distance(int **arr, int y, int x);
int	get_manhattan_arr(int **arr);
int	change_inversion(int **arr, int empty_x, int empty_y, int swap_x, int swap_y);

//utils.c
void	print_arr(int **arr);
void	parse_input(char *filename, t_queue *root);

//heap.c
void	free_arr(int **arr);
void	print_heap(t_heap **heap, int heap_size);
void	exit_search(t_queue	**heap, t_heap **hashmap);
t_heap	*copy_state(t_heap *old, int operation);
void	change_state(t_heap *new, int operation);
int	check_heap(t_heap **heap, int heap_size);
void	insert_node(t_heap **heap, t_heap *new, int heap_size);
void	delete_root(t_heap **heap, int heap_size);
int		insert_hashmap(t_heap *temp, t_heap **hashmap);
void	generate_next_state(t_heap *temp, t_heap **heap, t_heap **hashmap, int *heap_size, int heap_limit, int operation);
void	search_path(t_heap *root);

//hashtable.c
uint32_t	hash(int **arr);
int	check_double(t_heap *traverse, int **arr);

//list.c
//void	free_arr(int **arr);
//void	print_queue(t_queue *root);
//void	exit_search(t_queue	*end);
//void	change_state(t_queue *new, int operation);
//t_queue *copy_node(t_queue *old, int operation);
//void	add_node(t_queue **queue, int operation);
//void	search_path(t_queue *root);

#endif