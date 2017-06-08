/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 14:30:25 by pribault          #+#    #+#             */
/*   Updated: 2017/05/29 15:42:20 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		red_cross(t_env *env)
{
	if (env->where & 0x20)
		destroy_menu(env);
	free_blocks(env);
	smlx_destroy_image(&env->win, &env->img);
	smlx_destroy_window(&env->win);
	exit(0);
	return (0);
}

void	wolf_keys2(t_env *env)
{
	if (env->win.keys.tab[0])
		move_player(env, cos(env->cam.angle - PI / 2) / 10,
		sin(env->cam.angle - PI / 2) / 10);
	if (env->win.keys.tab[2])
		move_player(env, cos(env->cam.angle + PI / 2) / 10,
		sin(env->cam.angle + PI / 2) / 10);
	if (env->win.keys.tab[15])
	{
		free_blocks(env);
		load_blocks(env);
		free_entities(env);
		load_entities(env);
		free_map(env);
		load_map(env, NULL);
		ft_printf("blocks and map reloaded !\n\n");
	}
}

void	wolf_keys(t_env *env)
{
	if (env->win.keys.tab[123])
		env->cam.angle -= 0.03;
	if (env->win.keys.tab[124])
		env->cam.angle += 0.03;
	if (env->win.keys.tab[13])
		move_player(env, cos(env->cam.angle) / 10, sin(env->cam.angle) / 10);
	if (env->win.keys.tab[1])
		move_player(env, -cos(env->cam.angle) / 10, -sin(env->cam.angle) / 10);
	wolf_keys2(env);
	env->cam.angle += (env->cam.angle < -PI) ? 2 * PI : 0;
	env->cam.angle += (env->cam.angle > PI) ? -2 * PI : 0;
}

void	menu_keys(t_env *env)
{
	if (env->win.keys.personnal[1])
	{
		env->where += (env->where & 1) ? -1 : 1;
		env->where -= (env->where & 2) ? 2 : 0;
		env->where += (env->where & 4) ? -4 : 4;
	}
}

void	ft_keys(t_env *env)
{
	if (env->win.keys.tab[53])
		ft_exit(env, 0);
	if (env->where & 2)
		menu_keys(env);
	else if (env->where & 1)
		wolf_keys(env);
	if (env->win.keys.tab[49])
	{
		if (!(env->where & 128) && !(env->where & 2))
			create_menu(env);
		else if (!(env->where & 128) && (env->where & 2))
			destroy_menu(env);
		env->where += (!(env->where & 128)) ? 128 : 0;
	}
	else
		env->where -= (env->where & 128) ? 128 : 0;
}
