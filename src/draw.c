/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 14:47:58 by pribault          #+#    #+#             */
/*   Updated: 2017/06/12 17:10:07 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <sys/time.h>

int		convert(double n)
{
	if (n - (int)n > 0.5)
		return ((int)n + 1);
	return ((int)n);
}

void	draw_menu(t_env *env)
{
	t_pixel	b[4];

	b[0] = smlx_create_pixel(env->win.w / 4, env->win.h / 4,
	smlx_create_color(128, 128, 128, 0));
	b[1] = smlx_create_pixel(3 * env->win.w / 4, env->win.h / 4, b[0].c);
	b[2] = smlx_create_pixel(3 * env->win.w / 4, 3 * env->win.h / 4, b[0].c);
	b[3] = smlx_create_pixel(env->win.w / 4, 3 * env->win.h / 4, b[0].c);
	smlx_draw_full_polygone(env->img, b, 4);
}

void	draw_editor(t_thread *t)
{
	t_pixel	a;
	t_point	p;

	a.x = t->i;
	while (a.x < t->max)
	{
		a.y = 0;
		p.x = a.x * t->env->map.w / t->env->img->w;
		while (a.y < t->env->img->h)
		{
			p.y = a.y * t->env->map.h / t->env->img->h;
			a.c = t->env->blocks[t->env->map.map[p.y][p.x]].color;
			smlx_pixel_put(t->env->img, a);
			a.y++;
		}
		a.x++;
	}
}

void	draw_multithread(t_env *env, void *(*function)(void*))
{
	pthread_t	thread[env->threads];
	t_thread	params[env->threads];
	int			i;

	i = 0;
	while (i < env->threads)
	{
		params[i].env = env;
		params[i].i = i * env->img->w / env->threads;
		params[i].max = (i + 1) * env->img->w / env->threads;
		pthread_create(&thread[i], NULL, function, &params[i]);
		i++;
	}
	i = 0;
	while (i < env->threads)
		pthread_join(thread[i++], NULL);
}

int		ft_draw(t_env *env)
{
	ft_keys(env);
	mlx_clear_window(env->win.mlx, env->win.win);
	smlx_clear_image(env->img);
	smlx_clear_image(env->img2);
	mlx_put_image_to_window(env->win.mlx, env->win.win, env->back->img, 0, 0);
	draw_multithread(env, (void*)&draw_wolf);
	mlx_put_image_to_window(env->win.mlx, env->win.win,
	env->img->img, 0, 0);
	mlx_put_image_to_window(env->win.mlx, env->win.win,
	env->img2->img, 0, 0);
	ft_printf("\033[1A\033[Kangle: %d degrés | x=%d y=%d | fps: %d\n",
	(int)(env->cam.angle * 180 / PI), (int)env->cam.x, (int)env->cam.y,
	smlx_get_fps());
	return (0);
}
