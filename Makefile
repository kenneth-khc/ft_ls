NAME := ft_ls

CC := clang

include_dir := include

src_dir := src
srcs := $(src_dir)/main.c

build_dir := build
objs := $(srcs:$(src_dir)/%.c=$(build_dir)/%.o)

libft_dir := libft
libft := $(libft_dir)/libft.a

CPPFLAGS := -I $(libft_dir)/includes -I $(include_dir)
LDFLAGS := -L $(libft_dir)
LDLIBS := -lft

all: $(NAME)

$(NAME): $(libft) $(objs)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(objs) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(build_dir):
	mkdir -p $@

$(build_dir)/%.o: $(src_dir)/%.c | $(build_dir)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -c -o $@

$(libft):
	@if git submodule status | grep '^[+-]' ; then \
		printf "Initializing libft submodule...\n" ; \
		git submodule update --init ; \
	fi
	@$(MAKE) -C $(libft_dir)

clean:
	$(RM) $(objs)

fclean: clean
	$(RM) $(NAME)

re: fclean all

watch:
	trap "exit" INT; \
	while true; do \
		find $(src_dir) $(include_dir) -type f \
	  | entr -cdp scripts/update_header_and_recompile.sh /_ ; \
	done

.PHONY: all clean fclean re
