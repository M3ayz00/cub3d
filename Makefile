NAME = cub3d
BONUS = cub3d_bonus
SRCS = cub.c ./parsing/gnl/get_next_line.c ./parsing/gnl/get_next_line_utils.c \
		./parsing/ft_split.c ./parsing/ft_strtrim.c ./parsing/memory_management.c\
		./parsing/checkers_1.c ./parsing/checkers_2.c ./parsing/checkers_3.c \
		./parsing/checkers_4.c ./parsing/color_processing.c ./parsing/init_and_free.c \
		./parsing/map_processing.c ./parsing/map_texture_parsing.c ./parsing/texture_processing.c  \
		./parsing/parsing_utils.c ./parsing/parsing_utils2.c ./parsing/string_operations.c  \
		./parsing/lst_management.c ./parsing/map_parsing.c ./raycasting/raycasting.c \
		./raycasting/player.c ./raycasting/move.c ./raycasting/draw_env.c ./raycasting/utils.c \

SRCS_BONUS =./bonus/cub_bonus.c ./parsing/memory_management.c ./parsing/map_parsing.c\
		./parsing/gnl/get_next_line.c ./parsing/gnl/get_next_line_utils.c \
		./parsing/ft_split.c ./parsing/ft_strtrim.c \
		./parsing/checkers_1.c ./parsing/checkers_2.c ./parsing/checkers_3.c \
		./parsing/checkers_4.c ./parsing/color_processing.c ./parsing/init_and_free.c \
		./parsing/map_processing.c ./parsing/map_texture_parsing.c ./parsing/texture_processing.c  \
		./parsing/parsing_utils.c ./parsing/parsing_utils2.c ./parsing/string_operations.c  \
		./parsing/lst_management.c ./raycasting/raycasting.c \
		./raycasting/player.c ./bonus/move_bonus.c ./raycasting/draw_env.c ./raycasting/utils.c \
		./bonus/minimap_bonus.c

INCLUDES = -I/usr/include -Imlx
MLX_FLAGS = -L./minilibx-linux -lmlx -lX11 -lXext -lm
CFLAGS=  -g3 -fsanitize=address #-Wall -Werror -Wextra
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
GREEN = \033[0;32m
RESET = \033[0m

all: $(NAME)

bonus: $(BONUS)

$(NAME): $(OBJS)
		cc  $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)
		@echo "$(GREEN)Ready to play 🕹️ ✅ $(RESET)"

$(BONUS): $(OBJS_BONUS)
		cc  $(CFLAGS) -o $(BONUS) $(OBJS_BONUS) $(MLX_FLAGS)
		@echo "$(GREEN)Ready to play 🕹️ ✅ $(RESET)"

.c.o:
		cc $(CFLAGS) -c -o $@ $< $(INCLUDES)

clean:
		rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
		rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re
