/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 08:20:49 by anfouger          #+#    #+#             */
/*   Updated: 2026/03/10 10:34:57 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	exec_path(t_minish *minish, char **envp)
{
	pid_t	pid;
	int		status;
	char	*path;
	
	pid = fork();
	if (pid == 0)
	{
		path = find_path(minish->cmds->argv[0], envp);
		execve(path, minish->cmds->argv, envp);
		perror("execve");
		exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			minish->g_exit_status = WEXITSTATUS(status);
	}
}

static void	exec_direct(t_minish *minish, char **envp)
{
	pid_t	pid;
	int		status;
	
	pid = fork();
	if (pid == 0)
	{
		execve(minish->cmds->argv[0], minish->cmds->argv, envp);
		perror("execve");
		exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			minish->g_exit_status = WEXITSTATUS(status);
	}
}

void	exec(t_minish *minish, char **envp)
{
	if (!minish->cmds || !minish->cmds->argv || !minish->cmds->argv[0])
		return ;
	if (is_slash_in(minish->cmds->argv[0]))
		exec_direct(minish, envp);
	else
		exec_path(minish, envp);
}
