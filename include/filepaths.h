/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filepaths.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:12:02 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/09 21:28:03 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEPATHS_H
# define FILEPATHS_H

# include <stddef.h>

struct s_filepath
{
	char	*str;
};

struct s_filepaths
{
	struct s_filepath	*arr;
	size_t				num_filepaths;
};

void	add_filepath(struct s_filepaths *filepaths, char *arg);

#endif
