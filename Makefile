# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junhjeon <seungsle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/06 12:17:29 by seungsle          #+#    #+#              #
#    Updated: 2022/10/23 16:04:09 by junhjeon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= cc -g -Wall -Wextra -Werror
# CFLAG	= -Werror -Wextra -Wall

RDLINE_DIR	=	/Users/junhjeon/.brew/opt/readline/lib/
RDLINE_INC	=	/Users/junhjeon/.brew/opt/readline/include/

INC_DIR		=	./includes/

# CC		= cc -g -lreadline -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include
# CC		= cc -L/Users/junhjeon/.brew/opt/readline/lib/ -lreadline -I/Users/junhjeon/.brew/opt/readline/include/ -I./includes/
SRCS_DIR	=	./srcs/

SOURCES 	=	main.c\
			parse/node/node_env1.c\
			parse/node/node_env2.c\
			parse/node/node_token1.c\
			parse/node/node_token2.c\
			parse/parse_dollar.c\
			parse/parse_env.c\
			parse/parse_token_conditions.c\
			parse/parse_token_utils1.c\
			parse/parse_token_utils2.c\
			parse/parse_token_utils3.c\
			parse/parse_token.c\
			parse/syntax_check1.c\
			parse/syntax_check2.c\
			utils/utils1.c\
			utils/utils2.c\
			utils/utils3.c\
			utils/utils4.c\
			utils/utils5.c\
			utils/utils.c\
			utils/utils6.c\
			utils/utils7.c\
			pipex.c\
			exe_cmd.c\
			cmd.c\
			iofile.c\
			set_terminal.c\
			set_signal.c\
			print.c\
			parse_dol_jh.c\
			parse_dol_jh2.c\
			monitoring.c\
			exe_cmd2.c\
			exe_cmd3.c\
			make_cmdlst.c\
			make_pipe_cmdlst.c\
			make_pipe_cmdlst2.c\
			built_in.c\
			built_in2.c\
			built_in3.c\
			built_in4.c\
			set_signal_fork.c\
			env_manage.c

SRCS		=	$(addprefix $(SRCS_DIR), $(SOURCES))


OBJS 	= ${SRCS:.c=.o}
LIBRARY		= -L$(RDLINE_DIR) -lreadline
HEADERS		= -I$(INC_DIR) -I$(RDLINE_INC)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAG) $(LIBRARY) $(HEADERS)

# $(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(INCS_DIR)*.h
.c.o: 
	$(CC) -c $< -o $@ $(CFLAG) $(HEADERS)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : 
	make fclean
	make all

.PHONY: all clean fclean re
