/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 00:30:20 by miphigen          #+#    #+#             */
/*   Updated: 2020/10/26 19:33:53 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include "libft.h"
# include "my_mlx.h"
# include <math.h>
# include "stdint.h"
# include "save_bmp.h"
# define MLX_SYNC_IMAGE_WRITABLE    1 
# define MLX_SYNC_WIN_FLUSH_CMD     2
# define MLX_SYNC_WIN_CMD_COMPLETED 3

# define ANGLE_OV M_PI / 3
# define STEP 10 
# define ROTATION_SPEED M_PI / 90 
# define PPR 1 //не менять

typedef struct	s_sprite
{
	double		dist;
	char		type;
	double		x;
	double		y;

	double		height;
	double		actual_height;
	t_img		*texture_ptr;
	char		number;

	// center of the sprite
	double		xs;
	double		ys;

	// distance from the left side of the sprite
	double		d;
}				t_sprite;

typedef struct	s_wall
{
	double		dist;
	char		type;
	double		x;
	double		y;

	double		height;
	double		actual_height;
	t_img		*texture_ptr;
	char		number;
	t_sprite	*next;
}				t_wall;

typedef struct	s_item
{
	int			x;
	int			y;
	double		angle;
	double		dist;
}				t_item;

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

	t_img		*NO;
	t_img		*WE;
	t_img		*SO;
	t_img		*EA;
	t_img		*S;
	t_img		*texture_ptr;


	t_item		*items;
	int			items_count;
}				t_map;

t_map			*g_map;

void	 		parse_map(int fd);
void			parse_maze(int fd, char *str);
void			maze_is_valid();
void			render_map();
void			draw_2d_image();
void			draw_3d_image();
double			get_ray_length(double x, double y, double angle);
void			save_in_bmp(t_img *img);
int				set_error_and_exit(char *msg);
void			free_2d_array(char **s, int size);
void			swap_double(double *a, double *b);
void			mh_correct_values(double angle, double *x, double *y);
void			print_info();//
void			print_2d(char *s, char **array);//
//void			add_item(double x, double y, double anrle, int flag);
//void			put_items_to_image();
void			apply_texture(int x0, int x1, t_wall *wall);
void			dl_textures();
void			*ft_malloc(size_t size);
void	free_2d_array(char **s, int size);
void	*ft_malloc(size_t size);
void	get_wall_inf_and_collect_sprite_loc(double angle, t_wall *wall);
char	**add_spaces(char **array, int width, int *height);
int		is_valid_hor(char **array);
void	parse_line(char *line, int fd);
int	process_key(int key);
void	get_items_coord(char **maze);
	void		put_items(void);
void	print(t_item *tab, char *str);

// deprecated
typedef struct	s_line
{
	double		x0;
	double		y0;
	double		x1;
	double		y1;
	int			steep;
}				t_line;

#endif
