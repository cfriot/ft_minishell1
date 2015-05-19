/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 02:37:23 by cfriot            #+#    #+#             */
/*   Updated: 2015/04/24 15:55:40 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

t_magic	*ft_setenv(t_magic *magic, char *info)
{
	char	*key;

	if (ft_verif_info_set(info) == -1)
	{
		ft_putendl_fd(ft_strjoin("Error command usage : KEY=value  ->  ",
					info), 2);
		return (magic);
	}
	key = ft_get_key(info);
	if (key != NULL && ft_wline(magic->env, key) < 0)
		magic->env = ft_addstr_to_tab(magic->env, info);
	else if (key != NULL)
	{
		magic->env = ft_delstr_from_tab(magic->env, key);
		magic->env = ft_addstr_to_tab(magic->env, info);
	}
	if (key != NULL)
	{
		(ft_strcmp("PATH", key) == 0) ?
			magic->path = ft_strsub(info, 5, ft_strlen(info) - 5) :
			ft_putstr("");
	}
	key ? free(key) : ft_putstr("");
	return (magic);
}

char	**ft_unsetenv(char **env, char *info)
{
	char	*key;

	if ((key = ft_get_key(info)) == NULL)
		return (env);
	else if (ft_wline(env, key) >= 0)
		env = ft_delstr_from_tab(env, key);
	free(key);
	return (env);
}

char	**ft_addstr_to_tab(char **tab, char *str)
{
	char	**newtab;
	int		i;

	i = -1;
	newtab = (char**)malloc(sizeof(char*) * ft_lentab(tab) + 2);
	if (tab)
	{
		while (++i < ft_lentab(tab))
			newtab[i] = ft_strdup(tab[i]);
		newtab[0] = ft_strdup(tab[0]);
		newtab[i] = ft_strdup(str);
		newtab[i + 1] = NULL;
	}
	else
	{
		newtab[0] = ft_strdup(str);
		newtab[1] = NULL;
	}
	return (newtab);
}

char	**ft_delstr_from_tab(char **tab, char *key)
{
	char	**newtab;
	int		i;
	int		j;
	int		index;

	i = 0;
	j = 0;
	index = ft_wline(tab, key);
	newtab = (char**)malloc(sizeof(char*) * ft_lentab(tab));
	if (index >= 0)
	{
		while (i < ft_lentab(tab))
		{
			if (i == index)
				i++;
			newtab[j] = ft_strdup(tab[i]);
			i++;
			j++;
		}
		newtab[j] = NULL;
		ft_cleartab(tab);
	}
	return (newtab);
}

char	*ft_get_key(char *info)
{
	char	*key;
	int		i;

	i = -1;
	key = NULL;
	if (info && ft_strlen(info) >= 0)
	{
		if (info[0] == '=')
			return (NULL);
		while (info[++i] && info[i] != '=')
			;
		key = ft_strsub(info, 0, i);
	}
	else
		ft_putendl_fd(ft_strjoin("Error command usage : KEY=value  ->  ",
					info), 2);
	return (key);
}
