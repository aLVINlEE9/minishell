# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/06 12:17:29 by seungsle          #+#    #+#              #
#    Updated: 2022/10/09 23:11:18 by seungsle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= cc -g -lreadline
CFLAG	= -Werror -Wall -Wextra
SRCS 	=	./srcs/main.c		\
			./srcs/node_env.c	\
			./srcs/node_token.c	\
			./srcs/parse_env.c	\
			./srcs/parse_token_n.c\
			./srcs/utils.c

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