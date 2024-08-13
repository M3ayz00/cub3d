NAME = cub3d
SRCS = minimap.c
INCLUDES = -I/usr/include -Imlx
MLX_FLAGS = -L./minilibx-linux -lmlx -lX11 -lXext -lm
CFLAGS= -g3 -fsanitize=address #-Wall -Werror -Wextra 
OBJS = $(SRCS:.c=.o)
GREEN = \033[0;32m

all: $(NAME)

$(NAME): $(OBJS)
		cc  $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)
		@echo "$(GREEN)Ready to play 🕹️ ✅"
 
.c.o:
		cc $(CFLAGS) -c -o $@ $< $(INCLUDES)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re