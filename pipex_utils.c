/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 02:45:09 by myakoven          #+#    #+#             */
/*   Updated: 2024/02/17 22:19:07 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *cmd, char **env, char *cmdpath)
{
	char	*path;
	char	**command;

	path = ft_findpath(cmd, env, cmdpath);
	if (!path)
		exit(1);
	command = ft_split(cmd, ' ');
	if (execve(path, command, env) == -1)
	{
		ft_putstr_fd("pipex: command path not found for ", 2);
		ft_putendl_fd(command[0], 2);
		ft_freetab(command, 0);
		exit(2);
	}
}

char	*ft_findpath(char *cmd, char **env, char *cmdpath)
{
	int		i;
	char	*paths;
	char	**splitpaths;
	char	*path;
	char	**splitcommand;

	paths = ft_findpathenv("PATH", env);
	if (!paths)
		return (cmd);
	splitpaths = ft_split(paths, ':');
	splitcommand = ft_split(cmd, ' ');
	i = 0;
	while (splitpaths[i])
	{
		path = ft_jointhree(cmdpath, splitpaths[i], "/", splitcommand[0]);
		if (access(path, F_OK | X_OK) == 0)
		{
			ft_freetab(splitpaths, 0);
			ft_freetab(splitcommand, 0);
			return (path);
		}
		ft_bzero(cmdpath, 100);
		// free(path);
		i++;
	}
	ft_freetab(splitpaths, 0);
	ft_freetab(splitcommand, 0);
	return (cmd);
}
char	*ft_findpathenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*tempsubstr;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		tempsubstr = ft_substr(env[i], 0, j);
		if (ft_strncmp(name, tempsubstr, 4) == 0)
		{
			free(tempsubstr);
			return (env[i] + j + 1);
		}
		free(tempsubstr);
		i++;
	}
	// free(tempsubstr);
	return (NULL);
}

char	*ft_jointhree(char *cmdpath, char const *s1, char const *s2,
		char const *s3)
{
	size_t	len_two;
	size_t	len_all;
	size_t	i;
	size_t	j;

	// char	*string;
	i = 0;
	j = 0;
	len_two = ft_strlen(s1) + ft_strlen(s2);
	len_all = len_two + ft_strlen(s3);
	if (len_all > 100)
	{
		pip_error(3);
		exit(1);
	}
	// string = malloc(sizeof(char) * len_all + 1);
	// if (!(string))
	// 	return (NULL);
	while (i < ft_strlen(s1))
	{
		cmdpath[i] = s1[i];
		i++;
	}
	while (i < len_two)
		cmdpath[i++] = s2[j++];
	j = 0;
	while (i < len_all)
		cmdpath[i++] = s3[j++];
	cmdpath[i] = 0;
	return (cmdpath);
}
