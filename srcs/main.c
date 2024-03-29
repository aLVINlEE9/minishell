/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:17:37 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/23 16:20:30 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_all(t_data *data, char **cmd, struct s_termi *termi, char **envp)
{
	parse_env(envp, data);
	cmd = unset_oldpath();
	built_unset(data, cmd);
	free_cmd(cmd);
	cmd = export_oldpath();
	built_export(data, cmd);
	free_cmd(cmd);
	set_termi(termi);
	data->termi = *termi;
	update_shlvl(data);
	update_home(data);
}

void	get_line(t_data *data)
{
	char	*str;

	while (1)
	{
		termi_new(data->termi);
		set_signal();
		data->heredoc_is_still_alive = 0;
		str = readline("minishell$ ");
		if (str == 0)
		{
			printf("\033[1A");
			printf("\033[10C");
			printf(" exit\n");
			free(str);
			break ;
		}
		else if (str)
		{
			add_history(str);
			if (parse_token(data, str))
				pipex(data);
			free_for_line(data);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data			data;
	char			**cmd;
	struct s_termi	termi;

	(void)argc;
	(void)argv;
	cmd = 0;
	init_all(&data, cmd, &termi, envp);
	get_line(&data);
	termi_old(data.termi);
	free_for_all(&data);
}
