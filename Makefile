CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

NAME		=	minitalk

SERVER		=	server

CLIENT		=	client

SRC_S		=	server.c

SRC_C		=	client.c

OBJ_S		=	$(SRC_S:.c=.o)

OBJ_C		=	$(SRC_C:.c=.o)

RM			=	rm -f

all:	$(SERVER) $(CLIENT)

$(SERVER):	$(OBJ_S)
	@make -s -C ./libft
	@$(CC) $(CFLAGS) -o $(SERVER) $(OBJ_S) ./libft/libft.a

$(CLIENT):	$(OBJ_C)
	@make -s -C ./libft
	@$(CC) $(CFLAGS) -o $(CLIENT) $(OBJ_C) ./libft/libft.a

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -s -C ./libft clean
	@$(RM) $(OBJ_S) $(OBJ_C)

fclean:	clean
	@make -s -C ./libft clean
	@$(RM) $(SERVER) $(CLIENT)

re:		fclean all

.PHONY:	all clean fclean re