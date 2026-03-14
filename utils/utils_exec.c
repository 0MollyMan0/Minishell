/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:07:26 by anfouger          #+#    #+#             */
/*   Updated: 2026/03/14 12:49:51 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	char	*tmp;
	int		i;

	if (!get_path(envp))
		return (NULL);
	paths = ft_split(get_path(envp), ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			free_tab(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_tab(paths);
	return (NULL);
}

int	is_slash_in(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo"))
		return (1);
	if (ft_strcmp(cmd, "cd"))
		return (1);
	if (ft_strcmp(cmd, "pwd"))
		return (1);
	if (ft_strcmp(cmd, "export"))
		return (1);
	if (ft_strcmp(cmd, "unset"))
		return (1);
	if (ft_strcmp(cmd, "env"))
		return (1);
	if (ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	exec_builtin(t_minish *minish)
{
	char	**argv;

	argv = minish->cmds->argv;
	if (ft_strcmp(argv[0], "echo"))
		return (builtin_echo(argv));
	if (ft_strcmp(argv[0], "pwd"))
		return (builtin_pwd());
	if (ft_strcmp(argv[0], "env"))
		return (builtin_env(minish->envp));
	if (ft_strcmp(argv[0], "cd"))
		return (builtin_cd(argv, minish->envp));
	if (ft_strcmp(argv[0], "export"))
		return (builtin_export(minish, argv));
	if (ft_strcmp(argv[0], "unset"))
		return (builtin_unset(minish, argv));
	if (ft_strcmp(argv[0], "exit"))
		return (builtin_exit(minish, argv));
	return (1);
}
