NAME        = cub3D

LIBFT       = ./libft/libft.a 
MLX = ./mlx/
FILES = cub3D.c parsing_utils.c read_map.c parse_map.c 
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3
sanitize    = -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
RM          = rm -f
OBJS		= $(FILES:.c=.o)

all: $(NAME)

%.o : %.c
	@cc $(CFLAGS) -Imlx -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	@$(MAKE) -C $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
                                                         
$(LIBFT) :
	@make -sC ./libft

clean:
	@$(RM) $(OBJS)
	@make clean -sC ./libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -sC ./libft

re: fclean all

push: fclean
	git add .
	git commit -m "Updated on $(shell date +'%Y-%m-%d %H:%M:%S') by $(shell whoami) final"
	git push -u origin master

.PHONY: all clean fclean re