/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 21:41:46 by cfriot            #+#    #+#             */
/*   Updated: 2015/04/24 16:07:47 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

char	**ft_dup_env(char **environ)
{
	int				i;
	char			**copy;

	i = ft_lentab(environ);
	copy = (char**)malloc(sizeof(char*) * i + 1);
	i = 0;
	while (environ[i])
	{
		copy[i] = ft_strdup(environ[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char	**ft_get_env(void)
{
	extern char		**environ;
	char			**env;

	env = ft_dup_env(environ);
	if (ft_strlen(environ[0]) == 0 || environ[1] == NULL)
	{
		env = (char**)malloc(sizeof(char*) * 5);
		env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
		env[1] = ft_strdup("HOME=");
		env[2] = ft_strdup("OLDPWD=");
		env[3] = ft_strdup("PATH=/bin");
		env[4] = 0;
	}
	return (env);
}

t_magic	*ft_set_shlvl(t_magic *magic)
{
	int				place;
	int				equal;
	char			*value;

	equal = -1;
	place = ft_wline(magic->env, "SHLVL");
	if (place >= 0)
	{
		while (magic->env[place][++equal] != '=')
			;
		equal++;
		value = ft_strsub(magic->env[place], equal,
				ft_strlen(magic->env[place]) - equal);
		value = ft_itoa(ft_atoi(value) + 1);
		free(magic->env[place]);
		magic->env[place] = ft_strjoin("SHLVL=", value);
		free(value);
	}
	return (magic);
}
