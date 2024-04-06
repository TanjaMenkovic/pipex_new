/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:09:54 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/04/05 17:39:32 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_args(int argc)
{
	if (argc != 5)
	{
		error_msg("incorrect number of arguments!", 0);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pipex_args	t;

	check_args(argc);
	init_variables(&t, env, argv, argc);
	malloc_pipes_pid(&t);
	create_pipes(&t);
	t.cmd_iter = 0;
	while (t.cmd_iter < t.num_of_cmd)
	{
		execute_cmd(argv, env, &t, argc);
		t.cmd_iter++;
	}
	close_everything(&t);
	t.cmd_iter = 0;
	while (t.cmd_iter < t.num_of_cmd)
	{
		waitpid(t.pid[t.cmd_iter], &t.status, 0);
		t.cmd_iter++;
	}
	if (access(".here_doc", F_OK) == 0)
		unlink(".here_doc");
	free(t.pid);
	return (WEXITSTATUS(t.status));
}
