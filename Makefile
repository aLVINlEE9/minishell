# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/06 12:17:29 by seungsle          #+#    #+#              #
#    Updated: 2022/10/21 13:46:52 by seungsle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
# CC		= cc -g -lreadline -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include
CC		= cc -g -lreadline -L/Users/seungsle/.brew/opt/readline/lib -I/Users/seungsle/.brew/opt/readline/include
CFLAG	=
SRCS 	=	./srcs/main.c\
			./srcs/parse/node/node_env1.c\
			./srcs/parse/node/node_env2.c\
			./srcs/parse/node/node_token1.c\
			./srcs/parse/node/node_token2.c\
			./srcs/parse/parse_dollar.c\
			./srcs/parse/parse_env.c\
			./srcs/parse/parse_token_conditions.c\
			./srcs/parse/parse_token_utils1.c\
			./srcs/parse/parse_token_utils2.c\
			./srcs/parse/parse_token_utils3.c\
			./srcs/parse/parse_token.c\
			./srcs/parse/syntax_check.c\
			./srcs/utils/utils1.c\
			./srcs/utils/utils2.c\
			./srcs/utils/utils3.c\
			./srcs/utils/utils4.c\
			./srcs/utils/utils5.c\
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
			./srcs/env_manage.c

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
