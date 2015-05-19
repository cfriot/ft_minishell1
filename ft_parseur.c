/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parseur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 00:59:35 by cfriot            #+#    #+#             */
/*   Updated: 2015/05/08 16:20:52 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

t_magic	*ft_parseur(t_magic *magic, char **info)
{
	if (!info)
		return (magic);
	else if (ft_strcmp("cd", info[0]) == 0)
		magic = do_cd(magic, info);
	else if (ft_strcmp("env", info[0]) == 0)
		magic = ft_check_command_env(magic, info);
	else if (ft_strcmp("setenv", info[0]) == 0)
		magic = ft_x_param_setenv(magic, info);
	else if (ft_strcmp("unsetenv", info[0]) == 0)
		magic->env = ft_x_param_unsetenv(magic->env, info);
	else if (info[0][0] == '.')
		ft_to_fork_path(magic->env, info);
	else if (ft_strcmp("exit", info[0]) != 0)
		ft_to_fork(magic, info);
	return (magic);
}

void	ft_to_fork(t_magic *magic, char **info)
{
	pid_t	father;

	father = fork();
	if (father > 0)
	{
		signal(SIGINT, ft_sighandler2);
		wait(NULL);
		signal(SIGINT, ft_sighandler);
	}
	else if (father == 0)
	{
		signal(SIGINT, SIG_DFL);
		magic->env = ft_test_exec(magic, info);
	}
	else
		ft_putendl_fd("Erreur fork", 2);
}

void	ft_to_fork_path(char **env, char **info)
{
	pid_t	father;
	int		access;
	char	*call;

	access = 0;
	call = ft_strsub(info[0], 1, ft_strlen(info[0]) - 1);
	father = fork();
	if (father > 0)
		ft_useless();
	else if (father == 0)
	{
		if ((access = ft_check_access_exe(getcwd(NULL, 0), call)) == 0)
		{
			signal(SIGINT, SIG_DFL);
			execve(info[0], info, env);
		}
		if (access == -1)
			ft_parse_error_exe(access, info[0]);
		else
			ft_parse_error_exe(0, info[0]);
		exit(0);
	}
	else
		ft_putendl_fd("Erreur fork", 2);
}
