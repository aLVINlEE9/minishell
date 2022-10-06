CC = cc -lreadline -g
CFLAGS = 
SRC_DIR = .
SRCS = ./lst.c ./parse.c ./tokenize.c
NAME = parsing
OBJS = $(SRCS:.c=.o)
INCLUDE = .

all : $(NAME)
		
.c.o:
	$(CC) -c $(CFLAGS) -I $(INCLUDE) -o $@ $< 

$(NAME) : $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $(OBJS)

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all fclean re
