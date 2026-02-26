/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_case.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 09:41:16 by anfouger          #+#    #+#             */
/*   Updated: 2026/02/24 11:11:38 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	var_case(char *str, char **new_str, int	*i)
{
	char	*var;
	int		i_var;

	i_var = 0;
	var = get_var(str, *(&i));
	if (!var)
		*new_str = NULL;
	while (var && var[i_var])
	{
		*new_str = add_char(*new_str, var[i_var]);
		if (!*new_str)
			return ;
		i_var++;
	}
}

// void	var_inter(char *str, char **new_str, int	*i)
// {
// 	char	*var;
// 	int		i_var;

// 	i_var = 0;
// 	var = get_var(str, *(&i));
// 	if (!var)
// 		*new_str = NULL;
// 	while (var && var[i_var])
// 	{
// 		*new_str = add_char(*new_str, var[i_var]);
// 		if (!*new_str)
// 			return ;
// 		i_var++;
// 	}
// }
