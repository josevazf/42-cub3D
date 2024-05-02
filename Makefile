# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/25 10:36:01 by jrocha-v          #+#    #+#              #
#    Updated: 2024/05/02 21:21:31 by jrocha-v         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= cub3d

SRCS_DIR		= src

OBJS_DIR		= objs

INCLUDES		= includes
LIBFT			= ./libs/libft/libft.a
LIBFT_DIR		= ./libs/libft
LIBMLX			= ./libs/minilibx-linux/libmlx.a
LIBMLX_DIR		= ./libs/minilibx-linux

CC				= cc
CFLAGS			= -Wall -Wextra -Werror
MLX_FLAGS		= -lmlx_Linux -lXext -lX11 -lm -lbsd

MK_FLAG			= --no-print-directory
RM				= rm -rf

SRCS			= 	main.c \
					init.c 	\
					events.c \
					player.c \
					minimap.c \
					draw.c \
					utils.c \
					error.c

# Substitute .c with .o 
OBJS			= $(SRCS:%.c=$(OBJS_DIR)/%.o)

#default target
all: $(NAME)
$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBMLX_DIR) $(MLX_FLAGS) $(LIBFT) -o $(NAME)
	echo "Finished!"

#create .o files
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(@D)
	$(CC) -I $(INCLUDES) $(CFLAGS) -c $< -o $@

$(LIBFT):
	echo "Compiling necessary libs..."
	$(MAKE) $(MK_FLAG) -C $(LIBFT_DIR)

#$(LIBMLX):
#	echo "Compiling necessary libs..."
#	$(MAKE) $(MK_FLAG) -C $(LIBMLX_DIR)

#remove .o files
clean:
	$(RM) $(OBJS_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
#$(MAKE) clean -C $(LIBMLX_DIR)

fclean: clean
#$(RM) $(NAME) $(LIBFT) $(LIBMLX)
	$(RM) $(NAME) $(LIBFT)

#reset - remove and recompile
re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
.SILENT:
