/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:28:21 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/04/04 16:17:19 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	check_args(int argc, char **argv)
{
	if (argc < 5 || (argc < 6 && ft_strncmp(argv[1], "here_doc", 9) == 0))
	{
		error_msg("Incorrect number of arguments!\n", 0);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pipex_args	t;

	check_args(argc, argv);
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
