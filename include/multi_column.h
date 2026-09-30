/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_column.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 15:55:10 by kecheong          #+#    #+#             */
/*   Updated: 2026/09/30 20:21:07 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTI_COLUMN_H
# define MULTI_COLUMN_H

# include <stddef.h>

typedef struct s_col
{
	char	*str;
}	t_col;

typedef struct s_row
{
	t_col	*cols;
}	t_row;

typedef struct s_multi_column
{
	size_t	num_cols;
	t_row	*rows;
}	t_multi_column;

typedef struct s_column_info
{
	size_t	output_width;
	size_t	max_cols;
}	t_column_info;

#endif
