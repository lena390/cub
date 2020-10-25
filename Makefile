all:
	gcc *c3.c ~/libft.a -lmlx -framework OpenGL -framework AppKit && ./a.out map.cub

l-with-flags:
	gcc *c3.c ~/libft.a mlx.a -Wall -Wextra -Werror -lXext -lX11 -lm && ./a.out map.cub
l:
	gcc *c3.c ~/libft.a mlx.a -lXext -lX11 -lm -g && ./a.out map.cub
lg:
	gcc *c3.c ~/libft.a mlx.a -lXext -lX11 -lm -g && gdb ./a.out map.cub
b:
	gcc *c3.c ~/libft.a mlx.a -lXext -lX11 -lm -g && ./a.out map.cub map.cub --save
c:
	gcc *c3.c ~/libft.a mlx.a -lXext -lX11 -lm -g
test:
	gcc my_mlx*.c test.c ~/libft.a mlx.a -lXext -lX11 -lm && ./a.out
