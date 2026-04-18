/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:17:32 by anfouger          #+#    #+#             */
/*   Updated: 2026/04/18 19:27:07 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_minish	init_minish(int ac, char **av, char **envp)
{
	t_minish	minish;

	(void)ac;
	(void)av;
	minish.exit_status = 0;
	minish.envp = dup_tab(envp);
	minish.input = NULL;
	minish.tokens = NULL;
	minish.cmds = NULL;
	return (minish);
}

int	main(int ac, char **av, char **envp)
{
	t_minish	minish;

	minish = init_minish(ac, av, envp);
	setup_signals();
	while (1)
	{
		minish.input = read_input();
		if (!minish.input)
			break ;
		add_history(minish.input);
		minish.tokens = tokenize(minish.input);
		minish.cmds = parser(minish.tokens);
		if (g_signal != 0)
			minish.exit_status = g_signal;
		minish.cmds = expansion(minish, minish.cmds);
		signal(SIGINT, SIG_IGN);
		execute(&minish);
		setup_signals();
		free_all(&minish);
	}
	free_tab(minish.envp);
	exit_minish();
	return (0);
}
