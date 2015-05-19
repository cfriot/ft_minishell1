/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 20:46:39 by cfriot            #+#    #+#             */
/*   Updated: 2015/01/28 01:42:05 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

t_magic	*ft_set_oldpwd(t_magic *magic)
{
	int		oldpwd;

	oldpwd = ft_wline(magic->env, "OLDPWD");
	if (oldpwd >= 0)
	{
		free(magic->env[oldpwd]);
		magic->env[oldpwd] = ft_strjoin("OLDPWD=", magic->pwd);
	}
	free(magic->oldpwd);
	magic->oldpwd = ft_strdup(magic->pwd);
	return (magic);
}
