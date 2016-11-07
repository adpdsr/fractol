# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/22 15:09:30 by adu-pelo          #+#    #+#              #
#    Updated: 2016/11/07 17:13:45 by adu-pelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fractol

C_DIR		= sources
C_DIRS		= $(shell find $(C_DIR) -type d -follow -print)
C_FILES 	= $(shell find $(C_DIRS) -type f -follow -print | grep -w "[.c]$$")

O_DIR		= .tmp/obj
O_DIRS		= $(C_DIRS:$(C_DIR)%=$(O_DIR)%)
O_FILES 	= $(C_FILES:$(C_DIR)%.c=$(O_DIR)%.o)

FLAGS		= -Wall -Werror -Wextra
INCLUDES 	= -Iincludes -Ilibft
LIB			= -L./libft -lft
MLX			= -lmlx -framework OpenGl -framework AppKit

all: $(NAME)

$(NAME): $(O_FILES)
	@echo "Creating $(NAME)"
	@make -C ./libft
	@gcc $(FLAGS) $^ $(LIB) $(MLX) -o $@

$(O_DIR)%.o: $(C_DIR)%.c
	@echo "Creating object : $@"
	@mkdir -p $(O_DIRS) $(O_DIR)
	@gcc $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:	
	@echo "Deleting objects"
	@rm -rf $(O_FILES)
	@make clean -C libft

fclean: clean
	@echo "Deleting $(NAME)"
	@make fclean -C libft
	@rm $(NAME) || true
	@rm -rf .tmp/

re: fclean all

.PHONY : all clean fclean re
