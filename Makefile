SRC_FILES = pipex_error.c split_utils.c files.c init.c \
			ft_split_new.c main.c pipes.c exec.c paths.c
SRC_BONUS = pipex_error_bonus.c split_utils.c files_bonus.c \
			init_bonus.c ft_split_new.c main_bonus.c \
			pipes_bonus.c exec_bonus.c paths_bonus.c
HDR_BONUS = pipex_bonus.h
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

NAME = pipex
LIBFT = libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

all: $(LIBFT) $(NAME)

bonus: $(LIBFT) $(OBJ_BONUS)
			$(CC) $(OBJ_BONUS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft/

$(NAME): $(OBJ_FILES)
	${CC} ${CFLAGS} ${OBJ_FILES} ${LIBFT} -o ${NAME} -lft -Llibft

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	make clean -C ./libft
	rm -f $(OBJ_FILES)
	rm -f $(OBJ_BONUS)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

.PHONY: fclean all bonus clean
