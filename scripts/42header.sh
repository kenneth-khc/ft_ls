#!/usr/bin/env bash

## Creates or updates a 42 Header for a given file

## Searches for your username and email from the environment,
## looking for FT_USER/FT_MAIL > USER/MAIL, defaulting to marvin otherwise

## Currently only supports C and C++ files ending in .c, .h, .cpp, .hpp, .cxx, .hxx

## TODO
## - Ensure long names or emails don't break the formatting
## - Support more languages and file extensions
## - Accept more than just a single file to format
## - More strict matching to check whether a header exists

set -euo pipefail

if [[ $# -ne 1 ]]; then
	echo >&2 "Error. Usage: $0 <filename>"
	exit 1
fi

filepath=$1
if [[ ! -f "$filepath" ]]; then
	echo >&2 "Error. '$filepath' does not exist."
	exit 1
fi

filename=$(basename "$filepath")

extension=${filename##*.}
if [[ ! $extension =~ ^(c|h|cpp|hpp|cxx|hxx)$ ]]; then
	echo >&2 "Error. Unsupported file extension '$extension'"
	exit 1
fi

width=80
padding=3
margin=5
start="/*"
end="*/"
name="${FT_USER:-${USER:-"marvin"}}"
mail="${FT_MAIL:-${MAIL:-"marvin@42.fr"}}"
ascii_art=(
	"        :::      ::::::::"
	"      :+:      :+:    :+:"
	"    +:+ +:+         +:+  "
	"  +#+  +:+       +#+     "
	"+#+#+#+#+#+   +#+        "
	"     #+#    #+#          "
	"    ###   ########.fr    "
)
readonly width padding margin start end name mail ascii_art

by="By: $name <$mail>"
date_time=$(date "+%Y/%m/%d %H:%M:%S")
created="Created: $date_time by $name"
updated="Updated: $date_time by $name"
readonly date_time by created updated

function border() {
	local inner_char="*"
	local inner_len=$((width - ${#start} - ${#end} - 2))
	local inner

	inner=$(printf "%${inner_len}s" " " | tr " " "$inner_char")
	printf "%s %s %s" "$start" "$inner" "$end"
}

function spaces() {
	local len=$1
	printf "%${len}s" " "
}

function str() {
	printf "%s" "$1"
}

function mkline() {
	local words=$1
	local art=$2
	local inner_padding=$((width - (margin * 2) - ${#words} - ${#art}))

	printf "%s%s%s%s%s%s%s" "$(str "$start")" "$(spaces ${padding})" \
		"$(str "$words")" "$(spaces ${inner_padding})" \
		"$(str "$art")" "$(spaces ${padding})" \
		"$(str "$end")"
}
current_updated_line=$(sed -n '9p' "$filepath" 2>/dev/null)
new_updated_line=$(mkline "$updated" "${ascii_art[6]}")
if [[ "$current_updated_line" == "$new_updated_line" ]]; then
	exit 0
fi

function insert_new_header() {
	temp_file=$(mktemp)
	cat <<EOF >"$temp_file"
$(border)
$(mkline "" "")
$(mkline "" "${ascii_art[0]}")
$(mkline "$filename" "${ascii_art[1]}")
$(mkline "" "${ascii_art[2]}")
$(mkline "$by" "${ascii_art[3]}")
$(mkline "" "${ascii_art[4]}")
$(mkline "$created" "${ascii_art[5]}")
$(mkline "$updated" "${ascii_art[6]}")
$(mkline "" "")
$(border)
$(echo)
EOF
	cat "$filepath" >>"$temp_file"
	mv "$temp_file" "$filepath"
}

function update_header() {
	temp_file=$(mktemp)
	cat <<EOF >"$temp_file"
$(border)
$(mkline "" "")
$(mkline "" "${ascii_art[0]}")
$(mkline "$filename" "${ascii_art[1]}")
$(mkline "" "${ascii_art[2]}")
$(sed -n '6p' "$filepath")
$(mkline "" "${ascii_art[4]}")
$(sed -n '8p' "$filepath")
$(mkline "$updated" "${ascii_art[6]}")
$(mkline "" "")
$(border)
EOF
	tail -n +12 "$filepath" >>"$temp_file"
	mv "$temp_file" "$filepath"
}

header_regex=$'^(.{80}(\r\n|\n)){10}.{80}(\r\n|\n)?'
first_eleven_lines=$(head -n 11 "$filepath")
if [[ "$first_eleven_lines" =~ $header_regex ]]; then
	update_header
else
	insert_new_header
fi
