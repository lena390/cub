/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_c3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 00:53:17 by miphigen          #+#    #+#             */
/*   Updated: 2020/09/27 16:49:53 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	struct_init(t_map *map)
{
	map->res_width = -1;
	map->res_height = -1;
	map->ceil = -1;
	map->floor = -1;
	map->hero_direction = -1.;
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

void	free_map(t_map *map)
{
	puts("free_map() in a process");
}

int	set_error_and_exit(char *msg, t_map *map)
{
	if (msg)
		ft_printf("Error\n%s (%d)\n", msg, map->status);
	free_map(map);
	exit(0);
}

int main(int ac, char **av)
{	
	t_map	*map;
	
	if ((map = ft_calloc(sizeof(t_map), 1)) != NULL)
	{
		struct_init(map);
		parse_map(map, open("map.cub", O_RDONLY));
		maze_is_valid(map);
		if (map->status == 6)
		{
			if (ac >= 2 && ft_strncmp(av[1], "--save\0", 7) == 0) 
				map->screenshot_needed = 1;	
			render_map(map);
		}
	}
	else
		set_error_and_exit("Memory allocation failure", map);
	free_map(map);

}

void	print_info(t_map *map)
{
	if (map == NULL)
	{
		puts("map == NULL");
		return;
	}
	printf("status = %d\n", map->status);
	printf("R %d %d\n", map->res_width, map->res_height);
	printf("NO %s\n", map->path_NO);
	printf("SO %s\n", map->path_SO);
	printf("WE %s\n", map->path_WE);
	printf("EA %s\n", map->path_EA);
	printf("S %s\n", map->path_S);
	printf("ceil %x\n", map->ceil);
	printf("floor %x\n\n", map->floor);
}

void	print_2d(char *s, char **array)
{
	puts(s);
	while (array && *array)
		printf("%s\n", *array++);
}
