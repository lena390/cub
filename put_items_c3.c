/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_items_c3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 15:50:37 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/25 13:52:45 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	print(t_item *tab, char *str)
{
	int i;
	i = -1;
	printf("%s %d\n", str, g_map->items_count);
	while (++i < g_map->items_count)
	{
		printf("%d. x = %d, y = %d, angle = %f, dist = %f\n", i, tab[i].x, tab[i].y, tab[i].angle, tab[i].dist);
	}
}

void	draw_items(t_item *item, int i, int j)
{
	int	start_x;
	int	start_y;
	float	scale_x;
	float	scale_y;

	print(g_map->items, "tri");
}

void	sort_items_by_dist(void)
{
	t_item	*tab;
	t_item	*sprite_max;
	float	dist_max;
	int		i;

	tab = g_map->items;
	dist_max = 0;
	while (dist_max != -1)
	{
		dist_max= -1;
		i = -1;
		while (++i < g_map->items_count)
		{
			if (tab[i].dist > dist_max)
			{
				dist_max = tab[i].dist;
				sprite_max = &tab[i];
			}
		}
		if (dist_max != -1)
		{
			print(g_map->items, "dva");
			draw_items(sprite_max, 0, 0);
			sprite_max->dist = -1;
		}
	}
}

void	put_items(void)
{
	t_item	*tab;
	int		i;


	i = -1;
	while (++i < g_map->items_count)
	{
		tab[i].angle = atan2(g_map->hero_y - (double)tab[i].y, (double)tab[i].x - g_map->hero_x);
		if (tab[i].angle < 0 && g_map->hero_direction >= M_PI / 6 &&
			g_map->hero_direction <= (M_PI * 2 - M_PI / 6))
			tab[i].angle += M_PI;
		if ((g_map->hero_direction > -M_PI / 6 && g_map->hero_direction <= 7))
			tab[i].angle += 2 * M_PI;
		tab[i].angle -= 2 * M_PI;
		if (tab[i].angle > -M_PI / 6 && tab[i].angle < M_PI / 6)
			tab[i].dist = sqrt(pow(g_map->hero_x - tab[i].x, 2) + pow(g_map->hero_y - tab[i].y, 2));
		else
			tab[i].dist = -1;
	}
	print(g_map->items, "один");
	sort_items_by_dist();
}


