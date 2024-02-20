/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 02:43:55 by myakoven          #+#    #+#             */
/*   Updated: 2024/02/17 00:30:12 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX
# define PIPEX

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

int		pip_error(int err);
char	*ft_findpath(char *cmd, char **env, char *cmdpath);
char	*ft_jointhree(char *cmdpath, char const *s1, char const *s2, char const *s3);
char	*ft_findpathenv(char *name, char **env);
void	child_process(char **argv, int *p_fd, char **env, int fd_in,\
			char *cmdpath);
void	execute(char *cmd, char **env, char *cmdpath);

#endif