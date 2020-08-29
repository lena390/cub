/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 00:53:17 by miphigen          #+#    #+#             */
/*   Updated: 2020/08/27 19:05:57 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	struct_init(t_map *map)
{
	map->res_width = -1;
	map->res_height = -1;
	map->ceil = -1;
	map->floor = -1;
}

int main(int ac, char **av)
{	
	t_map	*map;
	
	if ((map = ft_calloc(sizeof(t_map), 1)) == NULL)
		return (0); //malloc error
	struct_init(map);
	parse_map(map, open("map.cub", O_RDONLY));
	
	char **array = map->maze;
	int i = 0;
	if (map->status == 2)
		puts("map is valid");
	else
		puts("map is NOT valid");
	printf("map status = %d\n", map->status);
//	while (array != NULL && *array != NULL)
//		printf("%2d : %s\n", i++, *array++);
//	if (map->status == 2)
		render_map(map);
	//print error
//	free_map(map);
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