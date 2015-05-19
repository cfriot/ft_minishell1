/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_cd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 03:39:55 by cfriot            #+#    #+#             */
/*   Updated: 2015/02/13 04:20:12 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

t_magic	*ft_update_magic(t_magic *magic, char *pwd)
{
	magic = ft_set_oldpwd(magic);
	if (ft_wline(magic->env, "PWD") >= 0)
	{
		free(magic->env[ft_wline(magic->env, "PWD")]);
		magic->env[ft_wline(magic->env, "PWD")] =
			ft_strjoin("PWD=", pwd);
	}
	ft_putendl(pwd);
	return (magic);
}

t_magic	*ft_double_cd(t_magic *magic, char **info)
{
	char	*begin;
	char	*new_pwd;
	char	*pwd;

	pwd = ft_get_pwd();
	if ((begin = ft_strstr(pwd, info[1])))
	{
		new_pwd = ft_strsub(pwd, 0, ft_strlen(pwd) - ft_strlen(begin));
		new_pwd = ft_strjoin(new_pwd, info[2]);
		new_pwd = ft_strjoin(new_pwd, ft_strsub(pwd, ft_strlen(pwd) -
					ft_strlen(begin) + ft_strlen(info[1]), ft_strlen(pwd)));
		if (ft_check_access_cd(new_pwd, "") == 0)
		{
			if (chdir(new_pwd) == 0)
				magic = ft_update_magic(magic, new_pwd);
			free(magic->pwd);
			magic->pwd = ft_get_pwd();
		}
		else
			ft_parse_error_cd(ft_check_access_cd(new_pwd, ""), info[2]);
	}
	else
		ft_putendl(ft_strjoin("cd: not in pwd: ", info[1]));
	return (magic);
}
