/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:37:02 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/06 23:44:19 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_dollar(char c)
{
    if (c == '$')
        return(1);
    return (0);
}

int is_dquot(char c)
{
    if (c == '\"')
        return (1);
    return (0);
}

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
    char    *s;
    char    *buf_q;
    char    *buf_s;
    int     dollar;

    s = str;
    buf_q = s;
    buf_s = s;
    dollar = 0;
    create_cmd_list(data);
    while (*(s + 1))
    {
        if (is_quot(*s))
        {
            buf_q = s;
            while(*buf_q)
            {
                if (is_dquot(*s) && is_dollar(*buf_q))
                    dollar = 1;
                if (*s == *buf_q)
                {
                    append_cmd(data->cmd_list, s, buf_q - s, dollar);
                    break ;
                }
                buf_q++;
            }
            s = buf_q;
        }
        if (is_space(*s) && !is_space(*(s + 1)) && !is_quot(*(s + 1)))
        {
            s++;
            buf_s = s;
            while (*buf_s)
            {
                buf_s++;
            }
        }
        s++;
    }
    if (!str && !buf) // quotation only once
    {
        printf("quotation only once\n");
    }
}