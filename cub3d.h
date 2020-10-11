/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 00:30:20 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/11 19:00:19 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include "libft.h"
# include "my_mlx.h"
# include <math.h>
# define MLX_SYNC_IMAGE_WRITABLE    1 
# define MLX_SYNC_WIN_FLUSH_CMD     2
# define MLX_SYNC_WIN_CMD_COMPLETED 3

# define ANGLE_OV M_PI / 3
# define STEP 5 
# define ROTATION_SPEED M_PI / 90 
# define PPR 1
typedef struct	s_wall_info
{
	double		dist;
	char		type;
}				t_wall;

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

	double		hero_x;
	double		hero_y;
	double		hero_direction;

	int			scale;
	int			section_width;
	t_img		img;
	t_img		*img2;
	double		*sp_location;
}				t_map;

void	 		parse_map(t_map *map, int fd);
void			parse_maze(t_map *map, int fd, char *str);
void			maze_is_valid(t_map *map);
void			render_map(t_map *map);
void			draw_2d_image(t_map *map);
void			draw_3d_image(t_map *map);
double			get_ray_length(t_map *map, double x, double y, double angle);
void			save_in_bmp(t_img *img);
int				set_error_and_exit(char *msg, t_map *map);
void			free_2d_array(char **s, int size);
void			swap_double(double *a, double *b);
void			mh_correct_values(double angle, double *x, double *y);
void			print_info(t_map *map);//
void			print_2d(char *s, char **array);//
void			add_sprite(t_map *map, double x_start, double dist, int	flag);
void			put_sprites_to_image(t_map *map);


#endif
