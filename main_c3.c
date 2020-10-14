/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_c3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 00:53:17 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/14 15:23:53 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		exit(4);//set_err and exit;
	else
		return (ptr);
}

void	cub_init()
{
	g_map->res_width = -1;
	g_map->res_height = -1;
	g_map->ceil = -1;
	g_map->floor = -1;
	g_map->hero_direction = -1.;
//	g_map->sp_location = malloc(10);
	g_map->img2 = malloc(sizeof(t_img));//free()!!
	g_map->sp_location = malloc(sizeof(double) * 4);
	if (!g_map->sp_location) set_error_and_exit("Memory allocation failure");
	g_map->column_counter = 0;
}

void	free_2d_array(char **s, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		free(s[i]);
	}
	free(s);
}

void	free_map()
{
	puts("free_map() in a process");
}

int	set_error_and_exit(char *msg)
{
	if (msg)
		ft_printf("Error\n%s (%d)\n", msg, g_map->status);
	free_map(g_map);
	exit(0);
}

int main(int ac, char **av)
{	
	if ((g_map = ft_calloc(sizeof(t_map), 1)) != NULL)
	{
		cub_init(g_map);
		parse_map(open("map.cub", O_RDONLY));
		maze_is_valid();
		if (g_map->status == 6)
		{
			if (ac >= 2 && ft_strncmp(av[1], "--save\0", 7) == 0) 
				g_map->screenshot_needed = 1;
			render_map();
		}
	}
	else
		set_error_and_exit("Memory allocation failure");
	free_map(g_map);
}
/*
void	print_info(t_map *map)
{
	if (g_map == NULL)
	{
		puts("map == NULL");
		return;
	}
	printf("status = %d\n", g_map->status);
	printf("R %d %d\n", g_map->res_width, g_map->res_height);
	printf("NO %s\n", g_map->path_NO);
	printf("SO %s\n", g_map->path_SO);
	printf("WE %s\n", g_map->path_WE);
	printf("EA %s\n", g_map->path_EA);
	printf("S %s\n", g_map->path_S);
	printf("ceil %x\n", g_map->ceil);
	printf("floor %x\n\n", g_map->floor);
}

void	print_2d(char *s, char **array)
{
	puts(s);
	while (array && *array)
		printf("%s\n", *array++);
}*/
