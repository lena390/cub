/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_image_c3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:11:05 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/15 07:25:31 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int dbg = 0;

char	check_intersect(double x, double y, int scale, double xshift, double yshift)
{
	char c;
	x = x + xshift;
	y = y + yshift;
	double y1 = y - 2 * yshift;
	double x1 = x - 2 * xshift;

	if (y >= g_map->maze_height * scale || x >= g_map->maze_width * scale)
	{
		y >= g_map->img2->height - 1 ? y = g_map->img2->height : 0 ; 
		x >= g_map->img2->width - 1 ? x = g_map->img2->width : 0;
		return ('1');
	}
	else if (y1 < 0 || x1 < 0)
		return ('1');
	int y_coord = (int)floor(y / scale);
	int x_coord = (int)floor(x / scale);
	c = g_map->maze[y_coord][x_coord];
	if (c == '1' || c == ' ')
		return ('1');
	y_coord = (int)floor(y1 / scale);
	x_coord = (int)floor(x1 / scale);
	c = g_map->maze[y_coord][x_coord];
	if (c == '1' || c == ' ')
		return ('1');
	return (0);
}

void	get_int_for_textures(t_wall *wall, double x, double angle)
{
	
}

void	vertical_cross(t_wall *wall, double angle)
{
	double	x;
	double	y;
	double	step;
	double	tg;

	step = g_map->scale;
	tg = tan(angle - M_PI / 2);
	if ((angle <= M_PI_2 * 3 && angle >= M_PI_2)) {
		x = floor(g_map->hero_x / step + 1) * step;
		step *= -1;
	}
	else
		x = floor(g_map->hero_x / step) * step;
	y = (x / tg) + g_map->hero_y - (g_map->hero_x / tg);
	double step_y = step / tg;//
	if (dbg) printf("@vertical_cross: initial x = %f, y = %f, step_y = %f, step_x = %f\n", x, y, step_y, step);
	while (x < g_map->img2->width)
	{
		x += step;
		y += step_y;
		wall->type = check_intersect(x, y, g_map->scale, 0.5, 0.5);
		if (wall->type == '1')
			break;
		if (wall->type == '2');//add sprite
	}
	wall->x = x;
	wall->y = y;
	if (dbg) printf("@vertical_cross: crosss x = %f, y = %f\n", x, y);
	wall->dist = sqrt(pow(x - g_map->hero_x, 2) + pow(y - g_map->hero_y, 2));
	if (angle >= M_PI_2 && angle < M_PI_2 * 3)
		wall->type = 'W';
	else
		wall->type = 'E';
}

void	horizontal_cross(t_wall *wall, double angle)
{
	double	x;
	double	y;
	double	step;
	double	tg;

	step = g_map->scale;
	tg = tan(M_PI - angle);
	if (angle >= M_PI && angle < M_PI * 2)
		y = floor(g_map->hero_y / step) * step;
	else
	{
		y = floor(g_map->hero_y / step + 1) * step;
		step *= -1;
	}
	x = (y / tg) + g_map->hero_x - (g_map->hero_y / tg);
	double step_x = step / tg;//
	if (dbg) printf("@horizontal_cross: initial x = %f, y = %f, step = %f, step_x = %f\n", x, y, step, step_x);
	while (y < g_map->img2->height)
	{
		y += step;
		x += step_x;
		wall->type = check_intersect(x, y, g_map->scale, 0.5, 0.5);
		if (wall->type == '1')
			break;
		if (wall->type == '2');//add sprite
	}
	wall->x = x;
	wall->y = y;
	if (dbg) printf("@horizontal_cross: crosss x = %f, y = %f\n", x, y);
	wall->dist = sqrt(pow(x - g_map->hero_x, 2) + pow(y - g_map->hero_y, 2));
if (angle >= 0 && angle < M_PI)
		wall->type = 'N';
	else
		wall->type = 'S';
}

t_wall	*get_wall_inf_and_collect_sprite_loc(double angle, double next)
{
	t_wall	*wall1;
	t_wall	*wall2;

	wall1 = ft_malloc(sizeof(t_wall));
	wall2 = ft_malloc(sizeof(t_wall));
	g_map->status = 12;
	if (angle < 0)
		angle += (M_PI) * 2;
	else if (angle >= M_PI * 2)
		angle -= (M_PI * 2);
	horizontal_cross(wall1, angle);
	vertical_cross(wall2, angle);
	if (dbg) printf("wall1 dist: %f. wall2 dist: %f\n", wall1->dist, wall2->dist);
	if (wall1->dist > wall2->dist)
	{
		free(wall1);
		wall1 = wall2;
	}
	if (dbg) printf("xh = %f, yh = %f;   wall1 %c dist: %f\n", g_map->hero_x, g_map->hero_y, wall1->type, wall1->dist);
//	wall1->x = cos(angle);
	wall1->dist *= cos(g_map->hero_direction - angle);
	return (wall1);
}

void	draw_section(int x0, int x1, t_wall *wall)
{
	t_img			*img;
	int				i;
	unsigned int	wall_h;
	int				y_skyline;
int	color_wall;
	g_map->status = 15;
	wall->height = ceil((g_map->scale * g_map->img2->height) / (wall->dist * 0.7));
	wall->height >= g_map->img2->height? wall->height = g_map->img2->height : 0;
	wall->height < 64 ? wall_h = 64 : 0;
	y_skyline = g_map->img2->height / 2;	
	if (wall->type == 'N')
		color_wall = 0x40d2ff;
	else if (wall->type == 'S')
		color_wall = 0xff5940;
	else if (wall->type == 'W')
		color_wall = 0xdbff5b;
	else
		color_wall = 0xfd85ff;
	while (x0 < x1)
	{
		i = 0;
		while (++i <= y_skyline - wall->height / 2 + 1)
		{
			img_pixel_put(g_map->img2, x0, i, g_map->ceil);
			img_pixel_put(g_map->img2, x0, g_map->img2->height - i, g_map->floor);
		}
		i = -1;
		while (++i < wall->height / 2 - 1)
		{
			img_pixel_put(g_map->img2, x0, y_skyline + i + 1, color_wall);
			img_pixel_put(g_map->img2, x0, y_skyline - i, color_wall);
		}
		x0++;
	apply_texture(x0 - 1, x1, wall);
	}
	if (dbg) printf("dist: %f wall->height: %f\n", wall->dist, wall->height);
}

void	draw_3d_image()
{
	double	r_min;
	double	r_max;
	int		rays_number;
	int		i;
	double f = M_PI / 180;
	g_map->status = 11;
	new_image(g_map->img2, g_map->res_width, g_map->res_height);
	rays_number = g_map->img2->width / PPR;
	g_map->section_width = g_map->img2->width / rays_number;
	r_min = (g_map->hero_direction - ANGLE_OV / 2);
	r_max = (g_map->hero_direction + ANGLE_OV / 2);
//	add_sprite(0, 0, 1);
	i = 0;
	if (dbg) printf("================================\n");
	while (i < g_map->img2->width)
	{	
		if (dbg) printf(" --- ");
		draw_section(i, i + g_map->section_width,
			get_wall_inf_and_collect_sprite_loc(r_max, (M_PI / 3) / rays_number));
		i += g_map->section_width;
		r_max -= (M_PI / 3) / rays_number;
	}
//	apply_texture(g_map, img22);
	//2put_sprites_to_image(g_map);
	put_image_to_window(g_map->img2, 0, 0);
	mlx_destroy_image(g_mlx_ptr, g_map->img2->ptr);

}
