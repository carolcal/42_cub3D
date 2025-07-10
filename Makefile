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

# Library
LIBFT = lib/
MLX_DIR = minilibx-linux/
LIBMLX	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# Directories
SRC_DIR = src/mandatory/
INI_DIR = src/mandatory/init/
PAR_DIR = src/mandatory/parsing/
VAL_DIR = src/mandatory/validation/
DRW_DIR = src/mandatory/draw/
ACT_DIR = src/mandatory/actions/
SRC_DIR_BONUS = src/bonus/
INI_DIR_BONUS = src/bonus/init/
PAR_DIR_BONUS = src/bonus/parsing/
VAL_DIR_BONUS = src/bonus/validation/
DRW_DIR_BONUS = src/bonus/draw/
ACT_DIR_BONUS = src/bonus/actions/
OBJ_DIR = obj/
OBJ_DIR_BONUS = obj_bonus/
INCLUDES = -I inc/ -I $(LIBFT)

# Source files and object files
SRC = $(addprefix $(SRC_DIR), main.c) \
	$(addprefix $(INI_DIR), init.c init_grid.c init_mlx.c) \
	$(addprefix $(PAR_DIR), parse.c parse_map.c parse_properties.c parse_utils.c) \
	$(addprefix $(VAL_DIR), validate.c validate_map.c validate_utils.c) \
	$(addprefix $(DRW_DIR), draw.c raycasting.c draw_ray.c draw_utils.c) \
	$(addprefix $(ACT_DIR), hooks.c handle_keys.c actions_player.c)
SRC_BONUS = $(addprefix $(SRC_DIR_BONUS), main_bonus.c) \
	$(addprefix $(INI_DIR_BONUS), init_bonus.c init_grid_bonus.c init_mlx_bonus.c) \
	$(addprefix $(PAR_DIR_BONUS), parse_bonus.c parse_map_bonus.c parse_properties_bonus.c parse_utils_bonus.c) \
	$(addprefix $(VAL_DIR_BONUS), validate_bonus.c validate_map_bonus.c validate_utils_bonus.c) \
	$(addprefix $(DRW_DIR_BONUS), draw_bonus.c raycasting_bonus.c draw_ray_bonus.c draw_sprites_bonus.c draw_minimap_bonus.c draw_utils_bonus.c) \
	$(addprefix $(ACT_DIR_BONUS), hooks_bonus.c handle_keys_bonus.c handle_mouse_bonus.c actions_player_bonus.c actions_sprites_bonus.c)

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
OBJ_BONUS = $(SRC_BONUS:$(SRC_DIR_BONUS)%.c=$(OBJ_DIR_BONUS)%.o)

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

$(OBJ_DIR_BONUS)%.o: $(SRC_DIR_BONUS)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Executable
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -L $(LIBFT) $(LIBMLX) -lft -o $(NAME)
	@echo "$(GREEN)Cub3D Mandatory Compiled!$(END)"

$(NAME_BONUS): $(OBJ_BONUS)
	@$(CC) $(CFLAGS) $(OBJ_BONUS) -L $(LIBFT) $(LIBMLX) -lft -o $(NAME_BONUS)
	@echo "$(GREEN)Cub3D Bonus Compiled!$(END)"

# Clean objects
clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR_BONUS)
	@make -C $(LIBFT) clean $(NO_PRINT)
	@echo "$(GREEN)Cleaned$(END)"

# Clean all generated file
fclean: clean
	@rm -rf $(NAME) $(NAME_BONUS)
	@make -C $(LIBFT) fclean $(NO_PRINT)
	@rm -f valgrind.log
	@echo "$(GREEN)All!$(END)"

# Valgrind
val: re
	@valgrind --leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				./${NAME} maps/valid/42.cub

val_bonus: re_bonus
	@valgrind --leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				./${NAME_BONUS} maps/valid/42_bonus.cub

# Recompile everything
re: fclean all
re_bonus: fclean bonus

.PHONY: all bonus clean fclean re re_bonus val val_bonus norm libft
