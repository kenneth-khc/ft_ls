/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 23:48:22 by kecheong          #+#    #+#             */
/*   Updated: 2026/09/30 22:57:15 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options/options.h"
#include "filepaths.h"
#include "ft_vec.h"
#include <stddef.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include "entry.h"
#include "output.h"
#include "printer.h"
#include "ft_printf.h"
#include "libft.h"
#include "multi_column.h"
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include "columns.h"
#include <math.h>
#include "directory.h"
#include "sort.h"

void	process_directory_entries(struct s_entry **, struct s_options *, struct s_printer *);

int	get_terminal_width();

struct s_column_info
count_columns()
{
	struct winsize			ws;
	struct s_column_info	col_info;
	const int				MIN_ENTRY_SIZE = 3;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	col_info.output_width = ws.ws_col;
	col_info.max_cols = ws.ws_col / MIN_ENTRY_SIZE;

	return (col_info);
}

void	pp(void *entry)
{
	(void)entry;
	// struct s_entry *ent	= (struct s_entry *)entry;

	// printf(">>> %s\n", ent->name);
}

void	peek_entries(struct s_entry *entries)
{
	size_t	n = ft_vec_len(entries);

	if (n > 0)
	{
		for (size_t i = 0; i < n; ++i)
		{
			printf("%s", entries[i].name);
			if (i != n - 1)
			{
				printf(" ");
			}
		}
		printf("\n");
	}
	else
	{
		printf("No entries\n");
	}
}

void	do_files(struct s_entry *files)
{
		// t_column_info	col_info = count_columns();

		int n = ft_vec_len(files);
		int	max_possible_cols = calculate_max_possible_cols(n);
		peek_entries(files);
		struct s_entry	*sorted_files = sort_alphabetically_inefficiently(files);
		peek_entries(sorted_files);
		sorted_files = files;

		max_possible_cols = bruteforce_columns(max_possible_cols, files);

		int row = 0;
		int rows = ceil((float)n / max_possible_cols);
		// int	rows = ceil(n / max_possible_cols);
		while (row < rows)
		{
			int	col = 0;
			size_t	printed_chars = 0;
			while (col < max_possible_cols)
			{
				int	entry_index = (col * rows) + row;
				if (entry_index >= n)
				{
					break;
				}
				// if (printed_chars + ft_strlen(files[entry_index].name) <= (size_t)get_terminal_width())
				// {
					if (col != 0)
					{
						printf("  ");
						printed_chars += 2;
					}
					printf("%s", sorted_files[entry_index].name);
					printed_chars += ft_strlen(sorted_files[entry_index].name);
				// }
				col++;
			}
			printf("\n");
			row++;
		}
}

int	main(int argc, char **argv)
{
	struct s_options	options;
	struct s_filepath	*filepaths;
	struct s_entry		*files;
	struct s_entry		*directories;
	struct s_printer	printer;

	(void)argc;
	ft_bzero(&printer, sizeof printer);
	errno = 0;
	options = init_program_options();
	filepaths = parse_args(++argv, &options);
	if (ft_vec_len(filepaths) == 0)
	{
		filepaths = ft_vec_append(filepaths, &(struct s_filepath){.str = "."});
	}

	files = ft_vec_init(sizeof *files);
	directories = ft_vec_init(sizeof *directories);

	// 1. process file entries
	// 2. print out file entries
	// 3. process any directory entries
	// 4. if recursive, add more directory entries
	// 5. print current directory contents
	// 6. remove entry and repeat

	get_entries(filepaths, &options, &files, &directories);
	peek_entries(files);
	peek_entries(directories);
	while (ft_vec_len(directories) > 0)
	{
		fprintf(stderr, "> D: %zu F: %zu\n", ft_vec_len(directories), ft_vec_len(files));
		struct s_entry	*fs = read_directory(directories, &options);
		do_files(fs);
		ft_vec_pop_front(directories);
		fprintf(stderr, "> D: %zu F: %zu\n", ft_vec_len(directories), ft_vec_len(files));
	}

	// while (ft_vec_len(directories) > 0)
	// {
	// 	process_directory_entries(&directories, &options, &printer);
	// 	// ft_vec_pop_front(directories);
	// }
	// ft_printf("\n");

	// print_output(&options, files, directories);

	ft_vec_free(filepaths);
	ft_vec_free(files);
	ft_vec_free(directories);
}
