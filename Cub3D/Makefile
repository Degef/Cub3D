NAME      = cub3D
LIBFT     = ./libft/libft.a
MLXMAC    = ./mlx/
MLXLINUX  = ./mlx_linux/

SRC_PATH  = src/
OBJ_PATH  = obj
SRC_DIRS  = execution parsing
SRC       = $(wildcard $(addprefix $(SRC_PATH), $(addsuffix /*.c, $(SRC_DIRS))))
OBJS      = $(patsubst $(SRC_PATH)%.c,$(OBJ_PATH)/%.o,$(SRC))

CC        = cc
CFLAGS    = -Wall -Wextra -Werror -g
RM        = rm -rf
MacLinker = -Lmlx -lmlx -framework OpenGL -framework AppKit
sanitize  = -fsanitize=address -g3 -fno-omit-frame-pointer 

all: $(OBJ_PATH) $(LIBFT) $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C $(MLXMAC)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MacLinker) -o $(NAME)

$(LIBFT):
	@make -sC ./libft

$(OBJ_PATH):
	mkdir -p $(addprefix $(OBJ_PATH)/, $(SRC_DIRS))

clean:
	@$(RM) $(OBJ_PATH)
	@make clean -sC ./libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -sC ./libft

re: fclean all

push: fclean
	git add .
	git commit -m "Updated on $(shell date +'%Y-%m-%d %H:%M:%S') by $(shell whoami)"
	git push -u origin master

.PHONY: all clean fclean re
