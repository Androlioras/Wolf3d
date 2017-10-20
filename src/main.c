/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 12:41:13 by pribault          #+#    #+#             */
/*   Updated: 2017/06/12 18:58:28 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		ft_exit(t_env *env, int k)
{
	free_map(env);
	free_blocks(env);
	free_entities(env);
	smlx_destroy_image(&env->win, &env->img);
	smlx_destroy_image(&env->win, &env->img2);
	smlx_destroy_image(&env->win, &env->back);
	smlx_destroy_image(&env->win, &env->sky);
	smlx_destroy_window(&env->win);
	exit(k);
	return (0);
}

void	calculate_background(t_image *back)
{
	t_pixel	p;

	p.y = back->h / 2;
	p.c = smlx_create_color(191, 191, 191, 0);
	while (p.y < back->h)
	{
		p.x = 0;
		while (p.x < back->w)
		{
			smlx_pixel_put(back, p);
			p.x++;
		}
		p.y++;
	}
}

void	draw_background(t_env *env)
{
	t_pixel	p;
	t_point	b;

	p.x = 0;
	while (p.x < env->back->w)
	{
		p.y = 0;
		while (p.y < env->back->h / 2)
		{
			b.y = 2 * p.y * env->sky->h / env->back->h;
			b.x = p.x * env->sky->w / env->back->w;
			p.c = env->sky->l[b.y * env->sky->w + b.x];
			smlx_pixel_put(env->back, p);
			p.y++;
		}
		p.x++;
	}
	calculate_background(env->back);
}

void	init(t_env *env)
{
	env->img = smlx_new_image(&env->win, env->win.w, env->win.h);
	env->img2 = smlx_new_image(&env->win, env->win.w, env->win.h);
	env->back = smlx_new_image(&env->win, env->win.w, env->win.h);
	env->sky = smlx_new_image_xpm(&env->win, "textures/sky.xpm");
	env->cam.x = 2;
	env->cam.y = 2;
	env->cam.angle = 0;
	env->map.w = 8;
	env->map.h = 8;
	env->threads = 4;
	env->fov = PI / 6;
	env->field = 100;
	ft_putchar('\n');
}

int		main(int argc, char **argv)
{
	t_env	env;

	smlx_init(&env.win, 1200, 900, "Wolf3d");
	smlx_set_flags(&env.win, SMLX_C_SLOPE);
	init(&env);
	draw_background(&env);
	load_blocks(&env);
	load_entities(&env);
	if (argc <= 1)
		load_map(&env, "map");
	else
		load_map(&env, argv[1]);
	smlx_key_hook(&env.win);
	mlx_hook(env.win.win, 17, (1L << 17), &red_cross, &env);
	mlx_loop_hook(env.win.mlx, &ft_draw, &env);
	mlx_loop(env.win.mlx);
	return (0);
}
