/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 16:18:03 by miphigen          #+#    #+#             */
/*   Updated: 2020/08/25 19:22:34 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		map_config_is_complete(t_map *map)
{
	if (map->res_width == -1 || map->res_height == -1)
		return (-10);
	else if (!map->path_NO)
		return (-11);
	else if (!map->path_SO)
		return (-12);
	else if (!map->path_S)
		return (-13);
	else if (map->floor == -1)
		return (-14);
	else if (!map->path_WE)
		return (-15);
	else if (!map->path_EA)
		return (-16);
	else if (map->ceil == -1)
		return (-17);
	return (1);
}

void	parse_resolution(t_map *map, char *line)
{
	int 	value;

	if (map->res_height != -1)
	{
		map->status = -2;//errno resolution config doubled
		return ;
	}
	map->res_width = ft_atoi(++line);
	line = ft_skip_characters(line, " \t");
	line = ft_skip_characters(line, "0123456789");
	map->res_height = ft_atoi(line);
	if (map->res_height <= 0 || map->res_width <= 0)
		map->status = -3;//errno invalid resolution
}

void	parse_texture_addr(t_map *map, char *line)
{
	char	*id;

	id = line;
	line = ft_strchr(line, ' ');
	line = ft_strtrim(line, " ");
	if (*id == 'N' && id[1] == 'O' && !map->path_NO)
		map->path_NO = line;
	else if (*id == 'S' && id[1] == 'O' && !map->path_SO)
		map->path_SO = line;
	else if (*id == 'W' && id[1] == 'E' && !map->path_WE)
		map->path_WE = line;
	else if (*id == 'E' && id[1] == 'A' && !map->path_EA)
		map->path_EA = line;
	else if (*id == 'S' && ft_is_in_set(" \t", *++id) == 1 && !map->path_S)
		map->path_S = line;
	else
	{
		map->status = -4;//errno invalid identifier name or repeated config
		free(line);
	}
}

void	parse_rgb(t_map *map, char *line)
{
	char			*id;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int i;

	id = line;
	r = ft_atoi(++line);
	line = ft_strchr(line, ',');
	g = ft_atoi(++line);
	line = ft_strchr(line, ',');
	b = ft_atoi(++line);
	if (*id == 'F' && ft_is_in_set(" \t", *(id + 1)) == 1 && map->floor == -1)
		map->floor = (r << 16 | g << 8 | b);
	else if (*id == 'C' && ft_is_in_set(" \t", *++id) == 1 && map->ceil == -1)
		map->ceil = (r << 16 | g << 8 | b);
	else
		map->status = -5;//errno rgb config invalid
}

void	parse_line(t_map *map, char *line, int fd)
{
	char *ptr;

	ptr = line;
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0')
		return ;
	if (*line == 'R')
		parse_resolution(map, line);
	else if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
		parse_texture_addr(map, line);
	else if (*line == 'F' || *line == 'C')
		parse_rgb(map, line);
	else if (*line == '1')
	{
		if ((map->status = map_config_is_complete(map)) == 1)
			parse_maze(map, fd, ft_strdup(ptr));
	}
	else
		map->status = -1; //invalid character
}

void	parse_map(t_map *map, int fd)
{
	char		*line;
	int			ret_value;

	while ((ret_value = get_next_line(fd, &line)) > 0 && map->status == 0)
	{
		parse_line(map, line, fd);
		free(line);
	}
	if (ret_value == -1)
		printf("invalid map addr\n");
}