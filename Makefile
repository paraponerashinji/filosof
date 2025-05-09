NAME= philo
NAME_BONUS= philo_bonus
CC= cc
CFLAGS = -Wall -Wextra -Werror
SRCS=		src/main.c\
			src/init.c\
			src/simulation.c\
			src/utils.c\
			src/print.c\
			src/simulation_utils.c\
			src/lib_utils.c\
			src/lib_more_utils.c
SRCS_BONUS=	src_bonus/main.c\
			src_bonus/init.c\
			src_bonus/routine.c\
			src_bonus/lib_more_utils.c\
			src_bonus/lib_utils.c
OBJS= $(SRCS:.c=.o)
OBJS_BONUS= $(SRCS_BONUS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
$(NAME_BONUS): $(LIBFT) $(OBJS_BONUS)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)
fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
bonus: $(NAME_BONUS)
all: $(NAME)
re: fclean all
.PHONY: clean fclean all re bonus
