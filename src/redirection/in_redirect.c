/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:08:15 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/13 20:29:25 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	input_redirects(char **matrix)
{
	char	*name;
	int		mode;
	int		fd;

	mode = check_redirects(matrix, '<');
	if (!mode)
		return (0);
	//if (mode == 2)
		//here_docs
	name = file_name(matrix, '<');
	if (name == NULL)
		return (-1);
	return (open(name, O_RDONLY));
}
