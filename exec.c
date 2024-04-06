/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:31:17 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/04/05 15:43:12 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dup2_checking(int *in, int *out, t_pipex_args *t)
{
	if (dup2(*in, 0) == -1 || dup2(*out, 1) == -1)
	{
		close_pipes(t);
		error_exit("dup2 failed\n", t, 1);
	}
	close(*in);
	close(*out);
	*in = -2;
	*out = -2;
}

static void	fork_error(t_pipex_args *t, int child_iter)
{
	int	i;

	close_pipes(t);
	i = 0;
	while (i < child_iter)
	{
		waitpid(t->pid[i], NULL, 0);
		i++;
	}
	error_exit("Failed to fork\n", t, 1);
}

static void	split_args(t_pipex_args *t, char **argv)
{
	t->args = ft_split_new(argv[2 + t->here_doc + t->cmd_iter]);
	if (!t->args)
		error_exit("Failed to split arguments\n", t, 4);
}

void	execute_cmd(char **argv, char **env, t_pipex_args *t, int argc)
{
	t->pid[t->cmd_iter] = fork();
	if (t->pid[t->cmd_iter] < 0)
		fork_error(t, t->cmd_iter - 1);
	if (t->pid[t->cmd_iter] == 0)
	{
		if (t->cmd_iter == 0)
		{
			open_input_file(argv, t);
			dup2_checking(&t->input_file, &t->pipes[1], t);
		}
		else if (t->cmd_iter == t->num_of_cmd - 1)
		{
			open_output_file(argv, argc, t);
			dup2_checking(&t->pipes[2 * t->cmd_iter - 2],
				&t->output_file, t);
		}
		else
			dup2_checking(&t->pipes[2 * t->cmd_iter - 2],
				&t->pipes[2 * t->cmd_iter + 1], t);
		close_pipes(t);
		split_args(t, argv);
		t->cmd_path = get_cmd_path(t->args[0], t->paths, t);
		execve(t->cmd_path, t->args, env);
		error_exit_msg(t->args[0], 0, t, -1);
	}
}
