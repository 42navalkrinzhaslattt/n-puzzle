NAME	= npuzzle

SRC		= main.c utils.c heuristics.c hashtable.c heap.c

SRC_DIR	= src/

OBJ	= $(addprefix $(SRC_DIR), $(SRC:.c=.o))

INC_DIR = include

CC		= cc

CFLAGS	= -Wall -Werror -Wextra

RM	= rm -f

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c  $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -O3 -g -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re