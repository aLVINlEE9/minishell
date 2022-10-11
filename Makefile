# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/06 12:17:29 by seungsle          #+#    #+#              #
#    Updated: 2022/10/11 19:12:49 by junhjeon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= cc -g -lreadline
CFLAG	=
SRCS 	=	./srcs/main.c		\
			./srcs/node_env.c	\
			./srcs/node_token.c	\
			./srcs/parse_env.c	\
			./srcs/parse_token_n.c\
			./srcs/utils.c\
			./srcs/pipex.c\
			./srcs/exe_cmd.c\
			./srcs/cmd.c\
			./srcs/iofile.c

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
