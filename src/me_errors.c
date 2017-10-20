/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 10:27:02 by pribault          #+#    #+#             */
/*   Updated: 2017/06/12 11:51:06 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_editor.h"

char	ft_error(t_uint error)
{
	if (error == 1)
		ft_putendl_fd("just a basic error\n", 2);
	else if (error == 2)
		ft_putendl("action reseted");
	else if (error == 3)
		ft_putendl("you don't have create a map yet !");
	else if (error == 4)
		ft_putendl("please load a map before");
	else if (error == 666)
		ft_putendl_fd("just a fatal error x_x\n", 2);
	if (error == 666)
		exit(1);
	return (1);
}
