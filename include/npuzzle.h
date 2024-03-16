#ifndef NPUZZLE_H
# define NPUZZLE_H
# define INV_ARG_MSG "Wrong number of arguments\n"
# define INV_FD_MSG "Bro gimme normal file\n"
# define INV_INPUT_MSG "Grid is not solvable\n"

# define INV_ARG_FLAG 1
# define INV_FD_FLAG 2
# define INV_INPUT_FLAG 3

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//int	table_size;

typedef struct s_state
{
	int	*arr;
	int	empty;
}	t_state;

typedef struct s_queue
{
	struct s_queue	*next;
	struct s_queue	*prev;
	int				prev_oper;
	t_state			*state;
	int				heuristic;
}	t_queue;

typedef struct s_data
{
	int		table_size;
}	t_data;

int	get_inversions(t_state *state, int size);
int	get_manhattan_distance(t_state *state, int index, int size);
int	get_manhattan_state(t_state *state, int size);

void	print_state(t_state *state, int size);
t_state	*parse_input(char *filename, t_data *data);
int		get_inversions(t_state *state, int size);

#endif