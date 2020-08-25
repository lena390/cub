/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3_parse_maze.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 18:47:49 by miphigen          #+#    #+#             */
/*   Updated: 2020/08/25 17:18:20 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**extend_capacity(char **array, int *capacity)
{
	int 	i;
	char	**new_array;
	
	new_array = malloc(sizeof(char *) * (*capacity + 20));
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < *capacity - 1)
	{
		new_array[i] = array[i];
		i++;
	}
	*capacity += 20;
	while (i < *capacity - 1)
		new_array[i++] = NULL;
	return (new_array);
}

char	**get_maze(int fd, char *s, t_map *map)
{
	char	**array;
	int		size;
	int		capacity;
	int		ret_value;

	capacity = 20;
	size = 1;
	if ((array = calloc(sizeof(char *), capacity)) == NULL)
		return (NULL);
	array[0] = s;
	while ((ret_value = get_next_line(fd, &array[size++])) >= 0)
	{
		size == capacity ? array = extend_capacity(array, &capacity) : 0;
		if (!array)
			break;
		if (ret_value == 0)
			break ;
	}
	if (ret_value == -1)
		map->status = -20;//errno error while reading maze

	return (array);
}

void	parse_maze(t_map *map, int fd, char *str)
{
	if ((map->maze = get_maze(fd, str, map)) == NULL )
		map->status = -21;//maze malloc error
	else if (map->status == 1 && maze_is_valid(map) == 2)
		map->status = 2;	
}
