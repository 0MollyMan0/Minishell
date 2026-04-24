/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemonthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 04:11:02 by jemonthi          #+#    #+#             */
/*   Updated: 2026/03/15 04:58:38 by jemonthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipes_child(int i, int nb_cmds, int **pipes)
{
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < nb_cmds - 1)
		dup2(pipes[i][1], STDOUT_FILENO);
}

void	check_ret_value(int ret, char *path, t_minish *minish)
{
	if (ret == -1)
	{
		if (errno == EACCES)
		{
			ft_putstr_fd("minishell: Permission denied\n", 2);
			call_free_all(path, minish);
			_exit (126);
		}
		else if (errno == ENOENT)
		{
			ft_putstr_fd("minishell: No such file or directory\n", 2);
			call_free_all(path, minish);
			_exit (127);
		}
		else if (errno == ENOEXEC)
		{
			if (minish->cmds->argv[0][0] == '.'
				|| minish->cmds->argv[0][0] == '/')
				execve("/bin/sh", minish->cmds->argv, minish->env->envp);
			else
				execve("/bin/sh", (char *[]){"sh", path, NULL}, minish->env->envp);
		}
	}
}

void	check_access(t_cmd *cmd)
{
	struct stat	st;

	if (stat(cmd->argv[0], &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			ft_putstr_fd("minishell: Is a directory\n", 2);
			exit(126);
		}
	}
}

// void	check_access(t_cmd *cmd)
// {
// 	int	fd;

// 	if (access(cmd->argv[0], F_OK) == 0)
// 	{
// 		fd = open(cmd->argv[0], O_DIRECTORY);
// 		if (fd != -1)
// 		{
// 			close(fd);
// 			ft_putstr_fd("minishell: Is a directory\n", 2);
// 			_exit (126);
// 		}
// 	}
// }

void	exec_external(t_minish *minish)
{
	char	*path;
	int		ret;

	path = NULL;
	if (minish->cmds->argv[0][0] == '.' || minish->cmds->argv[0][0] == '/')
	{
		check_access(minish->cmds);
		ret = execve(minish->cmds->argv[0], minish->cmds->argv, minish->env->envp);
	}
	else
	{
		path = resolve_cmd(minish->cmds->argv[0], minish->env->envp);
		if (!path)
		{
			ft_putstr_fd("minishell: command not found\n", 2);
			free_all(minish, 1);
			_exit(127);
		}
		ret = execve(path, minish->cmds->argv, minish->env->envp);
	}
	check_ret_value(ret, path, minish);
	call_free_all(path, minish);
	_exit(1);
}

/* ---- Child process ---- */
void	child_process(t_minish *minish, t_cmd *cmd, int i, t_exec *exec)
{
	int	ret;

	signal(SIGPIPE, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_pipes_child(i, exec->nb_cmds, exec->pipes);
	if (cmd->redirs)
	{
		if (apply_redirs(cmd->redirs))
			free_minish_exit_one(minish);
	}
	close_all_pipes(exec->pipes, exec->nb_cmds - 1);
	if (!cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
		free_minish_exit_zero(minish);
	if (is_builtin(cmd->argv[0]))
	{
		ret = exec_builtin(cmd, minish, 1);
		free_all(minish, 1);
		_exit(ret);
	}
	exec_external(minish);
}
