/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemonthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 02:10:23 by jemonthi          #+#    #+#             */
/*   Updated: 2026/03/22 12:44:16 by jemonthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_minish_exit_zero(t_minish *minish)
{
	free (minish);
	free_tab(minish->envp);
	_exit(0);
}

void	free_minish_exit_one(t_minish *minish)
{
	free (minish);
	free_tab(minish->envp);
	_exit(1);
}

void	call_free_all(char *path, t_minish *minish)
{
	free(path);
	free_all(minish);
	free_tab(minish->envp);
}
