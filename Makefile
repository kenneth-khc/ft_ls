NAME := ft_ls

CC := clang

include_dir := include

src_dir := src
srcs := $(src_dir)/main.c

build_dir := build
objs := $(srcs:$(src_dir)/%.c=$(build_dir)/%.o)

all: $(NAME)

$(NAME): $(objs)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(objs) -o $(NAME)

$(build_dir):
	mkdir -p $@

$(build_dir)/%.o: $(src_dir)/%.c | $(build_dir)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -c -o $@

clean:
	$(RM) $(objs)

fclean: clean
	$(RM) $(NAME)

re: fclean all

watch:
	find $(src_dir) $(include_dir) -type f | entr -cp scripts/update_header_and_recompile.sh /_

.PHONY: all clean fclean re
