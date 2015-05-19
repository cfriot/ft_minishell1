/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_param_setenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 03:53:08 by cfriot            #+#    #+#             */
/*   Updated: 2015/01/28 05:05:12 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

t_magic		*ft_x_param_setenv(t_magic *magic, char **info)
{
	int		i;

	i = 0;
	while (info && info[++i])
		magic = ft_setenv(magic, info[i]);
	return (magic);
}

char		**ft_x_param_unsetenv(char **env, char **info)
{
	int		i;

	i = 0;
	while (info && info[++i])
		env = ft_unsetenv(env, info[i]);
	return (env);
}
