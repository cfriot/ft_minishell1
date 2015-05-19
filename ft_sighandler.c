/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sighandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/15 00:52:24 by cfriot            #+#    #+#             */
/*   Updated: 2015/03/23 16:58:46 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void	ft_sighandler(int sig)
{
	(void)sig;
	ft_putendl("");
	ft_putstr("$> ");
}

void	ft_sighandler2(int sig)
{
	(void)sig;
	ft_putendl("");
}

void	ft_useless(void)
{
	signal(SIGINT, ft_sighandler2);
	wait(NULL);
	signal(SIGINT, ft_sighandler);
}
