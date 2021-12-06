NAME = fdf
COMP = gcc -Werror -Wextra -Wall

GNL_SRC = $(addprefix get_next_line/,get_next_line.c get_next_line_utils.c)

FDF_SRC = $(addprefix fdf_files/,fdf.c map.c draw.c) $(GNL_SRC)
FDF_OBJ = $(FDF_SRC:.c=.o)

all: $(NAME)

libmlx.a: mlx/
	@make -C mlx/

libft.a: libft/
	@make -C libft/

$(NAME): libft.a libmlx.a $(FDF_OBJ)
	@$(COMP) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(FDF_OBJ) libft/libft.a

%.o: %.c
	@$(COMP) -c $< -o $@

clean:
	@rm -f $(FDF_OBJ)
	@make -C mlx/ clean
	@make -C libft/ clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
