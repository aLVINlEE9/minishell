/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:37:02 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/06 20:48:03 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_quot(char c)
{
    if (c == '\'' || c == '\"')
        return (1);
    return (0);
}

int is_space(char c)
{
    if (c == ' ')
        return (1);
    return (0);
}

void    parse_cmd(t_data *data, char *str)
{
    int i;
    t_parse parse;

    i = -1;
    parse_init(&parse, 3);
    while (str[i + 1])
    {
        if (is_space(str[i]) && !is_space(str[i + 1]) && !is_quot(str[i]))
        {
            
        }
        i++;
    }
}