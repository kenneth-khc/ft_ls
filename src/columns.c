/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   columns.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 20:19:13 by kecheong          #+#    #+#             */
/*   Updated: 2026/09/22 00:06:35 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <math.h>
#include "entry.h"
#include "ft_vec.h"
#include "libft.h"

int	get_terminal_width()
{
	const char		*width = getenv("COLUMNS");
	struct winsize	ws;

	if (width)
	{
		return (ft_atoi(width));
	}
	else
	{
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
		return (ws.ws_col);
	}
}

int	calculate_max_possible_cols(int num_entries)
{
	// struct winsize	ws;
	const int		MIN_ENTRY_SIZE = 3;
	int				most_optimistic;
	const int		terminal_width = get_terminal_width();

	// ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	most_optimistic = ceil((float)terminal_width / MIN_ENTRY_SIZE);
	if (num_entries < most_optimistic)
	{
		return (num_entries);
	}
	else
	{
		return (most_optimistic);
	}
}

#include <stdio.h>

// TODO: pass terminal window size as parameter
int	bruteforce_columns(int max_cols, struct s_entry *entries)
{
	// struct winsize	ws;
	const int		terminal_width = get_terminal_width();
	const size_t	n = ft_vec_len(entries);
	int				*max_col_widths;

	// ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	while (max_cols > 0)
	{
		int	rows = ceil((float)n / max_cols);
		// int	rows = (n + max_cols - 1) / max_cols;
		max_col_widths = ft_vec_init_with(max_cols, sizeof(int));
		ft_bzero(max_col_widths, max_cols * sizeof(int));
		size_t i = 0;
		while (i < n)
		{
			int col_index = i / rows;
			int width = ft_strlen(entries[i].name);
			if (col_index != max_cols - 1)
			{
				width += 2;
			}
			if (max_col_widths[col_index] < width)
			{
				max_col_widths[col_index] = width;
			}
			i++;
		}

		// sum up all columns and see if it fits within terminal size
		int	j = 0;
		int	sum = 0;
		while (j < max_cols)
		{
			sum += max_col_widths[j];
			j++;
		}
		if (sum <= terminal_width)
		{
			// printf("%d columns, sum of %d fits %d\n", max_cols, sum, ws.ws_col);
			return (max_cols);
		}
		else
		{
			// printf("%d columns, sum of %d does not fit %d\n", max_cols, sum, ws.ws_col);
		}

		// printf("%d rows for %d cols\n", rows, max_cols);
		max_cols--;
		ft_vec_free(max_col_widths);
	}

	return 1;
}
