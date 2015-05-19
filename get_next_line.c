/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 16:34:12 by cfriot            #+#    #+#             */
/*   Updated: 2015/01/22 22:07:38 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>

char	*ft_get_line(int const fd, char **line, int *end)
{
	char	*buffer;
	char	*tmp;
	int		i;

	tmp = NULL;
	while (*end > 0)
	{
		buffer = ft_strnew(BUFF_SIZE);
		*end = read(fd, buffer, BUFF_SIZE);
		i = 0;
		while (buffer[i] != '\n' && buffer[i] != EOF && i < ft_strlen(buffer))
			i++;
		(line) ? tmp = ft_strdup(*line) : ft_putstr("");
		(i > 0) ? *line = ft_strncat(ft_strcpy((ft_strnew(ft_strlen(tmp) + i)),
					tmp), buffer, i) : ft_putstr("");
		free(tmp);
		if (buffer[i] == '\n')
		{
			*end = 1;
			return (ft_strsub(buffer, i + 1, (size_t)(BUFF_SIZE - i - 1)));
		}
		free(buffer);
	}
	return (0);
}

char	*ft_get_rmn(int const fd, char **line, int *end, char *rmn)
{
	int		i;

	i = -1;
	*line = ft_strdup(rmn);
	while (rmn && rmn[i] != '\n' && rmn[i] != EOF && rmn[++i])
		;
	if (rmn[i] == '\n' || rmn[i] == EOF)
	{
		if (rmn[i] != EOF)
			rmn = ft_strsub(*line, i + 1, (size_t)(ft_strlen(*line) - i - 1));
		*line = ft_strsub(*line, 0, (size_t)(i));
		if (rmn[i] == EOF || (rmn[i + 1] && rmn[i + 1] == EOF))
			*end = 0;
	}
	else
		rmn = ft_get_line(fd, line, end);
	return (rmn);
}

t_lst	*ft_lstnew_line(int const fd, char **line, int *end)
{
	t_lst	*tmp;

	if (*end >= 0)
	{
		tmp = (t_lst *)malloc(sizeof(t_lst));
		if (tmp)
		{
			*line = NULL;
			tmp->key = fd;
			tmp->next = NULL;
			tmp->rmn = ft_get_line(fd, line, end);
		}
		else
			*end = -1;
		return (tmp);
	}
	return (0);
}

void	ft_lstadd_line(t_lst *begin, int const fd, char **line, int *end)
{
	t_lst	*cursor;
	int		cpt;

	cpt = 0;
	*line = NULL;
	cursor = begin;
	while (cursor)
	{
		if (cursor->key == fd)
		{
			cpt = 1;
			if (cursor->rmn == NULL)
				cursor->rmn = ft_get_line(fd, line, end);
			else
				cursor->rmn = ft_get_rmn(fd, line, end, cursor->rmn);
			cursor = NULL;
		}
		else if (cursor->next)
			cursor = cursor->next;
		else if (cpt == 0)
		{
			cursor->next = ft_lstnew_line(fd, line, end);
			cursor->next ? cursor = cursor->next->next : ft_putstr("");
		}
	}
}

int		get_next_line(int const fd, char **line)
{
	static t_lst	*begin;
	t_lst			*cursor;
	t_lst			*previous;
	int				end;

	end = 1;
	(fd < 0 || line == NULL) ? (end = -1) : ft_putstr("");
	(!begin) ? begin = ft_lstnew_line(fd, line, &end) :
		ft_lstadd_line(begin, fd, line, &end);
	cursor = begin;
	previous = cursor;
	if (end == 0)
	{
		(cursor->key == fd) ? begin = cursor->next : ft_putstr("");
		while (cursor->key != fd)
		{
			previous = cursor;
			cursor = cursor->next;
		}
		previous->next = cursor->next;
		free(cursor->rmn);
		free(cursor);
	}
	return (end);
}
