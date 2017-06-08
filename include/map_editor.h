/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_editor.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 10:27:19 by pribault          #+#    #+#             */
/*   Updated: 2017/05/29 15:31:08 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_EDITOR_H
# define MAP_EDITOR_H

# include "ft_printf.h"
# include <stdio.h>

# define MAGIC			0x42424242
# define PI				3.1415926535

typedef unsigned char	t_uchar;
typedef unsigned int	t_uint;

typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct			s_p
{
	double				x;
	double				y;
}						t_p;

typedef struct			s_entity
{
	t_uchar				id;
	t_p					pos;
	double				angle;
}						t_entity;

typedef struct			s_map
{
	t_uint				magic;
	char				*name;
	int					w;
	int					h;
	t_point				spawn;
	t_uchar				**map;
	t_list				*entities;
}						t_map;

typedef struct			s_instruct
{
	char				*name;
	char				(*fct)(t_map*, char**);
	t_uchar				args;
}						t_instruct;

char					ft_error(t_uint error);

char					map_create(t_map *map, char **instruct);
char					map_push(t_map *map, char **instruct);
char					map_rm(t_map *map, char **instruct);
char					map_dump(t_map *map, char **instruct);
char					map_load(t_map *map, char **instruct);
char					map_unload(t_map *map, char **instruct);
char					map_exit(t_map *map, char **instruct);
char					map_set_spawn(t_map *map, char **instruct);
char					map_set_block(t_map *map, char **instruct);
char					map_set_line(t_map *map, char **instruct);
char					map_add_entity(t_map *map, char **instruct);
char					map_remove_entity(t_map *map, char **instruct);
char					map_help(t_map *map, char **instruct);

#endif
