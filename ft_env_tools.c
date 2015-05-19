/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 23:05:06 by cfriot            #+#    #+#             */
/*   Updated: 2015/04/21 18:31:54 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

int		ft_begin_with(char *key, char *from_env)
{
	int		i;

	i = 0;
	while (key[i] == from_env[i])
		i++;
	if (i == ft_strlen(key) && from_env[i] && from_env[i] == '=')
		return (1);
	else
		return (-1);
}

int		ft_wline(char **env, char *str)
{
	int		i;

	i = -1;
	if (env)
	{
		while (env[++i])
		{
			if (ft_begin_with(str, env[i]) == 1)
				return (i);
		}
	}
	return (-1);
}

char	*ft_get_pwd(void)
{
	char	*pwd;

	pwd = ft_strdup(getcwd(NULL, 0));
	return (pwd);
}

char	*ft_get_home(char **env)
{
	int		home_line;
	char	*home;

	home = NULL;
	home_line = ft_wline(env, "HOME");
	if (home_line >= 0)
		home = ft_strsub(env[home_line], 5, ft_strlen(env[home_line]) - 4);
	return (home);
}

char	*ft_get_oldpwd(char **env)
{
	int		line;
	char	*oldline;

	oldline = NULL;
	line = ft_wline(env, "OLDPWD");
	if (line >= 0)
		oldline = ft_strsub(env[line], 7, ft_strlen(env[line]) - 7);
	return (oldline);
}
