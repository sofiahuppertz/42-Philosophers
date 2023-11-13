NAME	= philo

CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./headers

SRCS_NAMES = actions.c \
			atoi.c \
			end.c \
			ft_usleep.c \
			init.c \
			lifecycle.c \
			logs.c \
			main_helpers.c \
			main.c \
			monitor.c \
			start_simulation.c \

SRCS = $(addprefix srcs/, $(SRCS_NAMES))
OBJS = $(SRCS:c=o)

all		: $(NAME)

$(NAME): $(OBJS)
	cc $(OBJS) -lpthread -o $(NAME)

%.o: srcs/%.c
	cc -g $(CFLAGS) $(INCLUDES) -c $< -o $@

fclean	: clean
	rm -f $(NAME) 

clean:
	rm -f $(OBJS)

re		: fclean all

.PHONY: clean fclean all re