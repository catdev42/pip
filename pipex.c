/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 02:45:09 by myakoven          #+#    #+#             */
/*   Updated: 2024/02/17 21:36:35 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int		p_fd[2];
	int		pid1;
	int		fd_in;
	int		fd_out;
	char	cmdpath[101];

	if (argc != 5)
		return (pip_error(1));
	fd_in = open(argv[1], O_RDONLY);
	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_in < 0 || fd_out < 0)
		return (pip_error(2)); // close fds
	if (pipe(p_fd) == -1)
		return (3); // close fds
	pid1 = fork();
	if (pid1 == -1)
		return (4);
	if (pid1 == 0)
		child_process(argv, p_fd, env, fd_in, cmdpath);
	wait(NULL);
	dup2(fd_out, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	close(p_fd[0]);
	execute(argv[3], env, cmdpath);
}

void	child_process(char **argv, int *p_fd, char **env, int fd_in,
		char *cmdpath)
{
	dup2(fd_in, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	close(p_fd[1]);
	execute(argv[2], env, cmdpath);
}

int	pip_error(int err)
{
	if (err == 1)
	{
		ft_printf("Correct implementation: ./a.out infile 'cmd1' 'cmd2' outfile");
		return (1);
	}
	if (err == 2)
	{
		ft_printf("Infile Open Error");
		return (2);
	}
	if (err == 3)
	{
		ft_printf("Path is over 100 characters long");
		return (3);
	}
	return (0);
}
