/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 16:54:08 by cfriot            #+#    #+#             */
/*   Updated: 2015/04/24 15:11:11 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH1_H
# define FT_SH1_H
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include "libft.h"

typedef struct	s_magic
{
	int			done;
	char		**env;
	char		*pwd;
	char		*oldpwd;
	char		*path;
}				t_magic;
char			**ft_stock_env(char **env, int i);
t_magic			*ft_setenv(t_magic *magic, char *info);
char			**ft_unsetenv(char **env, char *info);
char			**ft_addstr_to_tab(char **tab, char *str);
char			**ft_delstr_from_tab(char **tab, char *key);
char			**ft_dup_env(char **environ);
char			**ft_get_env(void);
char			**ft_try_all_path(t_magic *magic, char **info, char *call);
char			**ft_test_exec(t_magic *magic, char **info);
char			*ft_get_key(char *env);
char			*ft_get_path(char **env);
char			*ft_get_oldpwd(char **env);
char			*ft_get_home(char **env);
char			*ft_get_pwd(void);
char			*ft_check_call(char *call);
char			**ft_x_param_unsetenv(char **env, char **info);
t_magic			*ft_check_command_env(t_magic *magic, char **info);
t_magic			*ft_go_home(t_magic *magic);
t_magic			*ft_update_magic(t_magic *magic, char *pwd);
t_magic			*ft_go_from_home(t_magic *magic, char **info);
t_magic			*ft_double_cd(t_magic *magic, char **info);
t_magic			*ft_x_param_setenv(t_magic *magic, char **info);
t_magic			*ft_set_oldpwd(t_magic *magic);
t_magic			*ft_cd_return(t_magic *magic);
t_magic			*ft_do_cd_path(t_magic *magic, char **info);
t_magic			*do_cd(t_magic *magic, char **info);
t_magic			*ft_set_shlvl(t_magic *magic);
t_magic			*ft_parseur(t_magic *magic, char **info);
int				ft_verif_info_set(char *str);
int				ft_begin_with(char *key, char *from_env);
int				ft_wline(char **env, char *str);
int				get_next_line(int fd, char **line);
int				ft_lentab(char **tab);
int				ft_check_access_exe(char *path, char *info);
int				ft_check_access_cd(char *path, char *info);
void			ft_parse_error_exe(int error, char *info);
void			ft_parse_error_cd(int error, char *info);
void			ft_displaytab(char **tab);
void			ft_cleartab(char **tab);
void			ft_coffee(t_magic **magic);
void			ft_to_fork(t_magic *magic, char **info);
void			ft_to_fork_path(char **env, char **info);
void			ft_sighandler(int sig);
void			ft_sighandler2(int sig);
void			ft_useless(void);
#endif
