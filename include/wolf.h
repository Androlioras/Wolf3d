/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 12:49:52 by pribault          #+#    #+#             */
/*   Updated: 2017/06/12 18:20:40 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "libsmlx.h"
# include <math.h>
# include <pthread.h>
# include <stdio.h>

# define MAGIC			0x42424242
# define PLAYER_SPEED	0.05
# define CAM_SPEED		0.05
# define SHADOWS		1.3

typedef struct	s_map
{
	int			w;
	int			h;
	t_uchar		**map;
	t_list		*entities;
}				t_map;

typedef struct	s_p
{
	double		x;
	double		y;
}				t_p;

typedef struct	s_block
{
	char		*name;
	int			h;
	t_color		color;
	t_image		*texture;
}				t_block;

typedef struct	s_ent
{
	char		*name;
	int			h;
	int			y;
	t_color		color;
	t_image		*texture;
}				t_ent;

typedef struct	s_entity
{
	t_uchar		id;
	t_p			pos;
	double		angle;
}				t_entity;

typedef struct	s_env
{
	t_win		win;
	t_image		*img;
	t_image		*back;
	t_image		*sky;
	t_image		*img2;
	t_block		*blocks;
	t_ent		*entities;
	t_map		map;
	t_camera	cam;
	t_uchar		threads;
	double		fov;
	int			field;
}				t_env;

typedef struct	s_thread
{
	t_env		*env;
	int			i;
	int			max;
}				t_thread;

void			load_map(t_env *env, char *name);
void			free_map(t_env *env);
void			load_blocks(t_env *env);
void			free_blocks(t_env *env);
void			load_entities(t_env *env);
void			free_entities(t_env *env);

void			ft_keys(t_env *env);

int				ft_exit(t_env *env, int k);
int				red_cross(t_env *env);

void			create_menu(t_env *env);
void			destroy_menu(t_env *env);

void			move_player(t_env *env, double x, double y);

void			draw_background(t_env *env);
int				ft_draw(t_env *env);
void			draw_wolf(t_thread *t);
void			draw_objects(t_thread *t, t_p max, double angle);
int				convert(double n);

#endif
