/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 19:16:20 by cfriot            #+#    #+#             */
/*   Updated: 2015/04/28 15:01:11 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

t_magic	*ft_go_home(t_magic *magic)
{
	char	*home;
	int		pwd;
	int		access;

	pwd = ft_wline(magic->env, "PWD");
	home = ft_get_home(magic->env);
	if ((access = ft_check_access_cd(home, "")) == 0)
	{
		if (chdir(home) == 0)
		{
			magic = ft_set_oldpwd(magic);
			if (pwd >= 0)
			{
				free(magic->env[pwd]);
				magic->env[pwd] = ft_strjoin("PWD=", getcwd(NULL, 0));
			}
		}
		free(magic->pwd);
		magic->pwd = ft_get_pwd();
	}
	else if (ft_strlen(home) > 0)
		ft_parse_error_cd(access, home);
	return (magic);
}

t_magic	*ft_cd_return(t_magic *magic)
{
	char	*oldpwd;
	int		pwd;

	pwd = ft_wline(magic->env, "PWD");
	oldpwd = magic->oldpwd;
	if (oldpwd)
	{
		if ((ft_check_access_cd(oldpwd, "")) == 0)
		{
			if (chdir(oldpwd) == 0)
			{
				magic = ft_set_oldpwd(magic);
				if (pwd >= 0)
				{
					free(magic->env[pwd]);
					magic->env[pwd] = ft_strjoin("PWD=", getcwd(NULL, 0));
				}
			}
			free(magic->pwd);
			magic->pwd = ft_get_pwd();
		}
		else
			ft_parse_error_cd(ft_check_access_cd(oldpwd, ""), oldpwd);
	}
	return (magic);
}

t_magic	*ft_do_cd_path(t_magic *magic, char **info)
{
	int		pwd;
	char	*path;
	int		access;

	pwd = ft_wline(magic->env, "PWD");
	path = ft_strjoin(getcwd(NULL, 0), "/");
	if ((access = ft_check_access_cd(path, info[1])) == 0)
	{
		if (chdir(info[1]) == 0)
		{
			magic = ft_set_oldpwd(magic);
			if (pwd >= 0)
			{
				free(magic->env[pwd]);
				magic->env[pwd] = ft_strjoin("PWD=", getcwd(NULL, 0));
			}
		}
		free(magic->pwd);
		magic->pwd = ft_get_pwd();
	}
	else
		ft_parse_error_cd(access, info[1]);
	return (magic);
}

t_magic	*ft_go_from_home(t_magic *magic, char **info)
{
	int		pwd;
	char	*path;
	int		access;

	pwd = ft_wline(magic->env, "PWD");
	path = ft_get_home(magic->env);
	if ((access = ft_check_access_cd(path, &info[1][1])) == 0)
	{
		if (chdir(ft_strjoin(path, &info[1][1])) == 0)
		{
			magic = ft_set_oldpwd(magic);
			if (pwd >= 0)
			{
				free(magic->env[pwd]);
				magic->env[pwd] = ft_strjoin("PWD=", getcwd(NULL, 0));
			}
		}
		free(magic->pwd);
		magic->pwd = ft_get_pwd();
	}
	else
		ft_parse_error_cd(access, info[1]);
	return (magic);
}

t_magic	*do_cd(t_magic *magic, char **info)
{
	if (ft_lentab(info) == 1 || ft_strcmp(info[1], "~") == 0)
		magic = ft_go_home(magic);
	else if (ft_lentab(info) == 2)
	{
		if (ft_strcmp(info[1], "-") == 0)
			magic = ft_cd_return(magic);
		else if (info[1][0] != '~')
			magic = ft_do_cd_path(magic, info);
		else
			magic = ft_go_from_home(magic, info);
	}
	else if (ft_lentab(info) == 3)
		magic = ft_double_cd(magic, info);
	else
		ft_putendl("command unknow");
	return (magic);
}
