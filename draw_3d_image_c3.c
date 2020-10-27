/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_image_c3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:11:05 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/26 22:01:09 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int dbg = 0;

typedef struct {
	double x;
	double y;
	char type;
	char is_last;
} inter_info_t;

// Based on the left top coord of square, find it's center - sprite coord.
inter_info_t adjust_sprite_coord(inter_info_t info) {
	info.x = info.x + g_map->scale / 2;
	info.y = info.y + g_map->scale / 2;
	return info;
}

inter_info_t	check_intersect(double x, double y, int scale)
{
	char	c;
	char	c1;
	double	y1;
	double	x1;
	int		y_coord;
	int		x_coord;
	int		y_coord1;
	int		x_coord1;
	inter_info_t info = {-1, -1, 0, 0};

	x = x + 0.00001;
	y = y + 0.00001;
	y1 = y - 2 * 0.00001;
	x1 = x - 2 * 0.00001;
	if (y >= g_map->maze_height * scale || x >= g_map->maze_width * scale)
	{
		//printf("%f (%d) %f (%d)\n", x , g_map->maze_width * scale,y, g_map->maze_height * scale);
		y >= g_map->img2->height - 1 ? y = g_map->img2->height : 0; 
		x >= g_map->img2->width - 1 ? x = g_map->img2->width : 0;
		info.type = '1';
		return info;
	}
	else if (y1 < 0 || x1 < 0) {
		info.type = '1';
		return info;
	}
	y_coord = (int)floor(y / scale);
	x_coord = (int)floor(x / scale);
	c = g_map->maze[y_coord][x_coord];
//	printf("xcoord %d, ycoord %d, c %d\n", x_coord, y_coord, c);
	y_coord1 = (int)floor(y1 / scale);
	x_coord1 = (int)floor(x1 / scale);
	c1 = g_map->maze[y_coord1][x_coord1];
//	printf("xcoord1 %d, ycoord1 %d, c1 %d\n", x_coord1, y_coord1, c1);

	// Next iteration will be inside a wall
	if (c == '1' || c == ' ') {
		info.is_last = 1;
	}
	if (c1 == '1' || c1 == ' ') {
		info.is_last = 1;
	}

	// Report sprites first
	if (c == '2') {
		info.x = x_coord * scale;
		info.y = y_coord * scale;
		info.type = '2';
		return info;
	}
	if (c1 == '2') {
		info.x = x_coord1 * scale;
		info.y = y_coord1 * scale;
		info.type = '2';
		return info;
	}
	if (c == '1' || c == ' ') {
		info.type = '1';
		return info;
	}
	if (c1 == '1' || c1 == ' ') {
		info.type = '1';
		return info;
	}
	info.type = c1;
	return (info);
}

void	vertical_cross(t_wall *wall, double angle)
{
	double	x;
	double	y;
	double	step;
	double	step_y;
	double	tg;

	step = g_map->scale;
	if ((angle <= M_PI_2 * 3 && angle >= M_PI_2))
	{
		x = floor(g_map->hero_x / step + 1) * step;
		step *= -1;
	}
	else
		x = floor(g_map->hero_x / step) * step;
	tg = tan(M_PI - angle);
	double c = g_map->hero_y - (g_map->hero_x * tg);
	y = (x * tg) + c;
	step_y = step * tg;
	if (dbg) printf("@vertical_cross: initial x = %f, y = %f, step_y = %f, step_x = %f\n", x, y, step_y, step);
	char first_sprite_met = 0;
	char last_iter = 0;
	while (x < g_map->img2->width)
	{
		x += step;
		y += step_y;
		inter_info_t info = check_intersect(x, y, g_map->scale);
		last_iter = info.is_last;
		wall->number = info.type;
//		printf("angle %f, wall->number: %c\n",angle, wall->number);
		if (wall->number == '2' && !first_sprite_met) {
			info = adjust_sprite_coord(info);
			//printf("sprite center: (%f, %f)\n", info.x, info.y);
			// y = -1/tg * x + cs
			double center_tg = (info.y - g_map->hero_y) / (info.x - g_map->hero_x);
			double cs = info.y + info.x / center_tg;
			// (x0, y0) - intersection of ray and sprite
			//double x0 = tg * (cs - c) / (tg * tg + 1);
			//double y0 = (tg * tg * cs + c) / (tg * tg + 1);
			double x0 = (cs - c) / (tg + 1 / center_tg);
			double y0 = x0 * tg + c;
			double d = sqrt((x0 - info.x) * (x0 - info.x) + (y0 - info.y) * (y0 - info.y));
			const int width_coef = 2;
			double sprite_width = g_map->scale / width_coef;
			char behind_sprite = 1;
			if (angle < M_PI * 3 / 4 && angle >= M_PI * 1 / 4) {
				behind_sprite = g_map->hero_y < info.y ? 1 : 0;
			} else if (angle < M_PI * 5 / 4 && angle >= M_PI * 3 / 4) {
				behind_sprite = g_map->hero_x < info.x ? 1 : 0;
			} else if (angle < M_PI * 7 / 4 && angle >= M_PI * 5 / 4) {
				behind_sprite = g_map->hero_y < info.y ? 0 : 1;
			} else {
				behind_sprite = g_map->hero_x < info.x ? 0 : 1;
			}
//			printf("angle %f, behind sprite %d\n",angle, (int)behind_sprite);
			if (d * 2 <= sprite_width && !behind_sprite) {
				first_sprite_met = 1;
				wall->next->x = x0;
				wall->next->y = y0;
				wall->next->xs = info.x;
				wall->next->ys = info.y;
				wall->next->dist = sqrt(pow(x0 - g_map->hero_x, 2) + pow(y0 - g_map->hero_y, 2));
				if (angle < M_PI * 3 / 4 && angle >= M_PI * 1 / 4) {
					wall->next->d = x0 < info.x ? -d : d;
				} else if (angle < M_PI * 5 / 4 && angle >= M_PI * 3 / 4) {
					wall->next->d = y0 > info.y ? -d : d;
				} else if (angle < M_PI * 7 / 4 && angle >= M_PI * 5 / 4) {
					wall->next->d = x0 < info.x ? d : -d;
				} else {
					wall->next->d = y0 > info.y ? d : -d;
				}
				wall->next->d += sprite_width / 2;
				//printf("@@@@ sprite center: (%f, %f), sprite intersect: (%f, %f), d: %f\n", info.x, info.y,x0,y0,d);
			}
		}
		if (wall->number == '1' || last_iter)
			break ;
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
	double	step_x;
	double	tg;
	double dist;

	step = g_map->scale;
	if (angle >= M_PI && angle < M_PI * 2)
		y = floor(g_map->hero_y / step) * step;
	else
	{
		y = floor(g_map->hero_y / step + 1) * step;
		step *= -1;
	}
	tg = tan(M_PI - angle);
	double c = g_map->hero_y - (g_map->hero_x * tg);
	x = (y / tg) - c / tg;//g_map->hero_x - (g_map->hero_y / tg);
	step_x = step / tg;
	if (dbg) printf("@horizontal_cross: initial x = %f, y = %f, step = %f, step_x = %f\n", x, y, step, step_x);
	char first_sprite_met = 0;
	char last_iter = 0;
	while (y < g_map->img2->height)
	{
		y += step;
		x += step_x;
		inter_info_t info = check_intersect(x, y, g_map->scale);
		last_iter = info.is_last;
		wall->number = info.type;
//		printf("hor angle %f, wall->number: %c\n",angle, wall->number);
		if (wall->number == '2' && !first_sprite_met) {
			info = adjust_sprite_coord(info);
			//printf("sprite center: (%f, %f)\n", info.x, info.y);
			// y = -1/tg * x + cs
			double center_tg = (info.y - g_map->hero_y) / (info.x - g_map->hero_x);
			//printf("ray tg %f, sprite center tg: %f\n", tg, center_tg);
			double cs = info.y + info.x / center_tg;
			// (x0, y0) - intersection of ray and sprite
			//double x0 = tg * (cs - c) / (tg * tg + 1);
			//double y0 = (tg * tg * cs + c) / (tg * tg + 1);
			double x0 = (cs - c) / (tg + 1 / center_tg);
			double y0 = -x0 / center_tg + cs;
			//printf("angle: %f, tg = %f, sprite equasion:  y = x * %f + %f\n", angle, tg, -1/center_tg, cs);
			double d = sqrt((x0 - info.x) * (x0 - info.x) + (y0 - info.y) * (y0 - info.y));
			const int width_coef = 2;
			double sprite_width = g_map->scale / width_coef;
			char behind_sprite = 1;
			if (angle < M_PI * 3 / 4 && angle >= M_PI * 1 / 4) {
				behind_sprite = g_map->hero_y < info.y ? 1 : 0;
			} else if (angle < M_PI * 5 / 4 && angle >= M_PI * 3 / 4) {
				behind_sprite = g_map->hero_x < info.x ? 1 : 0;
			} else if (angle < M_PI * 7 / 4 && angle >= M_PI * 5 / 4) {
				behind_sprite = g_map->hero_y < info.y ? 0 : 1;
			} else {
				behind_sprite = g_map->hero_x < info.x ? 0 : 1;
			}
//			printf("hor angle %f, behind sprite %d\n",angle, (int)behind_sprite);
			if (d * 2 <= sprite_width && !behind_sprite) {
				first_sprite_met = 1;
				double sprite_dist = sqrt(pow(x0 - g_map->hero_x, 2) + pow(y0 - g_map->hero_y, 2));
				if (sprite_dist < wall->next->dist || wall->next->x < 0) {
					wall->next->x = x0;
					wall->next->y = y0;
					wall->next->xs = info.x;
					wall->next->ys = info.y;
					wall->next->dist = sprite_dist;
					if (angle < M_PI * 3 / 4 && angle >= M_PI * 1 / 4) {
						wall->next->d = x0 < info.x ? -d : d;
					} else if (angle < M_PI * 5 / 4 && angle >= M_PI * 3 / 4) {
						wall->next->d = y0 > info.y ? -d : d;
					} else if (angle < M_PI * 7 / 4 && angle >= M_PI * 5 / 4) {
						wall->next->d = x0 < info.x ? d : -d;
					} else {
						wall->next->d = y0 > info.y ? d : -d;
					}
					wall->next->d += sprite_width / 2;
					//printf("dist: %f, hero_x: %f, hero_y: %f\n", sprite_dist, g_map->hero_x, g_map->hero_y);
				}
				//printf("#### sprite center: (%f, %f), sprite intersect: (%f, %f), d: %f\n", info.x, info.y,x0,y0,d);
			}
		}
		if (wall->number == '1' || last_iter)
			break ;
	}
	dist = sqrt(pow(x - g_map->hero_x, 2) + pow(y - g_map->hero_y, 2));
	if (dist < wall->dist)
	{
		wall->dist = dist;
		wall->x = x;
		wall->y = y;
		if (angle >= 0 && angle < M_PI)
			wall->type = 'N';
		else
			wall->type = 'S';
	}
	if (dbg) printf("@horizontal_cross: crosss x = %f, y = %f\n", x, y);
}

void	get_wall_inf(double angle, t_wall *wall)
{
	g_map->status = 12;
	if (angle < 0)
		angle += (M_PI) * 2;
	else if (angle >= M_PI * 2)
		angle -= (M_PI * 2);
	vertical_cross(wall, angle);
	if (dbg) printf("xh = %f, yh = %f;   wall %c dist: %f\n", g_map->hero_x, g_map->hero_y, wall->type, wall->dist);
	horizontal_cross(wall, angle);
//	if (dbg) printf("wall dist: %f. item dist: %f\n", wall->dist, wall->next->dist);
	if (dbg) printf("xh = %f, yh = %f;   wall %c dist: %f\n", g_map->hero_x, g_map->hero_y, wall->type, wall->dist);
}

void	paint_ceil_floor(int x0, int y_skyline, int max)
{
	int	i;
	int	i_max;

	i_max = y_skyline - max;
	i = 0;
	while (++i <= i_max)
	{
		img_pixel_put(g_map->img2, x0, i, g_map->ceil);
		img_pixel_put(g_map->img2, x0, g_map->img2->height - i, g_map->floor);
	}
}

void	calculate_height(t_wall *wall, double angle)
{
	const int walls_height = g_map->img2->height;
	const int sprites_height = walls_height / 2;
	wall->dist *= cos(g_map->hero_direction - angle);
	wall->actual_height =
		ceil((g_map->scale * walls_height) / (wall->dist * 0.7));
	wall->height = wall->actual_height > g_map->img2->height ?
		g_map->img2->height : wall->actual_height;
	wall->height < 64 ? wall->height = 64 : 0;

	if (wall->next->x < 0) {
		return;
	}
	wall->next->dist *= cos(g_map->hero_direction - angle);
	wall->next->actual_height =
		ceil((g_map->scale * sprites_height) / (wall->next->dist * 0.7));
	wall->next->height = wall->next->actual_height > walls_height ?
		walls_height : wall->next->actual_height;
	//printf("wall height: %f, sprite_dist: %f, sprite_height: %f\n", wall->height, wall->next->dist, wall->next->height);

}

void	draw_section(int x0, int x1, double angle)
{
	t_wall	wall;
	t_sprite	sprite;

	sprite.x = -1;
	wall.next = &sprite;

	g_map->status = 15;
	get_wall_inf(angle, &wall);
	calculate_height(&wall, angle);
	while (x0 < x1)
	{
		paint_ceil_floor(x0, g_map->img2->height / 2, wall.height / 2);
		apply_texture(x0, x1, &wall);
//		if (wall.next.x > 0)//
//			put_sprite(&wall.next);//
		x0++;
	}
	if (dbg)
		printf("dist: %f wall->height: %f\n", wall.dist, wall.height);//
}

void	draw_3d_image()
{
	double	r_min;
	double	r_max;
	int		rays_number;
	int		i;

	g_map->status = 11;
	new_image(g_map->img2, g_map->res_width, g_map->res_height);
	rays_number = g_map->img2->width / PPR;
	g_map->section_width = g_map->img2->width / rays_number;	
	r_min = (g_map->hero_direction - ANGLE_OV / 2);
	r_max = (g_map->hero_direction + ANGLE_OV / 2);
	i = 0;
	if (dbg)
		printf("================================\n");//
	while (i < g_map->img2->width)
	{
		if (dbg)
			printf(" --- ");//
		draw_section(i, i + g_map->section_width, r_max);
		i += g_map->section_width;
		r_max -= (M_PI / 3) / rays_number;
	}
//	put_items();
	if (g_map->screenshot_needed == 0)
		put_image_to_window(g_map->img2, 0, 0);
	else
		save_in_bmp(g_map->img2);
	mlx_destroy_image(g_mlx_ptr, g_map->img2->ptr);
}
