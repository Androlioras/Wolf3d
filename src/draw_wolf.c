/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wolf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 17:40:11 by pribault          #+#    #+#             */
/*   Updated: 2017/06/12 17:05:19 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_line(t_env *env, t_point n, t_p b, t_pixel *p)
{
	t_image	*texture;
	int		ym[2];
	int		x;
	int		y;

	ym[0] = p[0].y;
	ym[1] = p[1].y;
	texture = env->blocks[env->map.map[n.y][n.x]].texture;
	if (fabs(b.x - (int)b.x) != 0.5)
		x = texture->w * (b.x - (int)b.x) + texture->w / 2;
	else
		x = texture->w * (b.y - (int)b.y) + texture->w / 2;
	p[0].y = (p[0].y < 0) ? 0 : p[0].y;
	p[1].y = (p[1].y >= env->img->h) ? env->img->h - 1 : p[1].y;
	while (p[0].y < p[1].y)
	{
		y = texture->h * (p[0].y - ym[0]) / (ym[1] - ym[0]);
		p[0].c = texture->l[y * texture->w + x];
		if ((fabs(b.x - (int)b.x) == 0.5 && b.x > n.x) ||
		(fabs(b.y - (int)b.y) == 0.5 && b.y > n.y))
			p[0].c = smlx_create_color(p[0].c.r / SHADOWS, p[0].c.g / SHADOWS,
			p[0].c.b / SHADOWS, p[0].c.a);
		smlx_pixel_put(env->img, p[0]);
		p[0].y++;
	}
}

void	draw_wall(t_env *env, t_p b, int i, double angle)
{
	t_pixel	p[2];
	t_point	n;
	double	d;

	if (fabs(b.x - (int)b.x) != 0.5)
		n.x = convert(b.x);
	else
		n.x = (cos(angle) > 0) ? (int)(b.x + 0.5) : (int)(b.x - 0.5);
	if (fabs(b.y - (int)b.y) != 0.5)
		n.y = convert(b.y);
	else
		n.y = (sin(angle) > 0) ? (int)(b.y + 0.5) : (int)(b.y - 0.5);
	if (n.x < 0 || n.y < 0 || n.x >= env->map.w || n.y >= env->map.h)
		return ;
	p[0] = smlx_create_pixel(i, 0, env->blocks[env->map.map[n.y][n.x]].color);
	p[1] = p[0];
	d = sqrt(pow(b.x - env->cam.x, 2) + pow(b.y - env->cam.y, 2)) * cos(angle -
	env->cam.angle);
	p[0].y = env->win.h / 2 - (env->blocks[env->map.map[n.y][n.x]].h / d);
	p[1].y = env->win.h / 2 + (env->blocks[env->map.map[n.y][n.x]].h / d);
	if (env->blocks[env->map.map[n.y][n.x]].texture)
		draw_line(env, n, b, p);
	else
		smlx_draw_line(env->img, p[0], p[1]);
}

t_p		find_vertical(t_env *env, double angle)
{
	t_point	t;
	t_p		p;
	double	max;

	p.x = (cos(angle) > 0) ? convert(env->cam.x) + 0.5 :
	convert(env->cam.x) - 0.5;
	max = (cos(angle) < 0) ? p.x - env->field : p.x + env->field;
	while (p.x != max)
	{
		p.y = env->cam.y + (p.x - env->cam.x) * tan(angle);
		t.y = convert(p.y);
		t.x = (cos(angle) > 0) ? (int)(p.x + 0.5) : (int)(p.x - 0.5);
		if (t.x < env->map.w && t.y < env->map.h && t.x >= 0 && t.y >= 0 &&
		env->map.map[t.y][t.x])
			if (p.y >= -0.5 && p.x >= -0.5 && p.y < env->map.h + 0.5 && p.x <
			env->map.w + 0.5)
				return (p);
		p.x += (p.x < max) ? 1 : -1;
	}
	p.x = -1;
	return (p);
}

t_p		find_horizontal(t_env *env, double angle)
{
	t_point	t;
	t_p		p;
	double	max;

	p.y = (sin(angle) > 0) ? convert(env->cam.y) + 0.5 :
	convert(env->cam.y) - 0.5;
	max = (sin(angle) < 0) ? p.y - env->field : p.y + env->field;
	while (p.y != max)
	{
		p.x = env->cam.x + (p.y - env->cam.y) / tan(angle);
		t.x = convert(p.x);
		t.y = (sin(angle) > 0) ? (int)(p.y + 0.5) : (int)(p.y - 0.5);
		if (t.y < env->map.h && t.x < env->map.w && t.y >= 0 && t.x >= 0 &&
		env->map.map[t.y][t.x])
			if (p.y >= -0.5 && p.x >= -0.5 && p.y < env->map.h + 0.5 && p.x <
			env->map.w + 0.5)
				return (p);
		p.y += (p.y < max) ? 1 : -1;
	}
	p.x = -1;
	return (p);
}

void	draw_wolf(t_thread *t)
{
	double	angle;
	t_p		p[2];

	while (t->i <= t->max)
	{
		angle = t->env->cam.angle +
		t->env->fov * (2 * t->i - t->env->win.w + 1) / (t->env->win.w - 1);
		p[0] = find_vertical(t->env, angle);
		p[1] = find_horizontal(t->env, angle);
		if (p[0].x != -1 && pow(p[0].x - t->env->cam.x, 2) + pow(p[0].y -
		t->env->cam.y, 2) < pow(p[1].x - t->env->cam.x, 2) + pow(p[1].y -
		t->env->cam.y, 2))
		{
			draw_wall(t->env, p[0], t->i, angle);
			draw_objects(t, p[0], angle);
		}
		else if (p[1].x != -1)
		{
			draw_wall(t->env, p[1], t->i, angle);
			draw_objects(t, p[1], angle);
		}
		else
			draw_objects(t, p[1], angle);
		t->i++;
	}
}
