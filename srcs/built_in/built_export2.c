/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:06:24 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/23 16:06:37 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_alnum(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		return (1);
	}
	else if (c >= 'A' && c <= 'Z')
	{
		return (1);
	}
	else if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int	is_alpha(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int	export_valid_check(char **cmd2, int i, char *ptr)
{
	int	j;

	j = 1;
	if (!is_alpha(cmd2[i][0]) && cmd2[i][0] != '_')
	{
		print_built_error("export: `", cmd2[i], "': \
						not a valid identifier");
		return (1);
	}
	while (cmd2[i][j] && ptr != &cmd2[i][j])
	{
		if (!is_alnum(cmd2[i][j]) && cmd2[i][j] != '_')
		{
			print_built_error("export: `", cmd2[i], "': \
						not a valid identifier");
			return (1);
		}
		j++;
	}
	return (0);
}
