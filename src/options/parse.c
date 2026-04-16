/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:38:53 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/15 17:56:22 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"
#include "options/options.h"
#include "filepaths.h"
#include "libft.h"
#include "ft_printf.h"

void	parse_long_option(char *arg, struct s_options *options)
{
	size_t			i;
	struct s_option	*opt;

	i = 0;
	arg++;
	arg++;
	while (i < options->num_opts)
	{
		opt = &options->opts[i];
		if (ft_strcmp(arg, opt->long_name) == 0)
		{
			opt->is_on = true;
			return ;
		}
		i++;
	}
	ft_panic(2, "ft_ls: unrecognized option '%s'\n"
		"Try 'ft_ls --help' for more information\n", arg);
}

void	parse_short_option(const char *arg, struct s_options *options)
{
	size_t			i;
	bool			is_valid_option;
	struct s_option	*opt;

	arg++;
	while (*arg)
	{
		i = 0;
		is_valid_option = false;
		while (i < options->num_opts)
		{
			opt = &options->opts[i];
			if (*arg == *opt->short_name)
			{
				opt->is_on = true;
				is_valid_option = true;
			}
			i++;
		}
		if (!is_valid_option)
			ft_panic(2, "ft_ls: invalid option -- '%c'\n"
				"Try 'ft_ls --help' for more information\n", *arg);
		arg++;
	}
}

struct s_filepath  *parse_args(char **argv, struct s_options *options)
{
	struct s_filepath	*vec;

	vec = ft_vec_init(sizeof (struct s_filepath));
	if (vec == NULL)
	{
		ft_panic(1, "oops~\n");
	}
	while (*argv != NULL)
	{
		if (ft_str_startswith(*argv, "--"))
		{
			parse_long_option(*argv, options);
		}
		else if (ft_str_startswith(*argv, "-"))
		{
			parse_short_option(*argv, options);
		}
		else
		{
			vec = ft_vec_append(vec, &(struct s_filepath){.str = *argv});
		}
		argv++;
	}
	return (vec);
}

void	pretty_print_options(const struct s_options *opts)
{
	size_t					i;
	const struct s_option	*opt;

	i = 0;
	while (i < opts->num_opts)
	{
		opt = &opts->opts[i];
		if (opt->is_on)
		{
			ft_printf("%s | ", "Yes");
		}
		else
		{
			ft_printf("%s | ", "No ");
		}
		ft_printf("%s | %s\n", opt->short_name, opt->long_name);
		i++;
	}
}
