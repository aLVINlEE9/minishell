/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_terminal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:08:43 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/12 19:44:02 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_termi(struct s_termi termi)
{
	struct termios	*save;
	struct termios	*new_term;

	save = malloc(sizeof(struct termios) * 1);
	new_term = malloc(sizeof(struct termios) * 1);
	if (!new_term | !save)
		return ;//exit?
	tcgetattr(0, save);
	tcgetattr(0, new_term);
	new_term -> c_lflag &= ~(ECHOCTL);
	new_term -> c_cc[VMIN] = 1;
	new_term -> c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, new_term);
	termi.save_t = save;
	termi.new_t = new_term;
}

void	termi_old(struct s_termi termi)
{
	tcsetattr(0, TCSANOW, termi.save_t);
}

void	termi_new(struct s_termi termi)
{
	tcsetattr(0, TCSANOW, termi.new_t);
}
