/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 16:50:59 by cfriot            #+#    #+#             */
/*   Updated: 2015/04/24 15:23:54 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"
#include <stdlib.h>

char	*ft_clear_line(char *line)
{
	int		i;

	i = 0;
	if (line)
	{
		while (line[i] && (line[i] == ' ' || line[i] == 9))
			i++;
		if (i == ft_strlen(line))
			return (NULL);
		else
			return (ft_strsub(line, i, ft_strlen(line) - i));
	}
	return (line);
}

void	ft_coffee(t_magic **magic)
{
	char	**tab;
	char	*line;

	tab = NULL;
	line = NULL;
	ft_putstr("$> ");
	get_next_line(0, &line);
	line = ft_clear_line(line);
	if (ft_strlen(line) != 0)
		tab = ft_strsplit(line, ' ');
	if (tab && ft_lentab(tab) > 0)
		(*magic) = ft_parseur(*magic, tab);
	if (tab && ft_lentab(tab) > 0 && ft_strcmp(tab[0], "exit") == 0)
		(*magic)->done = 0;
	if (tab && ft_lentab(tab) > 0)
		ft_cleartab(tab);
	tab = NULL;
	free(line);
}

int		main(void)
{
	t_magic	*magic;

	signal(SIGINT, ft_sighandler);
	magic = (t_magic*)malloc(sizeof(t_magic));
	if (magic)
	{
		magic->env = ft_get_env();
		magic->pwd = ft_get_pwd();
		magic->oldpwd = ft_get_oldpwd(magic->env);
		magic->path = ft_get_path(magic->env);
		magic->done = 1;
		magic = ft_set_shlvl(magic);
		while (magic->done == 1)
			ft_coffee(&magic);
		free(magic->env);
		free(magic->pwd);
		free(magic->oldpwd);
		free(magic->path);
		free(magic);
	}
	return (0);
}
