/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 23:28:07 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/18 18:31:57 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options/options.h"
#include "libft.h"

struct s_option	make_option(const char *short_opt, const char *long_opt)
{
	struct s_option	option;

	option.short_name = short_opt;
	option.long_name = long_opt;
	option.is_on = false;
	return (option);
}

struct s_options	init_program_options(void)
{
	struct s_options	options;

	options.opts[0] = make_option("l", "l");
	options.opts[1] = make_option("R", "recursive");
	options.opts[2] = make_option("a", "all");
	options.opts[3] = make_option("r", "reverse");
	options.opts[4] = make_option("t", "t");
	options.num_opts = 5;
	return (options);
}

bool	is_option_enabled(const struct s_options *options,
						const char *short_opt)
{
	size_t		i;
	const char	*short_name;

	i = 0;
	while (i < options->num_opts)
	{
		short_name = options->opts[i].short_name;
		if (ft_strcmp(short_name, short_opt) == 0)
		{
			return (options->opts[i].is_on);
		}
		i++;
	}
	return (false);
}
