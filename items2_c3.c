/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items2_c3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 20:19:36 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/25 13:52:43 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_item(int x, int y, int pos)
{
	int	scale;

	scale = g_map->scale;
	g_map->items[pos].x = x * scale + scale / 2;
	g_map->items[pos].y = y * scale + scale / 2;
	g_map->items[pos].angle = -1;
	g_map->items[pos].dist = -1;
}

void	get_items_coord(char **maze)
{
	int	i;
	int	j;
	int	k;
	int	count;


	count = 0;
	i = -1;
	while (++i < g_map->maze_height)
	{
		j = -1;
		while (++j < g_map->maze_width)
			if (maze[i][j] == '2')
				count++;
	}
	g_map->items = ft_malloc(sizeof(t_item) * count);
	i = -1;
	k = 0;
	while (++i < g_map->maze_height && k != count)
	{
		j = -1;
		while (++j < g_map->maze_width)
		{
			if (maze[i][j] == '2')
				add_item(j, i, k++);
		}
	}
	g_map->items_count = count;
}
