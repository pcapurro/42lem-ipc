# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAME = 42lem-ipc

SRCS = srcs/main.c \
	srcs/help.c \
	srcs/heart/initialize.c \
	srcs/heart/routine.c \
	srcs/heart/map.c \
	srcs/heart/state.c \
	srcs/heart/move.c \
	srcs/heart/target.c \
	srcs/tools/library.c \
	srcs/tools/print.c \
	srcs/tools/tools.c \

CC = gcc

CFLAGS = -Wall -Wextra -Werror # -fsanitize=address -g

## == .C TO .O == ##

OBJS = $(SRCS:.c=.o)

## === RULES === ##

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS)

re: fclean all

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)
