/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:03:07 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/04/04 16:40:18 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_input_file(char **argv, t_pipex_args *t)
{
	if (t->here_doc == 1)
		get_here_doc(argv[2], t);
	else
	{
		t->input_file = open(argv[1], O_RDONLY);
		if (t->input_file < 0)
		{
			error_msg(argv[1], ": No such file or directory\n");
			close_pipes(t);
			error_exit(0, t, 1);
		}
	}
}

void	open_output_file(char **argv, int argc, t_pipex_args *t)
{
	if (t->here_doc == 1)
		t->output_file = open(argv[argc - 1], O_APPEND
				| O_CREAT | O_RDWR, 0644);
	else
		t->output_file = open(argv[argc - 1], O_TRUNC
				| O_CREAT | O_RDWR, 0644);
	if (t->output_file < 0)
	{
		error_msg(argv[1], ": No such file or directory\n");
		close_pipes(t);
		error_exit(0, t, 1);
	}
}

void	get_here_doc(char *argv, t_pipex_args *t)
{
	char	*buf;

	t->here_fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (t->here_fd < 0)
		error_exit("Failed to create here_doc\n", t, 1);
	while (1)
	{
		write(1, "heredoc> ", 9);
		buf = get_next_line(0);
		if (!buf)
			break ;
		if (buf < 0)
			error_exit("get_next_line failed\n", t, 1);
		if (!ft_strncmp(buf, argv, ft_strlen(argv))
			&& buf[ft_strlen(argv)] == '\n')
			break ;
		write(t->here_fd, buf, ft_strlen(buf));
		free (buf);
	}
	if (buf)
		free (buf);
	close(t->here_fd);
	t->input_file = open(".here_doc", O_RDONLY);
	if (t->input_file < 0)
		error_exit("Failed to open here_doc\n", t, 1);
}
