/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:31:51 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/04/05 17:37:10 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_variables(t_pipex_args *t, char **env, char **argv, int argc)
{
	t->input_file = -2;
	t->output_file = -2;
	t->here_fd = -2;
	t->pipes = NULL;
	t->pid = NULL;
	t->args = NULL;
	t->cmd_path = NULL;
	if (!ft_strncmp(argv[1], "here_doc", 9))
		t->here_doc = 1;
	else
		t->here_doc = 0;
	t->path_adresses = get_path(env);
	if (t->path_adresses != NULL)
	{
		t->paths = ft_split(t->path_adresses, ':');
		if (!t->paths)
			error_exit("ft_split malloc failed\n", t, 1);
	}
	else
		t->paths = NULL;
	t->num_of_cmd = argc - 3 - t->here_doc;
	t->num_of_pipes = (t->num_of_cmd - 1) * 2;
}
