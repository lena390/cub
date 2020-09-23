/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_c3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 16:18:03 by miphigen          #+#    #+#             */
/*   Updated: 2020/09/21 17:23:47 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		map_config_is_complete(t_map *map)
{
	if (map->res_width == -1 || map->res_height == -1)
		set_error_and_exit("Missing resolution configuration", map);
	else if (!map->path_NO)
		set_error_and_exit("Missing north walls texture address", map);
	else if (!map->path_SO)
		set_error_and_exit("Missing south walls texture address", map);
	else if (!map->path_WE)
		set_error_and_exit("Missing west walls texture address", map);
	else if (!map->path_EA)
		set_error_and_exit("Missing east walls texture address", map);
	else if (!map->path_S)
		set_error_and_exit("Missing sprite texture address", map);
	else if (map->floor == -1)
		set_error_and_exit("Missing floor color value", map);
	else if (map->ceil == -1)
		set_error_and_exit("Missing ceil color value", map);
	else
		return (1);
	return (0);
}

void	parse_resolution(t_map *map, char *line)
{
	if (map->res_height != -1)
	{
		set_error_and_exit("Repeated resolution configuration", map);
		return ;
	}
	map->res_width = ft_atoi(++line);
	line = ft_skip_characters(line, " \t");
	line = ft_skip_characters(line, "0123456789");
	map->res_height = ft_atoi(line);
	if (map->res_height <= 0 || map->res_width <= 0)
		set_error_and_exit("Invalid resolution value", map);
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
		set_error_and_exit("Invalid identifier name or repeated texture configuration", map);
		free(line);
	}
}

void	parse_rgb(t_map *map, char *line)
{
	char			*id;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

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
		set_error_and_exit("Invalid color value or repeated color configuration", map);
}

void	parse_line(t_map *map, char *line, int fd)
{
	char *ptr;

	map->status = 2;
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
		set_error_and_exit("Invalid character in map configuration", map);
}

void	parse_map(t_map *map, int fd)
{
	char		*line;
	int			ret_value;

	map->status = 1;
	while ((ret_value = get_next_line(fd, &line)) > 0 && map->msg == NULL)
	{
		parse_line(map, line, fd);
		free(line);
	}
	if (ret_value == -1)
		set_error_and_exit("Error occurred while reading or opening file", map);
}