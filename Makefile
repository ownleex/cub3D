# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/13 23:22:13 by ayarmaya          #+#    #+#              #
#    Updated: 2025/04/14 01:03:26 by ayarmaya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
RMDIR = rm -rf

LIBFT = libft/libft.a
MLX = mlx_linux/libmlx_Linux.a
MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

HEADERS = -I./include -Ilibft/include -Imlx_linux

SRCDIR = src
SRCS = $(SRCDIR)/main.c \
	   $(SRCDIR)/init.c \
	   $(SRCDIR)/parse.c \
	   $(SRCDIR)/parse_map.c \
	   $(SRCDIR)/parse_texture.c \
	   $(SRCDIR)/raycasting.c \
	   $(SRCDIR)/render.c \
	   $(SRCDIR)/textures.c \
	   $(SRCDIR)/move.c \
	   $(SRCDIR)/utils.c \
	   $(SRCDIR)/exit.c

OBJDIR = obj
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	make -C mlx_linux
	$(CC) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	$(RMDIR) $(OBJDIR)
	make -C libft clean
	make -C mlx_linux clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re