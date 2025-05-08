NAME= philo
NAME_BONUS= philo_bonus
CC= cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFTDIR) -ggdb
SRCS=		src/main.c\
			src/init.c\
			src/simulation.c\
			src/utils.c\
			src/print.c
SRCS_BONUS=	src_bonus/main.c\
			src_bonus/init.c\
			src_bonus/routine.c
OBJS= $(SRCS:.c=.o)
OBJS_BONUS= $(SRCS_BONUS:.c=.o)
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
$(NAME_BONUS): $(LIBFT) $(OBJS_BONUS)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIBFT)
$(LIBFT):
	@make -C $(LIBFTDIR)
%.o:%.c
	$(CC) $(CFLAGS) $(LIBFT) -c $< -o $@
clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)
	@make clean -C $(LIBFTDIR)
fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	@make fclean -C $(LIBFTDIR)
bonus: $(NAME_BONUS)
all: $(NAME)
re: fclean all
.PHONY: clean fclean all re bonus
