# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/13 23:22:13 by ayarmaya          #+#    #+#              #
#    Updated: 2025/05/18 23:35:29 by ayarmaya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D
BONUS_NAME  = cub3D_bonus

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f
RMDIR       = rm -rf

LIBFT       = libft/libft.a
MLX         = mlx_linux/libmlx_Linux.a
MLX_FLAGS   = -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

HEADERS     = -I./include -Ilibft/include -Imlx_linux

SRCDIR      = src
SRCS        = $(SRCDIR)/main.c \
		      $(SRCDIR)/init.c \
	 		  $(SRCDIR)/parse.c \
		      $(SRCDIR)/parse_map_1.c \
	 		  $(SRCDIR)/parse_map_2.c \
	 		  $(SRCDIR)/parse_map_3.c \
	 		  $(SRCDIR)/parse_map_4.c \
	 		  $(SRCDIR)/parse_texture.c \
	 		  $(SRCDIR)/raycasting.c \
	 		  $(SRCDIR)/render.c \
	 		  $(SRCDIR)/textures.c \
	 		  $(SRCDIR)/move.c \
	 		  $(SRCDIR)/utils.c \
	 		  $(SRCDIR)/exit.c	\
	 		  $(SRCDIR)/wall.c \
	 		  $(SRCDIR)/free.c \
	 		  $(SRCDIR)/dda.c

OBJDIR      = obj
OBJS        = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

BONUS_SRCDIR = src/bonus
BONUS_SRCS   = $(BONUS_SRCDIR)/main_bonus.c \
               $(BONUS_SRCDIR)/init_bonus.c \
               $(BONUS_SRCDIR)/parse_bonus.c \
               $(BONUS_SRCDIR)/parse_map_1_bonus.c \
			   $(BONUS_SRCDIR)/parse_map_2_bonus.c \
			   $(BONUS_SRCDIR)/parse_map_3_bonus.c \
			   $(BONUS_SRCDIR)/parse_map_4_bonus.c \
               $(BONUS_SRCDIR)/parse_texture_bonus.c \
               $(BONUS_SRCDIR)/raycasting_bonus.c \
               $(BONUS_SRCDIR)/render_bonus.c \
               $(BONUS_SRCDIR)/textures_bonus.c \
               $(BONUS_SRCDIR)/move_bonus.c \
               $(BONUS_SRCDIR)/utils_bonus.c \
               $(BONUS_SRCDIR)/exit_bonus.c  \
               $(BONUS_SRCDIR)/wall_bonus.c \
		       $(BONUS_SRCDIR)/free_bonus.c \
	 		   $(BONUS_SRCDIR)/dda_bonus.c \
			   $(BONUS_SRCDIR)/minimap_bonus.c \
			   $(BONUS_SRCDIR)/mouse_move_bonus.c \
			   $(BONUS_SRCDIR)/interact_door_bonus.c \
			   $(BONUS_SRCDIR)/minimap_door_bonus.c


BONUS_OBJDIR      = obj/bonus
BONUS_OBJS   = $(patsubst $(BONUS_SRCDIR)/%.c, $(BONUS_OBJDIR)/%.o, $(BONUS_SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@make -C mlx_linux
	$(CC) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	@make -C libft
	@make -C mlx_linux
	$(CC) $(BONUS_OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(BONUS_NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADERS) -MMD -MP -c $< -o $@

$(BONUS_OBJDIR)/%.o: $(BONUS_SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADERS) -MMD -MP -c $< -o $@

-include $(OBJS:.o=.d)
-include $(BONUS_OBJS:.o=.d)

clean:
	$(RMDIR) $(OBJDIR)
	@make -C libft clean
	@make -C mlx_linux clean

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all bonus clean fclean re