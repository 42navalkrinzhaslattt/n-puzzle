#ifndef NPUZZLE_H
# define NPUZZLE_H
# define INV_ARG_MSG "Wrong number of arguments\n"
# define INV_FD_MSG "Bro gimme normal file\n"
# define INV_INPUT_MSG "Grid is not solvable\n"

# define INV_ARG_FLAG 1
# define INV_FD_FLAG 2
# define INV_INPUT_FLAG 3

#define UP 1
#define DOWN 2
#define LEFT 4
#define RIGHT 8

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int		table_size;

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

int	get_inversions(int **arr);
int	get_manhattan_distance(int **arr, int y, int x);
int	get_manhattan_arr(int **arr);

void	print_arr(int **arr);
void	parse_input(char *filename, t_queue *root);

#endif