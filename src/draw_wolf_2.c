/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wolf_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 13:34:26 by pribault          #+#    #+#             */
/*   Updated: 2017/06/12 19:02:55 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		get_x(t_image *texture, t_entity *ent, t_p p, double angle)
{
	if (cos(angle) > 0)
	{
		if (p.y > ent->pos.y)
			return (sqrt(pow(p.x - ent->pos.x, 2) + pow(p.y - ent->pos.y, 2))
			* (texture->w - 2) + texture->w / 2);
		else
			return (sqrt(pow(p.x - ent->pos.x, 2) + pow(p.y - ent->pos.y, 2))
			* (-texture->w) + texture->w / 2);
	}
	if (p.y < ent->pos.y)
		return (sqrt(pow(p.x - ent->pos.x, 2) + pow(p.y - ent->pos.y, 2))
		* (texture->w - 2) + texture->w / 2);
	else
		return (sqrt(pow(p.x - ent->pos.x, 2) + pow(p.y - ent->pos.y, 2))
		* (-texture->w) + texture->w / 2);
}

void	draw_line_2(t_thread *t, t_entity *ent, t_p p, double angle)
{
	t_image	*texture;
	double	d;
	int		m[2];
	int		x;
	t_pixel	u;

	d = sqrt(pow(p.x - t->env->cam.x, 2) + pow(p.y - t->env->cam.y, 2)) *
	cos(t->env->cam.angle - angle);
	m[0] = (d != 0) ? t->env->img2->h / 2 - t->env->entities[ent->id].h / d -
	t->env->entities[ent->id].y / d : 0;
	m[1] = (d != 0) ? t->env->img2->h / 2 + t->env->entities[ent->id].h / d -
	t->env->entities[ent->id].y / d : 0;
	if (!(texture = t->env->entities[ent->id].texture))
		return ;
	x = get_x(texture, ent, p, t->env->cam.angle);
	u.x = t->i;
	u.y = (m[0] >= 0) ? m[0] : 0;
	while (u.y < m[1] && u.y < t->env->img2->h)
	{
		u.c = texture->l[(int)(texture->h * ((double)(u.y - m[0]) / (m[1] -
		m[0]))) * texture->w + x];
		if (!u.c.a)
			smlx_pixel_put(t->env->img2, u);
		u.y++;
	}
}

t_p		must_draw(t_env *env, t_p max, t_entity *ent, double angle)
{
	double		l;
	t_p			p;

	l = sqrt(pow(ent->pos.x - env->cam.x, 2) + pow(ent->pos.y - env->cam.y, 2));
	p.x = l * cos(angle) + env->cam.x;
	p.y = l * sin(angle) + env->cam.y;
	if (sqrt(pow(p.x - ent->pos.x, 2) + pow(p.y - ent->pos.y, 2)) > 0.5)
		p.x = -1;
	else if ((cos(angle) > 0) ? (p.x > max.x || p.x < env->cam.x) :
	(p.x < max.x || p.x > env->cam.x))
		p.x = -1;
	else if ((sin(angle) > 0) ? (p.y > max.y || p.y < env->cam.y) :
	(p.y < max.y || p.y > env->cam.y))
		p.x = -1;
	return (p);
}

void	draw_objects(t_thread *t, t_p max, double angle)
{
	t_entity	*entity;
	t_list		*list;
	t_p			min;
	t_p			p;

	list = t->env->map.entities;
	if (max.x == -1)
		max.x += (cos(angle) > 0) ? t->env->field : -t->env->field;
	if (max.y == -1)
		max.y += ((angle) > 0) ? t->env->field : -t->env->field;
	min.x = 0;
	min.y = 0;
	while (list)
	{
		entity = (t_entity*)list->content;
		p = must_draw(t->env, max, entity, angle);
		if (p.x != -1 && ((!min.x && !min.y) || sqrt(pow(t->env->cam.x - p.x, 2)
		+ pow(t->env->cam.y - p.y, 2)) < sqrt(pow(t->env->cam.x - min.x, 2) +
		pow(t->env->cam.y - min.y, 2))))
		{
			draw_line_2(t, entity, p, angle);
			min = p;
		}
		list = list->next;
	}
}
