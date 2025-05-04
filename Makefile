NAME= philo
CC= cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFTDIR) -ggdb
SRCS=		src/main.c\
			src/init.c\
			src/simulation.c\
			src/utils.c
OBJS= $(SRCS:.c=.o)
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
$(LIBFT):
	@make -C $(LIBFTDIR)
%.o:%.c
	$(CC) $(CFLAGS) $(LIBFT) -c $< -o $@
clean:
	rm -f $(OBJS)
	@make clean -C $(LIBFTDIR)
fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFTDIR)
all: $(NAME)
re: fclean all
.PHONY: clean fclean all re
