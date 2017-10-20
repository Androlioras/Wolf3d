NAME = wolf3d
NAME2 = map_editor
CC = gcc
FLAGS = -Wall -Wextra -Werror
LIBFT = libft
SMLX = smlx
ENDFLAGS = -L $(LIBFT) -lft -L $(SMLX) -lsmlx -lmlx -lm -framework OpenGL -framework AppKit
ENDFLAGS2 = -L $(LIBFT) -lft
LSD = lsd2
INCLUDE = include
SRC = src
SRCS =	main.c\
		hooks.c\
		draw.c\
		draw_wolf.c\
		draw_wolf_2.c\
		load_map.c\
		load_blocks.c\
		load_entities.c\
		move.c
SRCS2 =	map_editor.c\
		me_errors.c\
		me_exit.c\
		me_create.c\
		me_push.c\
		me_dump.c\
		me_load.c\
		me_unload.c\
		me_edit.c\
		me_spawn.c\
		me_rm.c\
		me_help.c\
		me_entity.c
OBJS = $(SRCS:%.c=%.o)
OBJS2 = $(SRCS2:%.c=%.o)

.PHONY: clean fclean all re norme

all: $(NAME) $(NAME2)

%.o: $(SRC)/%.c
	$(CC) $(FLAGS) -I $(INCLUDE) -I $(SMLX)/include -I $(LIBFT) -c $^

$(LIBFT)/libft.a:
	make -C $(LIBFT)

$(SMLX)/libsmlx.a:
	make -C $(SMLX)

$(NAME2): $(LIBFT)/libft.a $(OBJS2)
	$(CC) $(FLAGS) -o $(NAME2) -I $(INCLUDE) -I $(LIBFT) $(OBJS2) $(ENDFLAGS2)

$(NAME): $(LIBFT)/libft.a $(SMLX)/libsmlx.a $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) -I $(INCLUDE) -I $(LIBFT) -I $(SMLX)/include $(OBJS) $(ENDFLAGS)

clean:
	make -C $(LIBFT) clean
	make -C $(SMLX) clean
	rm -f $(OBJS)
	rm -f $(OBJS2)

fclean: clean
	make -C $(LIBFT) fclean
	make -C $(SMLX) fclean
	rm -f $(NAME)
	rm -f $(NAME2)

norme:
	make -C $(LIBFT) norme
	make -C $(SMLX) norme
	norminette $(INCLUDE) $(SRC)

re: fclean all
