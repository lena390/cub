all:
	gcc *c3.c ~/libft.a -lmlx -framework OpenGL -framework AppKit && ./a.out

l-with-flags:
	gcc *c3.c ~/libft.a mlx.a -Wall -Wextra -Werror -lXext -lX11 -lm && ./a.out
l:
	gcc *c3.c ~/libft.a mlx.a -lXext -lX11 -lm && ./a.out
lg:
	gcc *c3.c ~/libft.a mlx.a -lXext -lX11 -lm -g && gdb ./a.out
test:
	gcc my_mlx*.c test.c ~/libft.a mlx.a -lXext -lX11 -lm && ./a.out
