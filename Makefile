NAME	= philo

CFLAGS = -Wall -Wextra -Werror  

SRCS_NAMES = main.c \
			main_helpers.c \
			socrates.c \
			utils.c \
			nietzsche.c \

SRCS = $(addprefix srcs/, $(SRCS_NAMES))
OBJS = $(SRCS:c=o)

all		: $(NAME)

$(NAME): $(OBJS)
	cc -g3 $(OBJS) -o $(NAME)

%.o: srcs/%.c
	cc -g3 $(CFLAGS) -I -c $< -o $@

fclean	: clean
	rm -f $(NAME) 

clean:
	rm -f $(OBJS)

re		: fclean all

.PHONY: clean fclean all re
