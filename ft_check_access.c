/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_access.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/27 22:55:32 by cfriot            #+#    #+#             */
/*   Updated: 2015/05/08 16:47:14 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"
#include <sys/stat.h>

int		ft_check_access_exe(char *path, char *info)
{
	struct stat		*buf;
	int				retstat;

	if ((buf = malloc(sizeof(struct stat))))
	{
		retstat = stat(ft_strjoin(path, info), buf);
		if (retstat == 0)
		{
			if (!(buf->st_mode & S_IXUSR))
				return (-1);
			else
				return (0);
		}
		return (-3);
	}
	return (-4);
}

int		ft_check_access_cd(char *path, char *info)
{
	struct stat		*buf;
	int				retstat;

	if ((buf = malloc(sizeof(struct stat))))
	{
		retstat = stat(ft_strjoin(path, info), buf);
		if (retstat == 0)
		{
			if (!S_ISDIR(buf->st_mode))
				return (-1);
			if (!(buf->st_mode & S_IRUSR))
				return (-2);
			return (0);
		}
		else
			return (-3);
	}
	return (-4);
}

char	*ft_check_call(char *call)
{
	if (call[0] == '.')
		return (ft_strsub(call, 2, ft_strlen(call) - 2));
	else if (call[0] == '/')
		return (ft_strsub(call, 1, ft_strlen(call) - 1));
	else
		return (call);
}

void	ft_parse_error_cd(int error, char *info)
{
	if (error == -1)
		ft_putendl_fd(ft_strjoin("cd: not a directory: ", info), 1);
	else if (error == -2)
		ft_putendl_fd(ft_strjoin("cd: permission denied: ", info), 1);
	else if (error == -3)
		ft_putendl_fd(ft_strjoin("cd: no such file or directory: ", info), 1);
}

void	ft_parse_error_exe(int error, char *info)
{
	char			*trivial;

	if (error == -1)
		ft_putendl_fd(ft_strjoin("exe: permission denied: ", info), 2);
	else if (error == 0)
	{
		if (info[0] == '/' && info[1] == '/')
		{
			trivial = ft_strsub(info, 1, ft_strlen(info) - 1);
			ft_putendl_fd(ft_strjoin(trivial, ": command not found"), 2);
			free(trivial);
		}
		else
			ft_putendl_fd(ft_strjoin(info, ": command not found"), 2);
	}
}
