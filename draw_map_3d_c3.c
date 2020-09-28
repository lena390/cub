/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_3d_c3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:11:05 by miphigen          #+#    #+#             */
/*   Updated: 2020/09/28 20:47:30 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double		get_ray_length(t_map *map, double x0, double y0, double angle)
{
	double	x1;
	double	y1;
	double	i;	
	double	x;
	double	y;

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
		if (!wall_ahead(map, x + map->hero_x, y + map->hero_y))
		{
			x1 = x;
			y1 = y;
		}
		else
			break;
		i += 2;
	}
	while (1)
	{
		x = fabs(cos(angle)) * i;
		y = fabs(sin(angle)) * i;
		mh_correct_values(angle, &x, &y);
		if (!wall_ahead(map, x + map->hero_x, y + map->hero_y))
		{
			x1 = x;
			y1 = y;
		}
		else
			break;
		i += 0.4;
	}
	double dist = sqrt(pow(x1, 2) + pow(y1, 2));
//	printf("dist = %f\n", dist);
	//dist = (fabs((x1) / cos(angle)));
	return dist;
}

void	draw_section(t_map *map, int x0, int x1, float dist)
{
	t_img	*img;
	int		i;
	unsigned int	wall_h;
	int		y_skyline;
	int		wall_max_h;
	int		color_wall = 0xff5c77;
	
	wall_h = ceil((map->scale * map->img2->height) / (dist));
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
		while (++i < wall_h / 2)
		{
			img_pixel_put(map->img2, x0, y_skyline + i + 1, color_wall);
			img_pixel_put(map->img2, x0, y_skyline - i, color_wall);
		}
		x0++;
	}
}

void	draw_map_3d(t_map *map)
{
	int		section_width;
	double	d_min;
	double	d_max;
	int		rays_number;
	int		i;

	new_image(map->img2, map->res_width, map->res_height);
	rays_number = map->img2->width / 3;
	section_width = map->img2->width / rays_number;
	d_min = (map->hero_direction - ANGLE_OV / 2);
	d_max= (map->hero_direction + ANGLE_OV / 2);
	i = 0;
	while (d_max >= d_min)
	{
		draw_section(map, i, i + section_width,	get_ray_length(map, map->hero_x, map->hero_y, d_max));
		i += section_width;
		d_max -= (M_PI / 3) / rays_number;
	}
//	mlx_do_sync(g_mlx_ptr);
	put_image_to_window(map->img2, 0, 0);
//	draw_map_2d(map);
	put_image_to_window(&map->img, 0, map->res_height / 4 * 3 );
	mlx_destroy_image(g_mlx_ptr, map->img2->ptr);

}
