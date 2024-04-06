/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:33:07 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/04/05 09:18:17 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_msg(char *c, char *str)
{
	write(2, "pipex: ", 7);
	if (c)
		write(2, c, ft_strlen(c));
	if (str)
		write(2, str, ft_strlen(str));
}

void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	error_exit(char *error, t_pipex_args *t, int exitcode)
{
	if (error != 0)
		perror(error);
	if (t->input_file >= 0)
		close(t->input_file);
	if (t->output_file >= 0)
		close(t->output_file);
	if (t->here_fd >= 0)
		close(t->here_fd);
	if (t->paths)
		ft_free(t->paths);
	if (t->pid)
		free(t->pid);
	if (t->pipes)
		free(t->pipes);
	if (t->cmd_path)
		free(t->cmd_path);
	if (t->args)
		free(t->args);
	if (access(".here_doc", F_OK) == 0)
		unlink(".here_doc");
	exit(exitcode);
}

void	error_exit_msg(char *c, char *str, t_pipex_args *t, int exitcode)
{
	error_msg(c, str);
	error_exit(0, t, exitcode);
}
