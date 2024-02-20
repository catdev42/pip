/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 02:45:09 by myakoven          #+#    #+#             */
/*   Updated: 2024/02/17 06:10:44 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_info	basics;
	char	cmdpath[101];
	int		i;
	int		pid;
	int		pfd[argc - 4][2];

	ft_init_basics(argc, argv, env, &basics);
	if (argc < 5)
		return (pip_error(1));
	i = 2;
	dup2(basics.fd_in, 0);
	while (i < argc - 2)
	{
		exec_pipe(pfd[i - 2], argv[i], env, cmdpath);
		i++;
	}
	dup2(basics.fd_out, 1);
	pid = fork();
	if (pid == 0)
		execute(argv[argc - 2], env, cmdpath);
	return (0);
}
void	exec_pipe(int *p_fd, char *cmd, char **env, char *cmdpath)
{
	int	pid;

	if (pipe(p_fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		execute(cmd, env, cmdpath);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
	}
}
// void	exec_pipe(int *p_fd, char *cmd, char **env, char *cmdpath)
// {
// 	pid_t	pid;

// 	// int		p_fd[2];
// 	if (pipe(p_fd) == -1)
// 		exit(0);
// 	pid = fork();
// 	if (pid == -1)
// 		exit(0);
// 	if (!pid)
// 	{
// 		// child process assigns the write end to out
// 		close(p_fd[0]);
// 		dup2(p_fd[1], 1);
// 		execute(cmd, env, cmdpath);
// 	}
// 	else
// 	{
// 		/*
// 		parent process asssigns the read end to std_in and doesn't evaporate next function will automatically read from std in which is now the read end of the pipe
// 		*/
// 		close(p_fd[1]);
// 		dup2(p_fd[0], 0);
// 	}
// }

void	ft_init_basics(int argc, char **argv, char **env, t_info *basics)
{
	basics->fd_in = open(argv[1], O_RDONLY);
	basics->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (basics->fd_in < 0 || basics->fd_out < 0)
		pip_error(2);
	basics->argc = argc;
	basics->argv = argv;
	basics->env = env;
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
// int		fdfiles[2];

// int		fdfiles[2];

// fdfiles[0] = open(argv[1], O_RDONLY);
// fdfiles[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
// if (fdfiles[0] < 0 || fdfiles[1] < 0)
// 	return (pip_error(2));

/*
	pid1 = fork();
	if (pid1 == -1)
		return (4);
	if (pid1 == 0)
		child_process(argv, p_fd, env, fd_in, cmdpath);
	dup2(fd_out, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	close(p_fd[0]);
	execute(argv[3], env, cmdpath);
*/

//

// while (i < (basics->argc) - 3)
// {
// 	if (pfd[i][0] != fd_read)
// 		close(pfd[i][0]);
// 	if (pfd[i][1] != fd_write)
// 		close(pfd[i][1]);
// }
