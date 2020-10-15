/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_c3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 19:17:14 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/15 10:59:44 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*get_texture(char *filename)
{
	t_img	*img;
	
	img = malloc(sizeof(t_img));
	if (!img)
		set_error_and_exit("Не выделена память для текстур");
	img->ptr = mlx_xpm_file_to_image(g_mlx_ptr, filename, &img->width, &img->height);
	img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
			   &img->size_line, &img->endian);
	if (!img)
		set_error_and_exit("Ошибка чтения файла"); return (img);
}

void	dl_textures()
{
	g_map->NO = get_texture(g_map->path_NO);
	g_map->SO = get_texture(g_map->path_SO);
	g_map->EA = get_texture(g_map->path_EA);
	g_map->WE = get_texture(g_map->path_WE);
}

double	west_east_texture(t_wall *wall)
{
	double i =  wall->y / g_map->scale;
	while (i > 1)
		i -= 1.;
	return i * wall->texture_ptr->width;
}
double	north_south_texture(t_wall *wall)
{
	int x0;
	int x1;
	int	y;

	double i =  wall->x / g_map->scale;
	while (i > 1)
		i -= 1.;
	return i * wall->texture_ptr->width;
}

double		get_column_number(t_wall *wall)
{
	double coeff;

	return (wall->type == 'S' || wall->type == 'N' ?
		north_south_texture(wall) : west_east_texture(wall));
}

void	apply_texture(int x, int delete_later, t_wall *wall)
{
	double			scale_y;
	int				y;
	int				j;
	int				y_start;
	int	y_end;

	if (wall->type == 'N') 
		wall->texture_ptr = g_map->NO;
	else if (wall->type == 'S')
		wall->texture_ptr = g_map->SO;
	else if (wall->type == 'W')
		wall->texture_ptr = g_map->WE;
	else
		wall->texture_ptr = g_map->EA;
	if (wall->texture_ptr != g_map->previous_texture_ptr)
	g_map->column_number = 0;
	g_map->column_number = (int)floor(get_column_number(wall));
	y_start = (g_map->img2->height - wall->height) / 2;
	y_end = y_start + wall->height;
	scale_y = floor(wall->height / wall->texture_ptr->height);
	y = -1;
	int i = -1;
	while (++i <= wall->height)
	{
		int xx = g_map->column_number * wall->texture_ptr->bits_per_pixel / 8;
		int yy = round((double)i / wall->actual_height * wall->texture_ptr->height) * wall->texture_ptr->size_line;
		void *ptr = wall->texture_ptr->addr + xx + yy;
//		printf("%p, i = %d xx = %d yy = %d x = %d y = %d pixel = %x\n", ptr, i, xx, yy, x, y_start, *(unsigned int*)ptr);
//		printf("%p, i = %d xx = %d yy = %d x = %d y = %d pixel = %x\n", ptr, i, xx, yy, x, y_start, *(unsigned int*)ptr);
		img_pixel_put(g_map->img2, x, i + y_start, *(unsigned int *)ptr);
	}

/*	
	j = -1;
	while (++j < wall->texture_ptr->height)
	{
		int xx = g_map->column_number * wall->texture_ptr->bits_per_pixel / 8;
		int yy = j * wall->texture_ptr->size_line;
		void *ptr = wall->texture_ptr->addr + xx + yy;
		printf("%p, i = %d xx = %d yy = %d x = %d y = %d pixel = %x\n", ptr, j, xx, yy, x, y_start, *(unsigned int*)ptr);
		int k = -1;
		while (++k < scale_y && y_start < y_end)
		{
			img_pixel_put(g_map->img2, x, y_start++, *(unsigned int *)ptr);
			int piska = (wall->height - (scale_y * wall->texture_ptr->height));
			int	a = wall->height / piska;
			if (k % a == 0)
				img_pixel_put(g_map->img2, x, y_start++, *(unsigned int *)ptr);	
		}
	}
*/

	g_map->previous_texture_ptr = wall->texture_ptr;
	if (++g_map->column_counter >= scale_y)
	{	
		g_map->column_number++;
		g_map->column_counter = 0;
	}
	free(wall);
}
//	ptr = img->addr + (x * img->bits_per_pixel / 8) + (y * img->size_line);
//unsigned int	mlx_get_color_value(void *mlx_ptr, int color);
