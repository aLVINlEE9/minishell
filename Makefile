# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/06 12:17:29 by seungsle          #+#    #+#              #
#    Updated: 2022/10/20 22:44:11 by junhjeon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
#CC		= cc -g -lreadline -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include
 CC		= cc -g -lreadline -L/Users/junhjeon/.brew/opt/readline/lib -I/Users/junhjeon/.brew/opt/readline/include
CFLAG	=
SRCS 	=	./srcs/main.c		\
			./srcs/node_env.c	\
			./srcs/node_token.c	\
			./srcs/parse_env.c	\
			./srcs/parse_token.c\
			./srcs/utils.c\
			./srcs/pipex.c\
			./srcs/exe_cmd.c\
			./srcs/cmd.c\
			./srcs/iofile.c\
			./srcs/set_terminal.c\
			./srcs/set_signal.c\
			./srcs/print.c\
			./srcs/parse_dol_jh.c\
			./srcs/parse_dol_jh2.c\
			./srcs/monitoring.c\
			./srcs/exe_cmd2.c\
			./srcs/make_cmdlst.c\
			./srcs/make_pipe_cmdlst.c\
			./srcs/make_pipe_cmdlst2.c\
			./srcs/built_in.c\
			./srcs/built_in2.c\
			./srcs/built_in3.c\
			./srcs/built_in4.c\
			./srcs/syntax_check.c\
			./srcs/env_manage.c\
			./srcs/set_signal_fork.c

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
