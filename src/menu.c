/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 15:23:27 by pribault          #+#    #+#             */
/*   Updated: 2017/05/23 16:39:12 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	create_menu(t_env *env)
{
	t_point	b;
	t_point	a;

	env->where += (!(env->where & 2)) ? 2 : 0;
	a = smlx_create_point(env->img->w / 4, env->img->h / 4);
	b = smlx_create_point(3 * env->img->w / 4, 3 * env->img->h / 4);
	smlx_new_button(env->img, a, b, 1);
}

void	destroy_menu(t_env *env)
{
	t_list	*list;
	t_list	*next;

	list = env->win.buttons;
	while (list)
	{
		smlx_destroy_button((t_button**)&list->content);
		next = list->next;
		free(list);
		list = next;
	}
	env->win.buttons = NULL;
	env->where -= (env->where & 2) ? 2 : 0;
	env->where += (!(env->where & 1)) ? 1 : 0;
}
