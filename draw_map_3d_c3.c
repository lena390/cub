/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_3d_c3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:11:05 by miphigen          #+#    #+#             */
/*   Updated: 2020/09/23 00:21:03 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double		get_ray_length(t_map *map, int x, int y, double angle)//до изменений
{
	double	tg;
	double	x0;
	double	y0;
	double	i;
//printf("%f %d %d\n", angle/M_PI, x, y);
	if (angle == 0 || angle == M_PI_2 || angle == M_PI || angle == M_PI + M_PI_2 || angle == M_PI * 2)
		angle += 0.01;
	if (angle < 0)
		angle = angle + M_PI * 2;
	else if (angle >= M_PI * 2)
		angle = angle - M_PI * 2;
	tg = tan(angle);
	i = 0.0;
	while (i > -1)
	{
		x0 = i;
		y0 = i;
		if ((angle >= M_PI_4 && angle < M_PI_4 * 3) || (angle >= (M_PI + M_PI_4) && angle < (M_PI * 2 - M_PI_4)))
			x0 = fabs(y0 / tg);//for horizontal lines)
		else
			y0 = fabs(x0 * tg);//for vertical lines*/
		if (angle > 0 && angle < M_PI)
			y0 = -y0;
		if (angle > M_PI_2 && angle < M_PI_2 * 3)
			x0 = -x0;
		x0 = (x + x0);
		y0 = (y + y0);
		if (y0 / map->scale >= map->maze_height ||
			x0 / map->scale >= map->maze_width ||
			y0 / map->scale < 0 || x0 < map->scale ||
			map->maze[(int)y0 / map->scale][(int)x0 / map->scale] != '0')
			break;
		i = i + 0.5;
	}

	float dist_cos = (fabs((x0 - x) / cos(angle)));
//	float dist_sqrt = (sqrt(pow(x0 - x, 2) + pow(y0 - y, 2)));
//	printf("angle%f x%d y%d dist%f ", angle, (int)(x0)/map->scale, (int)(y0)/map->scale, dist_sqrt);
	return dist_cos;
//	return (fabs((x0) / cos(angle)));
/*	
	if ((angle >= 45 && angle < 135) || (angle >= 225 && angle < 315))
		return (fabs(y0 - y));//for horizontal lines)
	else
		return (fabs(x0 - x));//for vertical lines));
*/
}

void	draw_section(t_map *map, int x0, int x1, float dist)
{
	t_img	*img;
	int		i;
	unsigned int	wall_h;
	int		y_skyline;
	int		wall_max_h;
	int		color = 0xff5c77;

	wall_h = ceil((map->scale * map->img2->height) / (dist));
	wall_max_h = map->img2->height;
	wall_h >= wall_max_h ? (wall_h = wall_max_h) : 0;
//printf("wall_h %d\n", wall_h);
	y_skyline = map->img2->height / 2;
//	printf("dist = %d\n", (int)dist);
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
			img_pixel_put(map->img2, x0, y_skyline + i + 1, color);
			img_pixel_put(map->img2, x0, y_skyline - i, color);
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

	draw_map_2d(map);
	new_image(map->img2, map->res_width, map->res_height);
//	printf("new 3d image, central ray %d\n", map->hero_direction);
	rays_number = map->img2->width / 4;
	section_width = map->img2->width / rays_number;
	d_min = (map->hero_direction - ANGLE_OV / 2) / (180.0 / M_PI);
	d_max= (map->hero_direction + ANGLE_OV / 2) / (180.0 / M_PI);
	i = 0;
	while (d_max >= d_min)
	{
		draw_section(map, i, i + section_width,	get_ray_length(map, map->hero_x, map->hero_y, d_max));
		i += section_width;
		d_max -= (M_PI / 3) / rays_number;
	}
	mlx_do_sync(g_mlx_ptr);
	put_image_to_window(map->img2, 0, 0);
	put_image_to_window(&map->img, 0, map->res_height / 4 * 3 );
	mlx_destroy_image(g_mlx_ptr, map->img2->ptr);

}
