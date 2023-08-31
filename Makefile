# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/31 19:03:20 by aandom            #+#    #+#              #
#    Updated: 2023/08/31 19:04:47 by aandom           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D

LIBFT       = ./libft/libft.a 
MLXMAC		= ./mlx/
MLXLINUX	= ./mlx_linux/
FILES 		= cub3D.c parsing_utils.c 
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
sanitize    = -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
RM          = rm -f
LinLinker	= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
MacLinker	= -Lmlx -lmlx -framework OpenGL -framework AppKit
OBJS		= $(FILES:.c=.o)

all: $(NAME)

%.o : %.c
	@cc $(CFLAGS) -Imlx -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
//	# for MAC
//	# @$(MAKE) -C $(MLX)
//	# @$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MacLinker) -o $(NAME)

//	# for LINUX 
	@$(MAKE) -C $(MLXLINUX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LinLinker) -o $(NAME)
                                                         
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