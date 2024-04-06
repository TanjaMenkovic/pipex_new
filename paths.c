/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:24:42 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/04/05 17:35:33 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **env)
{
	if (!env)
		return (NULL);
	while (*env && ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	if (*env == NULL)
		return (NULL);
	return (*env + 5);
}

static	int	is_file(char *command)
{
	if (!command)
		return (0);
	if (ft_strchr(command, '/') != NULL)
		return (1);
	return (0);
}

static char	*cmd_file_errors(char *cmd, t_pipex_args *t, char **paths)
{
	if (!paths && access(cmd, F_OK) != 0)
		error_exit_msg(cmd, ": No such file or directory\n", t, 127);
	if (access(cmd, F_OK) != 0)
	{
		if (is_file(cmd))
			error_exit_msg(cmd, ": No such file or directory\n", t, 127);
		else
			error_exit_msg(cmd, ": command not found\n", t, 127);
	}
	if (is_file(cmd))
	{
		if (access(cmd, X_OK) != 0)
			error_exit_msg(cmd, ": Permission denied\n", t, 126);
		else
			return (cmd);
	}
	error_exit_msg(cmd, ": command not found\n", t, 127);
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **paths, t_pipex_args *t)
{
	char	*temp;
	char	*cmd_path;

	while (paths != NULL && *paths)
	{
		temp = ft_strjoin(*paths, "/");
		cmd_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!cmd_path)
			error_exit_msg(cmd, ": command not found\n", t, 127);
		if (access(cmd_path, F_OK) == 0)
		{
			if (access(cmd_path, X_OK) == 0)
				return (cmd_path);
			error_exit_msg(cmd, ": permission denied\n", t, 126);
		}
		free(cmd_path);
		paths++;
	}
	if (cmd_file_errors(cmd, t, paths) != NULL)
		return (cmd);
	error_exit_msg(t->args[0], ": No such file or directory\n", t, 127);
	return (NULL);
}
