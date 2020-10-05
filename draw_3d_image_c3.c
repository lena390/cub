/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_image_c3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:11:05 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/04 22:41:40 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_wall		get_wall_inf_loop(t_map *map, double x0, double y0, double angle)
{
	static int	i;
}

void	_add_sprite(t_map *map, double x_start, double dist)
{
	double	*tab_new;
	double	*tab;
	static int	capacity = 20;
	static int	size = 0;
int i;
	tab = map->sp_location;
	i = (int)ceil(tab[1]);
	if (ceil(x_start) == i - 2 && dist == tab[i - 1])
		return ;
	if (tab[0] == tab[1])
	{
		tab_new = malloc(sizeof(double) * (tab[0] * 2));
		i = ceil(tab[0]);
		while (--i)
			tab_new[i] = tab[i];
		tab_new[0] = tab[0] * 2;
		free(map->sp_location);
		map->sp_location = tab_new;
		tab = tab_new;
	}
	tab[i++] = dist;
	tab[i++] = x_start;
	tab[1] = (double)i;
//	printf("i = %f, tab[1] = %f, x_start = %f, dist = %f\n", i, tab[1], x_start, dist);
}

void	add_sprite(t_map *map, double x_start, double dist, int	flag)
{
	double	*tab_new;
	double	*tab;
	static int	capacity;
	static int	size;
	int 		i;

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
	if (ceil(tab[size - 1]) == ceil(dist))
		return ;
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
/*
t_wall	_get_wall_info(t_map *map, double x0, double y0, double angle)//slow ver
{
	double	x1;
	double	y1;
	double	i;
	double	x;
	double	y;
	t_wall	wall;

	if (angle < 0)
		angle += (M_PI) * 2;
	else if (angle >= M_PI * 2)
		angle -= (M_PI * 2);
	x1 = 0;
	y1 = 0;
	i = 2;
	while (1)
	{
		x = fabs(cos(angle)) * STEP * i;
		y = fabs(sin(angle)) * STEP * i;
		mh_correct_values(angle, &x, &y);
		if (wall.type = move_on(map, x + map->hero_x, y + map->hero_y))
		{
			x1 = x;
			y1 = y;
		}
		else
			break;
		i += 2;
	}
	int j;
	while (1)
	{
		x = fabs(cos(angle)) * i;
		y = fabs(sin(angle)) * i;
		mh_correct_values(angle, &x, &y);
		if ((wall.type = movew_on(map, x + map->hero_x, y + map->hero_y)))
		{
			x1 = x;
			y1 = y;
		}
		else
			break;
		i += 0.35;
	}
	wall.dist = sqrt(pow(x1, 2) + pow(y1, 2));
	
//	printf("wall = %d, angle = %f, dist = %f\n", j, angle / (M_PI / 180), dist);
	//dist = (fabs((x1) / cos(angle)));
	return wall;
}
*/
t_wall	get_wall_inf_and_collect_sprite_loc(t_map *map, double x1, double y1, double angle)
{
	double	i;
	double	x;
	double	y;
	t_wall	wall;
	double	step;

	if (angle < 0)
		angle += (M_PI) * 2;
	else if (angle >= M_PI * 2)
		angle -= (M_PI * 2);
	i = 0;
	step = STEP;
	if (angle == 0) angle + ROTATION_SPEED; 
	double tg = fabs(tan(angle));
	while ((i + 0.03))
	{
		y = i;
		x = y / tg;
		mh_correct_values(angle, &x, &y);
		if ((wall.type = move_on(map, x + map->hero_x, y + map->hero_y, map->scale)))
		{
			x1 = x;
			y1 = y;
			if (wall.type == 2);
				add_sprite(map, fabs(x1), sqrt(pow(x1, 2) + pow(y1, 2)), 0);
		}
		else
			break;
		i += 1;
	}
	wall.dist = sqrt(pow(x1, 2) + pow(y1, 2));	
	return wall;
}

void	draw_section(t_map *map, int x0, int x1, t_wall wall)
{
	t_img	*img;
	int		i;
	unsigned int	wall_h;
	int		y_skyline;
	int		wall_max_h;
	int		color_wall = 0xff5c77;
	
//	add_sprite(map, *wall);
	wall_h = ceil((map->scale * map->img2->height) / (wall.dist));
	wall_max_h = map->img2->height;
	wall_h >= wall_max_h ? (wall_h = wall_max_h) : 0;
	y_skyline = map->img2->height / 2;
	while (x0 < x1)
	{
		i = -1;
		while (++i <= y_skyline - wall_h / 2)
		{
			img_pixel_put(map->img2, x0, i, map->ceil);
			img_pixel_put(map->img2, x0, map->img2->height - i, map->floor);
		}
		i = -1;
		if (wall.type == 1);//общая на все типы стен ф-ция натягивания текстуры(тип стены, ссылка на текстуру)
		while (++i < wall_h / 2)
		{
			img_pixel_put(map->img2, x0, y_skyline + i + 1, color_wall);
			img_pixel_put(map->img2, x0, y_skyline - i, color_wall);
		}
		x0++;
	}
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

void	draw_3d_image(t_map *map)
{
	double	r_min;
	double	r_max;
	int		rays_number;
	int		i;

	new_image(map->img2, map->res_width, map->res_height);
	rays_number = map->img2->width / PPR;
	map->section_width = map->img2->width / rays_number;
	r_min = (map->hero_direction - ANGLE_OV / 2);
	r_max= (map->hero_direction + ANGLE_OV / 2);
	add_sprite(map, 0, 0, 1);
	i = 0;
	while (r_max >= r_min)
	{	
		draw_section(map, i, i + map->section_width,
			get_wall_inf_and_collect_sprite_loc(map, map->hero_x, map->hero_y, r_max));
		i += map->section_width;
		r_max -= (M_PI / 3) / rays_number;
	}
	//2put_sprites_to_image(map);
	put_image_to_window(map->img2, 0, 0);
	draw_2d_image(map);
//	put_image_to_window(&map->img, 0, 0);
	mlx_destroy_image(g_mlx_ptr, map->img2->ptr);

}
