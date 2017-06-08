/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wolf_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 13:34:26 by pribault          #+#    #+#             */
/*   Updated: 2017/06/06 13:17:58 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	custom_pixel_put(t_image *img, t_pixel p)
{
	t_color	*a;
	float	alpha;

	if (p.x < 0 || p.x >= img->w || p.y < 0 || p.y >= img->h)
		return ;
	alpha = (float)p.c.a / 255;
	a = img->l + (p.y * img->w + p.x);
	a->r = (1 - alpha) * p.c.r + (alpha * a->r);
	a->g = (1 - alpha) * p.c.g + (alpha * a->g);
	a->b = (1 - alpha) * p.c.b + (alpha * a->b);
	a->a = (1 - alpha) * p.c.a + (alpha * a->a);
}

int		get_x(t_image *texture, t_entity *ent, t_p p, double angle)
{
	if (cos(angle) > 0)
	{
		if (p.y > ent->pos.y)
			return (sqrt(pow(p.x - ent->pos.x, 2) + pow(p.y - ent->pos.y, 2))
			* (texture->w - 2) + texture->w / 2);
		return (sqrt(pow(p.x - ent->pos.x, 2) + pow(p.y - ent->pos.y, 2))
		* (-texture->w) + texture->w / 2);
	}
	if (p.y < ent->pos.y)
		return (sqrt(pow(p.x - ent->pos.x, 2) + pow(p.y - ent->pos.y, 2))
		* (texture->w - 2) + texture->w / 2);
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
	cos(angle - t->env->cam.angle);
	m[0] = (d != 0) ? t->env->img->h / 2 - t->env->entities[ent->id].h / d : 0;
	m[1] = (d != 0) ? t->env->img->h / 2 + t->env->entities[ent->id].h / d : 0;
	if (!(texture = t->env->entities[ent->id].texture))
		return ;
	x = get_x(texture, ent, p, t->env->cam.angle);
	u.x = t->i;
	u.y = m[0];
	while (u.y < m[1])
	{
		u.c = texture->l[(int)(texture->h * ((double)(u.y - m[0]) / (m[1] -
		m[0]))) * texture->w + x];
		custom_pixel_put(t->env->img, u);
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
	t_p			p;

	list = t->env->map.entities;
	if (max.x == -1)
		max.x += (cos(angle) > 0) ? t->env->field : -t->env->field;
	if (max.y == -1)
		max.y += ((angle) > 0) ? t->env->field : -t->env->field;
	while (list)
	{
		entity = (t_entity*)list->content;
		p = must_draw(t->env, max, entity, angle);
		if (p.x != -1)
			draw_line_2(t, entity, p, angle);
		list = list->next;
	}
}
