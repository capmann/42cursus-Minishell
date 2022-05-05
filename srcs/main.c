/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:48:56 by dcyprien          #+#    #+#             */
/*   Updated: 2022/04/28 21:29:43 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

pid_t	g_pid;

int	main(int ac, char **av, char **envp)
{
	char				*prompt;
	t_list				*list;

	(void)av;
	if (ac != 1)
	{
		ft_putstr_fd("Error: too many arguments\n", 1);
		exit(0);
	}
	list = init(envp);
	while (42)
	{
		set_sigaction(0);
		prompt = readline("Mimi_shell>> ");
		if (ft_strlen(prompt) > 0)
			add_history(prompt);
		list->prems = parsing(prompt, list);
		run_shell(list);
		ft_free_data(list);
		secure_free((void **)&prompt);
	}
	ft_free_list(list);
	rl_clear_history();
	return (g_pid);
}