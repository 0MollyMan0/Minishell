/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemonthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 09:50:10 by jemonthi          #+#    #+#             */
/*   Updated: 2026/03/22 12:21:51 by jemonthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_heredoc(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 1)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

static void	handle_heredoc(t_redir *redir)
{
	int		fd;

	fd = open("/tmp/minishell_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc");
		return ;
	}
	write_heredoc(fd, redir->filename);
	close(fd);
	free(redir->filename);
	redir->filename = ft_strdup("/tmp/minishell_heredoc");
}

void	prepare_heredocs(t_cmd *cmds)
{
	t_cmd	*cur;
	t_redir	*redir;

	cur = cmds;
	while (cur)
	{
		redir = cur->redirs;
		while (redir)
		{
			if (redir->type == TOKEN_HEREDOC)
				handle_heredoc(redir);
			redir = redir->next;
		}
		cur = cur->next;
	}
}
