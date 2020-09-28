/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_maze_c3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 18:47:49 by miphigen          #+#    #+#             */
/*   Updated: 2020/09/27 16:49:43 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_array(char **array, int i)
{
	char *s;

	s = *array;
	while (i--)
		free(s++);
	free(array);
}

char	**extend_capacity(char **array, int *capacity, t_map *map)
{
	int 	i;
	char	**new_array;

	new_array = malloc(sizeof(char *) * (*capacity + 20));
	if (!new_array)
	{	
		set_error_and_exit("Memory allocation failure", map);
	}
	i = 0;
	while (i < *capacity)
	{
		new_array[i] = array[i];
		i++;
	}
	free(array);
	*capacity += 20;
	while (i < *capacity)
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
	if ((array = ft_calloc(sizeof(char *), capacity)) == NULL)
		return (NULL);
	array[0] = s;
	while ((ret_value = get_next_line(fd, &array[size++])) >= 0)
	{
		size == capacity ? array = extend_capacity(array, &capacity, map) : 0;	
		if (!array)
			break;
		if (ret_value == 0)
			break ;
	}
	if (ret_value == -1)
		set_error_and_exit("Error occurred while reading file", map);
	return (array);
}

void	parse_maze(t_map *map, int fd, char *str)
{
	map->status = 3;
	if ((map->maze = get_maze(fd, str, map)) == NULL )
		set_error_and_exit("Memory allocation failure", map);
}
