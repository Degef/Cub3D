NAME        = cub3D

LIBFT       = ./libft/libft.a 
MLXMAC		= ./mlx/
MLXLINUX	= ./mlx_linux/
FILES 		= cub3D.c ./parse_map/parsing_utils.c ./parse_map/parse_map.c ./parse_map/read_map.c ./parse_map/validate_map.c   \
				./src/start_raycast.c ./src/hooks.c ./src/init.c  ./src/draw_map.c 
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
sanitize    = -fsanitize=address -fno-omit-frame-pointer 
# -fno-optimize-sibling-calls
RM          = rm -f
LinLinker	= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
MacLinker	= -Lmlx -lmlx -framework OpenGL -framework AppKit
OBJS		= $(FILES:.c=.o)

all: $(NAME)

%.o : %.c
	@cc $(CFLAGS) -Imlx -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
# for MAC
# $(MAKE) -C $(MLXMAC)
	 $(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MacLinker) -o $(NAME)

# for LINUX 
# @$(MAKE) -C $(MLXLINUX)
# @$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LinLinker) -o $(NAME)
                                                         
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
