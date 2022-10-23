/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 13:56:05 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/23 14:28:57 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_node(t_token_list *token_list)
{
	t_token	*now;

	now = token_list->head->next;
	while (now != token_list->tail)
	{
		printf("%s dollar:%d cmd:%d\n", now->token, now->in_dollar, now->is_cmd);
		now = now->next;
	}
	return (1);
}

void	print_env(t_env_list *env_list)
{
	t_env	*now;

	now = env_list->head->next;
	while (now != env_list->tail)
	{
		printf("%s ====  %s\n", now->key, now->val);
		now = now->next;
	}
}

void	free_for_line(t_data *data)
{
	t_token	*now;

	now = data->token_list->head->next;
	while (now != data->token_list->tail)
	{
		free(now->token);
		free(now);
		now = now->next;
	}
	free(data->token_list->head);
	free(data->token_list->tail);
	free(data->token_list);
}

void	free_for_all(t_data *data)
{
	t_env	*now;

	now = data->env_list->head->next;
	while (now != data->env_list->tail)
	{
		free(now->key);
		free(now->val);
		free(now);
		now = now->next;
	}
	free(data->env_list->head);
	free(data->env_list->tail);
	free(data->env_list);
}

char	**unset_oldpath(void)
{
	char	**ret;

	ret = (char **)malloc(sizeof(char *) * 3);
	ret[0] = ft_strdup("unset");
	ret[1] = ft_strdup("OLDPWD");
	ret[2] = 0;
	return (ret);
}
