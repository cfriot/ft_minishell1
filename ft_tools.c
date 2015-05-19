/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 22:31:56 by cfriot            #+#    #+#             */
/*   Updated: 2015/04/24 15:58:12 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void	ft_displaytab(char **tab)
{
	int		i;

	i = -1;
	if (tab)
	{
		while (tab[++i])
		{
			ft_putendl(tab[i]);
		}
	}
}

char	*ft_get_path(char **env)
{
	int		line;
	char	*path;

	path = NULL;
	line = ft_wline(env, "PATH");
	if (line >= 0)
		path = ft_strsub(env[line], 5, ft_strlen(env[line]) - 5);
	return (path);
}
