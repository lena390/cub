/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_c3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 18:57:58 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/15 20:11:27 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_item(double x, double y, double angle, int flag)
{
	double	*tab_new;
	double	*tab;
	static int	capacity;
	static int	size;
	int 		i;

	g_map->status = 13;
	tab = g_map->sp_location;
	if (flag == 1)
	{
		capacity = 1000;
		size = 1;
		g_map->sp_location = ft_malloc(sizeof(double) * capacity);
		tab = g_map->sp_location;
		return ;
	}
	if (size == capacity)
	{
		capacity *= 2;
		tab_new = ft_malloc(sizeof(double) * capacity);
		i = -1;
		while (++i < size)
			tab_new[i] = tab[i];
		free(tab);
		g_map->sp_location = tab_new;
		tab = tab_new;
	}
	tab[size++] = x;
	tab[size++] = cos(g_map->hero_direction - angle) *
		(sqrt(pow(x - g_map->hero_x, 2) + pow(y - g_map->hero_y, 2)));
	tab[0] = size;
}

void	put_item(t_img *img, int sp_height, int sp_x)
{
	int x, y;
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
	}
}

void	put_items_to_image()
{
	int		i0;
	int		i1;
	double	sp_width;
	double	sp_height;
	double	*tab;

	int i = 1;
	while (i < (int)g_map->sp_location[0] - 1)
		printf("%f\n", g_map->sp_location[i++]);
	//	printf("%f %f\n", g_map->sp_location[i++], g_map->sp_location[i++]);
	free(g_map->sp_location);
	return ;
	/*
	tab = g_map->sp_location;
	g_map->status = 16;
	i1 = tab[1];
	i0 = 2;
	while (i0 < i1)
	{
		//sp_height = ceil((g_map->scale * g_map->img2->height) / (4 * (tab[i0])));
		sp_height = 50;
		sp_width = 0;//написать что-нибудь
		put_item(g_map->img2, ceil(sp_height), ceil(tab[i0 + 1]));
		i0 += 2;
	}
	free(tab);
	*/
}

