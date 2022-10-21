/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:48:03 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/21 16:23:09 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_newline(char *token)
{
	if (ft_strncmp(token, "<<", -1) == 0 || ft_strncmp(token, ">>", -1) == 0 || \
		ft_strncmp(token, "<", -1) == 0 || ft_strncmp(token, ">", -1) == 0)
		return (1);
	return (0);
}

int	syntax_pipe(char *token)
{
	if (ft_strncmp(token, "|", -1) == 0)
		return (1);
	return (0);
}
