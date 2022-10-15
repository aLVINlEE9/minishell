# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/06 12:17:29 by seungsle          #+#    #+#              #
#    Updated: 2022/10/15 17:38:15 by seungsle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= cc -g -lreadline -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include
CFLAG	= 
SRCS 	=	./srcs/main.c			\
			./srcs/node_env.c		\
			./srcs/node_token.c		\
			./srcs/parse_env.c		\
			./srcs/parse_token_2.c	\
			./srcs/utils.c			\
			./srcs/pipex.c			\
			./srcs/exe_cmd.c		\
			./srcs/cmd.c			\
			./srcs/iofile.c			\
			./srcs/set_terminal.c	\
			./srcs/set_signal.c

OBJS 	= ${SRCS:.c=.o}

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o $(NAME)

.c.o:
	$(CC) $(CFLAG) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : 
	make fclean
	make all

.PHONY: all clean fclean re
