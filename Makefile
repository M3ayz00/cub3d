NAME = cub3d
SRCS = cub.c ./parsing/gnl/get_next_line.c ./parsing/gnl/get_next_line_utils.c \
		./parsing/file_parsing.c ./parsing/ft_split.c ./parsing/ft_strtrim.c \
		./parsing/lst_management.c ./parsing/map_parsing.c
INCLUDES = -I/usr/include -Imlx
MLX_FLAGS = -L./minilibx-linux -lmlx -lX11 -lXext -lm
CFLAGS= #-g3 -fsanitize=address #-Wall -Werror -Wextra 
OBJS = $(SRCS:.c=.o)
GREEN = \033[0;32m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
		cc  $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)
		@echo "$(GREEN)Ready to play 🕹️ ✅ $(RESET)"
 
.c.o:
		cc $(CFLAGS) -c -o $@ $< $(INCLUDES)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re