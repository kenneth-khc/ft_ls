/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filepaths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:26:24 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/09 21:37:25 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filepaths.h"
#include "libft.h"
#include <stdlib.h>

void	add_filepath(struct s_filepaths *filepaths, char *arg)
{
	int					i;
	struct s_filepath	*new_arr;

	filepaths->num_filepaths++;
	new_arr = malloc(sizeof *new_arr * filepaths->num_filepaths);
	if (!new_arr)
	{
		ft_panic(1, "failed to malloc\n");
	}
	i = 0;
	while (i < filepaths->num_filepaths - 1)
	{
		new_arr[i].str = filepaths->arr[i].str;
		i++;
	}
	new_arr[i].str = arg;
	free(filepaths->arr);
	filepaths->arr = new_arr;
}
