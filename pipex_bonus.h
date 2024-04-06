/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:29:01 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/04/04 14:29:39 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_pipex_args
{
	int			input_file;
	int			output_file;
	int			num_of_cmd;
	int			cmd_iter;
	char		*cmd_path;
	char		*path_adresses;
	char		**paths;
	char		**args;
	int			*pipes;
	int			num_of_pipes;
	int			status;
	pid_t		wpid;
	pid_t		*pid;
	int			here_doc;
	int			here_fd;
}	t_pipex_args;

/* pipex_error.c */
void	error_msg(char *c, char *str);
void	ft_free(char **s);
void	error_exit(char *error, t_pipex_args *t, int exitcode);
void	error_exit_msg(char *c, char *str, t_pipex_args *t, int exitcode);

/* split_utils.c */
int		ft_numofstr(char *s);
char	*ft_word(const char *str, int start, int finish);
int		ft_checkmem(char **str, size_t num);

/* ft_split_new.c */
char	**ft_split_new(char *s);

/* init.c */
void	init_variables(t_pipex_args *t, char **env, char **argv, int argc);

/* pipes.c */
void	malloc_pipes_pid(t_pipex_args *t);
void	create_pipes(t_pipex_args *t);
void	close_pipes(t_pipex_args *t);
void	close_everything(t_pipex_args *t);

/* files.c */
void	open_input_file(char **argv, t_pipex_args *t);
void	open_output_file(char **argv, int argc, t_pipex_args *t);
void	get_here_doc(char *argv, t_pipex_args *t);

/* paths.c */
char	*get_path(char **env);
char	*get_cmd_path(char *cmd, char **paths, t_pipex_args *t);

/* exec.c */
void	dup2_checking(int *in, int *out, t_pipex_args *t);
void	execute_cmd(char **argv, char **env, t_pipex_args *t, int argc);

#endif
