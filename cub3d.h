/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 00:30:20 by miphigen          #+#    #+#             */
/*   Updated: 2020/08/27 19:36:06 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include "libft.h"
# include "my_mlx.h"

typedef struct	s_hero
{
	int			x;
	int			y;
	char		orient;
}				t_hero;

typedef struct	s_map_info
{
	int			status;
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
	t_hero		hero;
}				t_map;

void	 		parse_map(t_map *map, int fd);
void			parse_maze(t_map *map, int fd, char *str);
int				maze_is_valid(t_map *map);

void			render_map(t_map *map);

void			print_info(t_map *map);//
void			print_2d(char *s, char **array);//

#endif
