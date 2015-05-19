/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 18:30:29 by cfriot            #+#    #+#             */
/*   Updated: 2015/05/08 16:49:15 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"
#include <stdlib.h>

int		ft_lentab(char **tab)
{
	int		i;

	i = -1;
	if (tab)
	{
		while (tab[++i])
			;
	}
	else
		return (0);
	return (i);
}

void	ft_cleartab(char **tab)
{
	int		i;

	i = ft_lentab(tab);
	i--;
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

char	**ft_test_exec(t_magic *magic, char **info)
{
	char	*call;
	int		access;

	access = 0;
	call = ft_strjoin("/", info[0]);
	if (info[0][0] == '/')
	{
		if ((access = ft_check_access_exe(info[0], "")) == 0)
			execve(info[0], info, magic->env);
		else if (access == -1)
		{
			ft_parse_error_exe(access, call);
			exit(0);
		}
		else
		{
			ft_parse_error_exe(0, call);
			exit(0);
		}
	}
	else
		magic->env = ft_try_all_path(magic, info, call);
	return (magic->env);
}

char	**ft_try_all_path(t_magic *magic, char **info, char *call)
{
	char	**path;
	int		i;
	int		access;

	i = -1;
	access = 0;
	path = NULL;
	if (ft_wline(magic->env, "PATH") >= 0)
		path = ft_strsplit(ft_get_path(magic->env), ':');
	while (path && path[++i])
	{
		if (ft_check_access_exe(path[i], call) == 0)
			execve(ft_strjoin(path[i], call), info, magic->env);
		else if (ft_check_access_exe(path[i], call) == -1)
			access = -1;
	}
	ft_parse_error_exe(access, call);
	if (path)
		ft_cleartab(path);
	exit(0);
	return (magic->env);
}

int		ft_verif_info_set(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '=')
		return (-1);
	return (1);
}
