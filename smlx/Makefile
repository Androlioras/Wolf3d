NAME = libsmlx.a
SRCS = smlx_init.c\
	   smlx_destroy_window.c\
	   smlx_destroy_image.c\
	   smlx_put_image_to.c\
	   smlx_clear_image.c\
	   smlx_new_image.c\
	   smlx_draw_line.c\
	   smlx_pixel_put.c\
	   smlx_set_flags.c\
	   smlx_translate.c\
	   smlx_key_hook.c\
	   smlx_converts.c\
	   smlx_rotate.c\
	   smlx_create.c\
	   smlx_button.c\
	   smlx_matrix.c\
	   smlx_hooks.c\
	   smlx_draw_polygone.c\
	   smlx_draw_triangle.c\
	   smlx_get_fps.c\
	   colors.c
OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror
INCLUDE = include
SRC = src
LIBFT = ../libft

.PHONY: clean fclean all re norme

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\033[0m\033[46m\033[37m\033[1m[libsmlx]\033[40m\033[1m\033[37m making libsmlx"
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "\033[0m\033[46m\033[37m\033[1m[libsmlx]\033[40m\033[1m\033[37m done"

%.o: $(SRC)/%.c
	@echo "\033[0m\033[46m\033[37m\033[1m[libsmlx]\033[0m\033[40m\033[33m making '$@'\033[0m"
	@$(CC) $(FLAGS) -I $(INCLUDE) -I $(LIBFT)/includes -c $^

clean:
	@echo "\033[0m\033[46m\033[37m\033[1m[libsmlx]\033[0m\033[40m\033[36m cleaning objects"
	@rm -f $(OBJS)
	@echo "\033[0m\033[46m\033[37m\033[1m[libsmlx]\033[0m\033[40m\033[36m done"

fclean: clean
	@echo "\033[0m\033[46m\033[37m\033[1m[libsmlx]\033[0m\033[40m\033[34m cleaning archive"
	@rm -f $(NAME)
	@echo "\033[0m\033[46m\033[37m\033[1m[libsmlx]\033[0m\033[40m\033[34m done"

norme:
	@echo "\033[0m\033[46m\033[37m\033[1m[libsmlx]\033[0m\033[40m\033[1m making norme\033[32m"
	@norminette $(SRC) $(INCLUDE)
	@echo "\033[0m\033[46m\033[37m\033[1m[libsmlx]\033[0m\033[40m\033[1m done\033[32m"

re: fclean all