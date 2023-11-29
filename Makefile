# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gibkim <gibkim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/05 10:18:50 by gibkim            #+#    #+#              #
#    Updated: 2023/11/28 16:12:47 by gibkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
RM			=	rm -rf
CFLAGS		=	-Wall -Wextra -Werror -I.
LIBFT_DIR	=	libft
LIBFT		=	libft.a
LIBMLX_DIR	=	mlx
LIBMLX		=	libmlx.dylib
SRC_DIR		=	srcs
OBJ_DIR		=	objs
SRCS 		= 	$(wildcard $(SRC_DIR)/*.c)
OBJS 		= 	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
HEADER		=	$(SRC_DIR)/minirt.h
NAME		=	miniRT

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: all

$(OBJ_DIR):
	mkdir -p $@

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) bonus
	$(MAKE) -C $(LIBMLX_DIR)
	$(CC) $(CFLAGS) -lmlx -Imlx -Llibft -lft -framework OpenGL -framework AppKit -o $@ $^
	install_name_tool -change $(LIBMLX) $(LIBMLX_DIR)/$(LIBMLX) $@

clean:
	$(MAKE) -C $(LIBFT_DIR) $@
	$(RM) $(OBJS)
	$(RM) $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) $@
	$(MAKE) -C $(LIBMLX_DIR) $^
	$(RM) $(NAME)

re: fclean all
	
.PHONY: all clean fclean re bonus
