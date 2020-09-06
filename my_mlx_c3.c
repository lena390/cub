/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_c3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 17:59:11 by miphigen          #+#    #+#             */
/*   Updated: 2020/09/01 16:05:25 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" 

void	new_image(t_img *img, int width, int height)
{
	int i;

	img->ptr = mlx_new_image(g_mlx_ptr, width, height);
	if (img->ptr)
	{
		img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel, &img->size_line, &img->endian);
		img->width = width;
		img->height = height;
		i = 0;
	}
}

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	void	*ptr;

	ptr = img->addr + (x * img->bits_per_pixel / 8) + (y * img->size_line);
	*(unsigned int *)ptr = color;
}

void	put_image_to_window(t_img *img, int x, int y)
{	
	
	mlx_put_image_to_window(g_mlx_ptr, g_win_ptr, img->ptr, x, y);
	mlx_do_sync(g_mlx_ptr);
}
int	mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr,
				int x, int y);

int	loop_hook(void *param)
{

	return (0);
}
