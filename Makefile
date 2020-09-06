all:
	gcc *c3.c ~/libft.a -lmlx -framework OpenGL -framework AppKit && ./a.out

linux:
	gcc *c3.c ~/Documents/42/libft.a -lmlx -lXext -lX11 && ./a.out
