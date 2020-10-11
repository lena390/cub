/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_c3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 18:57:58 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/11 18:59:07 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_sprite(t_map *map, double x_start, double dist, int	flag)
{
	double	*tab_new;
	double	*tab;
	static int	capacity;
	static int	size;
	int 		i;

	map->status = 13;
	tab = map->sp_location;
	if (flag == 1)
	{
		capacity = 20;
		size = 0;
		map->sp_location = malloc(sizeof(double) * 20);
		tab = map->sp_location;
		if (!tab) set_error_and_exit("Memory allocation failure", map); 
		return ;
	}
	if (size == capacity)
	{
		capacity *= 2;
		tab_new = malloc(sizeof(double) * capacity);
		if (!tab_new) set_error_and_exit("Memory allocation failure", map); 
		i = -1;
		while (++i < size)
			tab_new[i] = tab[i];
		free(tab);
		map->sp_location = tab_new;
		tab = tab_new;
	}
	tab[size++] = dist;
	tab[size++] = x_start;
}

void	put_sprite(t_map *map, t_img *img, int sp_height, int sp_x)
{
	int x, y;
	y = map->res_height * 0.5;
	while (y < sp_height + map->res_width * 0.5)
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

void	put_sprites_to_image(t_map *map)
{
	int		i0;
	int		i1;
	double	sp_width;
	double	sp_height;
	double	*tab;

	map->status = 16;
	tab = map->sp_location;
	i1 = tab[1];
	i0 = 2;
	while (i0 < i1)
	{
		//sp_height = ceil((map->scale * map->img2->height) / (4 * (tab[i0])));
		sp_height = 50;
		sp_width = 0;//написать что-нибудь
		put_sprite(map, map->img2, ceil(sp_height), ceil(tab[i0 + 1]));
		i0 += 2;
	}
	free(tab);
}

