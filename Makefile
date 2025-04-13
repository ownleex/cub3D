# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/13 23:22:13 by ayarmaya          #+#    #+#              #
#    Updated: 2025/04/13 23:22:55 by ayarmaya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

LIBFT = libft/libft.a
MLX = mlx_linux/libmlx_Linux.a
MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

HEADERS = -I./include -Ilibft/include -Imlx_linux

SRCS = src/main.c \
	   src/init.c \
	   src/parse.c \
	   src/parse_map.c \
	   src/parse_texture.c \
	   src/raycasting.c \
	   src/render.c \
	   src/textures.c \
	   src/move.c \
	   src/utils.c \
	   src/exit.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	make -C mlx_linux
	$(CC) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make -C libft clean
	make -C mlx_linux clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re