/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_c3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 16:24:19 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/24 14:54:45 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_max_width(char **array)
{
	int	max;
	int	current;

	max = 0;
	while (*array)
	{
		current = ft_strlen(*array);
		max = current > max ? current : max;
		array++;
	}
	return (max);
}

int		is_valid_vert(char **array)
{
	int		ret_value;
	int		i;
	int		j;
	char	c1;
	char	c2;

	g_map->status = 6;
	i = 0;
	while (i < g_map->maze_height && (array[i][0] == ' ' || array[i][0] == '1'))
		i++;
	ret_value = i == g_map->maze_height ? 1 : 0;
	while (i < g_map->maze_width && ret_value == 1)
	{
		j = 0;
		while (j < g_map->maze_height - 1 && ret_value == 1)
		{
			c1 = array[j][i];
			c2 = array[++j][i];
			if (c1 == '1')
				;
			else if (c1 == '0' || c2 == '2')
				ret_value = (c2 == ' ' || c2 == '\0') ? 0 : 2;
			else if (c1 == ' ')
				ret_value = c2 != ' ' && c2 != '1' && c2 != '\0' ? 0 : 2;
			else
				ret_value = 0;
		}
		i++;
	}
	return (ret_value);
}

void	maze_is_valid(void)
{
	char	**ptr;

	g_map->status = 4;
	g_map->maze_width = get_max_width(g_map->maze);
	if ((ptr = add_spaces(g_map->maze, g_map->maze_width, &g_map->maze_height))
		!= NULL)
	{
		g_map->maze = ptr;
		is_valid_hor(g_map->maze) && is_valid_vert(g_map->maze) ? 0 :
			set_error_and_exit("Invalid maze");
	}
	else
		set_error_and_exit("Memory allocation failure");
}
