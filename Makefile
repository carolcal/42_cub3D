# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 16:15:25 by cayamash          #+#    #+#              #
#    Updated: 2025/04/09 15:56:40 by naharumi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the program
NAME = cub3D
NAME_BONUS = cub3D_bonus

# Compilers and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline -lncurses

# Library
LIBFT = lib

# Directories
SRC_DIR = src/
VAL_DIR = src/validate
OBJ_DIR = obj/
INCLUDES = -I inc/ -I $(LIBFT)

# Source files and object files
SRC = $(addprefix $(SRC_DIR), init.c game.c main.c) \
	$(addprefix $(VAL_DIR), validate.c validate_map.c validate_player.c) \

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# Style
NO_PRINT = --no-print-directory
GREEN	= \033[1;32m
BLUE	= \033[1;36m
YELLOW	= \033[1;33m
MAGENTA	= \033[1;35m
END		= \033[0m

# Rules
all: libft $(NAME)

bonus: libft $(NAME_BONUS)

libft:
	@make -C $(LIBFT) $(NO_PRINT)

norm:
	@echo "\n$(BLUE)======= INCLUDES =======$(END)"
	@norminette inc | sed 's/OK/\x1b[1;32m&\x1b[0m/g' | sed 's/Error/\x1b[1;31m&\x1b[0m/g'
	@echo "\n$(YELLOW)========= LIB =========$(END)"
	@norminette lib | sed 's/OK/\x1b[1;32m&\x1b[0m/g' | sed 's/Error/\x1b[1;31m&\x1b[0m/g'
	@echo "\n$(MAGENTA)========= SRC =========$(END)"
	@norminette src | sed 's/OK/\x1b[1;32m&\x1b[0m/g' | sed 's/Error/\x1b[1;31m&\x1b[0m/g'

# Compile object files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Executable
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT) -lft $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)Cub3D Compiled!$(END)"

$(NAME_BONUS): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT) -lft $(LDFLAGS) -o $(NAME_BONUS)
	@echo "$(GREEN)Cub3D Compiled!$(END)"

# Clean objects
clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT) clean $(NO_PRINT)
	@echo "$(GREEN)Cleaned$(END)"

# Clean all generated file
fclean: clean
	@rm -rf $(NAME) $(NAME_BONUS)
	@make -C $(LIBFT) fclean $(NO_PRINT)
	@rm -f valgrind.log
	@echo "$(GREEN)All!$(END)"

#Valgrind
val: re
	@valgrind -q --suppressions=sup.sup \
				--leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				./${NAME}

# Recompile everything
re: fclean all

.PHONY: all bonus clean fclean re val norm libft
