/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 23:22:57 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/09 21:21:45 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_H
# define OPTIONS_H

# include <stddef.h>
# include <stdbool.h>
# include "../filepaths.h"

struct s_option
{
	const char	*short_name;
	const char	*long_name;
	bool		is_on;
};

struct s_options
{
	struct s_option	opts[5];
	size_t			num_opts;
};

struct s_options	init_program_options(void);
char				*parse_args(char **argv, struct s_options *options,
						struct s_filepaths *filepaths);

// Debug
void				pretty_print_options(const struct s_options *opts);

#endif
