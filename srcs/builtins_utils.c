/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:07:01 by dcyprien          #+#    #+#             */
/*   Updated: 2022/04/28 16:12:53 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_echo(char *cmd)
{
	int	k;

	k = 0;
	while (cmd && cmd[k])
	{
		if (cmd[k] == ' ' && k == 0)
			k++;
		ft_putchar_fd(cmd[k], 1);
		if (cmd[k])
			k++;
	}
}

char	*skip_spaces(char *cmd)
{
	int		i;
	int		k;
	char	*str;

	i = -1;
	k = -1;
	str = ft_strdup(cmd);
	if (!cmd)
		return (NULL);
	while (cmd[++i])
	{
		while (cmd[i] && cmd[i] != ' ')
			str[++k] = cmd[i++];
		while (cmd[i])
		{
			if (cmd[i] != ' ')
				break ;
			i++;
		}
		if (--i != (int)ft_strlen(cmd) - 1)
			str[++k] = ' ';
	}
	str[++k] = 0;
	secure_free((void **)&cmd);
	return (str);
}

int	file_test(char *tmp, int i, int k)
{
	while (tmp[i] != ' ' && tmp[i])
		i++;
	if (test_file(tmp, i, k) == -1)
	{
		secure_free((void **)&tmp);
		return (-1);
	}
	return (i - k + 2);
}

char	*access_path(char **tmp_path, char *tmp, t_data *data)
{
	int	i;

	i = -1;
	while (tmp_path[++i])
	{
		tmp = ft_strcat(tmp_path[i], data->cmd[0]);
		if (tmp && access(tmp, F_OK & X_OK) == 0)
		{
			data->path = ft_strdup(tmp);
			free_malloc(tmp_path, tmp, 2);
			return (data->path);
		}
		secure_free((void **)&tmp);
	}
	free_malloc(tmp_path, data->cmd[0], 1);
	return (NULL);
}
