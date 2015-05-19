/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/21 18:15:19 by cfriot            #+#    #+#             */
/*   Updated: 2015/04/24 15:49:32 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

t_magic	*ft_check_command_env(t_magic *magic, char **info)
{
	t_magic		*nomagic;

	nomagic = malloc(sizeof(t_magic));
	if (ft_lentab(info) == 1)
		ft_displaytab(magic->env);
	else if (ft_lentab(info) == 2 && ft_strcmp(info[1], "-i") == 0)
		ft_putstr("");
	else if (ft_strcmp(info[1], "-i") == 0)
	{
		nomagic->done = 0;
		nomagic->env = ft_strsplit("PATH=/bin", '\n');
		nomagic->pwd = NULL;
		nomagic->oldpwd = NULL;
		nomagic = ft_parseur(nomagic, &info[2]);
	}
	else
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(info[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	free(nomagic);
	return (magic);
}
