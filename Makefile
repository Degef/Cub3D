NAME        = cub3D

FILES = cub3D.c 

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
sanitize    = -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
RM          = rm -f

OBJS		= $(FILES:.c=.o)

all: $(NAME)

%.o : %.c
	@cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
                                                         
clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

push: fclean
	git add .
	git commit -m "Updated on $(shell date +'%Y-%m-%d %H:%M:%S') by $(shell whoami)"
	git push -u origin master

.PHONY: all clean fclean re