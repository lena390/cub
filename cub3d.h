/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 00:30:20 by miphigen          #+#    #+#             */
/*   Updated: 2020/09/23 00:15:18 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include "libft.h"
# include "my_mlx.h"
# include <math.h>
#define MLX_SYNC_IMAGE_WRITABLE    1 
#define MLX_SYNC_WIN_FLUSH_CMD     2
#define MLX_SYNC_WIN_CMD_COMPLETED 3
#define ANGLE_OV 60

typedef struct	s_map_info
{
	int			screenshot_needed;
	int			status;
	char		*msg;
	int			res_width;
	int			res_height;
	char		*path_NO;
	char		*path_SO;
	char		*path_WE;
	char		*path_EA;
	char		*path_S;
	int			ceil;
	int			floor;

	char		**maze;
	int			maze_width;
	int			maze_height;

	int			hero_x;
	int			hero_y;
	int			hero_direction;

	int			scale;
	t_img		img;
	t_img		*img2;
}				t_map;

void	 		parse_map(t_map *map, int fd);
void			parse_maze(t_map *map, int fd, char *str);
void			maze_is_valid(t_map *map);
void			render_map(t_map *map);
void			draw_map_2d(t_map *map);
void			draw_map_3d(t_map *map);
double			get_ray_length(t_map *map, int x, int y, double angle);
void			save_in_bmp(t_img *img);
int				set_error_and_exit(char *msg, t_map *map);
void			free_2d_array(char **s, int size);

void			print_info(t_map *map);//
void			print_2d(char *s, char **array);//

#endif
