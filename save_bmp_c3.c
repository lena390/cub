/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp_c3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 13:47:04 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/21 22:25:39 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bmp_file_header	get_bfh(void)
{
	t_bmp_file_header	bfh;
	int32_t				*ptr;

	bfh.type = 0x4D42;
	ptr = (int32_t *)&bfh.size1;
	*ptr = (sizeof(t_bmp_file_header) + sizeof(t_bmp_info_header) +
		g_map->img2->width * g_map->img2->height * 4);
	bfh.reserved1 = 0;
	bfh.reserved2 = 0;
	bfh.off_bits1 = sizeof(t_bmp_file_header) + sizeof(t_bmp_info_header);
	return (bfh);
}

t_bmp_info_header	get_bih(void)
{
	t_bmp_info_header	bih;

	bih.size = sizeof(bih);
	bih.width = g_map->img2->width;
	bih.height = -g_map->img2->height;
	bih.planes = 1;
	bih.bit_count = g_map->img2->bits_per_pixel;
	bih.compression = 0;
	bih.size_image = 0;
	bih.x_pels_per_meter = 0;
	bih.y_pels_per_meter = 0;
	bih.clr_used = 0;
	bih.clr_important = 0;
	return (bih);
}

void				save_in_bmp(t_img *img)
{
	int					fd;
	t_bmp_file_header	bfh;
	t_bmp_info_header	bih;

	bfh = get_bfh();
	bih = get_bih();
	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	write(fd, (void *)&bfh, sizeof(bfh));
	write(fd, (void *)&bih, sizeof(bih));
	write(fd, (void *)img->addr, img->width * img->height * 4);
	mlx_destroy_image(g_mlx_ptr, img->ptr);
	set_error_and_exit(NULL);
}
