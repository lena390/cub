/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_c3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 18:57:58 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/17 23:31:04 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_item(double x, double y, double angle, int flag)
{
	t_items		*tab_new;
	t_items		*tab;
	static int	capacity;
	static int	size;
	int 		i;

	tab = &(g_map->items[0]);
	g_map->status = 13;
	if (flag == 1)
	{
		capacity = 1000;
		size = 0;
	//	tab[0].size = size;
		g_map->items = ft_malloc(sizeof(t_items) * capacity);
		return ;
	}
	if (size == capacity)
	{
		capacity *= 2;
		tab_new = ft_malloc(sizeof(t_items) * capacity);
		i = -1;
		while (++i < size)
		{	
			tab_new[i].x = tab[i].x;
			tab_new[i].dist = tab[i].dist;
//			printf("tab_new = %p, end = %p\n", tab_new, (char*)tab_new + sizeof(double) * capacity);
//			printf("i = %d, size = %d, capacity = %d, tab_new[i] = %p\n", i, size, capacity, tab_new + i);
		}
		free(tab);
		g_map->items = tab_new;
		tab = tab_new;
	}
	tab[size].x = x;
	tab[size++].dist = cos(g_map->hero_direction - angle) *
		(sqrt(pow(x - g_map->hero_x, 2) + pow(y - g_map->hero_y, 2)));
	tab[0].size = size;
}

void	put_item()//(t_img *img, t_items *item)
{
	puts("put");
	return ;
	int x, y;/*
	y = g_map->res_height * 0.5;
	while (y < sp_height + g_map->res_width * 0.5)
	{
		x = sp_x;
		while (x < sp_height + sp_x)
		{
			img_pixel_put(img, x, y, 0);
			x++;
			
		}
		y++;
	}*/
}

void	sort(t_items *tab)
{
	return;
}

void	put_items_to_image()
{
	int		i0;
	int		i1;
	double	sp_width;
	double	sp_height;
	t_items	*tab;

	
	int i = -1;
	while (++i < 20)
		printf("size: %d, x = %f dist = %f\n", g_map->items[i].size, g_map->items[i].x, g_map->items[i].dist);
	return;
	tab = &g_map->items[0];
	sort(tab);//от большего к меньшему
	i = -1;
	while (++i < tab[0].size)//
		put_item();
	free(tab);
}

