/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:34:33 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/04/04 16:34:51 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	malloc_pipes_pid(t_pipex_args *t)
{
	t->pipes = (int *)malloc((t->num_of_pipes) * sizeof(int));
	if (!t->pipes)
		error_exit("Malloc for pipes failed\n", t, 1);
	t->pid = (int *)malloc((t->num_of_cmd) * sizeof(int));
	if (!t->pid)
		error_exit("Malloc for pid failed\n", t, 1);
}

void	create_pipes(t_pipex_args *t)
{
	int	i;
	int	j;

	i = 0;
	while (i < (t->num_of_cmd - 1))
	{
		if (pipe(t->pipes + 2 * i) < 0)
		{
			j = 0;
			while (j < i * 2)
				close(t->pipes[j++]);
			free(t->pipes);
			error_exit("Failed to create pipes\n", t, 1);
		}
		i++;
	}
}

void	close_pipes(t_pipex_args *t)
{
	int	i;

	i = 0;
	while (i < t->num_of_pipes)
		close(t->pipes[i++]);
}

void	close_everything(t_pipex_args *t)
{
	close_pipes(t);
	if (t->input_file >= 0)
		close(t->input_file);
	if (t->output_file >= 0)
		close(t->output_file);
	free(t->pipes);
	if (t->paths)
		ft_free(t->paths);
}
