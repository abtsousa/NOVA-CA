#!/bin/bash
# by Afonso Brás Sousa LEI-65263
# and Alexandre Cristóvão LEI-65143

# Constants
TMP_FILE=$(mktemp) #Alternativa: $(mktemp)
HELP_MESSAGE="usage: $0 path/to/directory hashfile.txt"

# Errors
SUCCESS=0
ERROR_TOO_MANY_ARGUMENTS="You have entered too many arguments."
TOO_MANY_ARGUMENTS=1
ERROR_TOO_FEW_ARGUMENTS="You have entered too few arguments."
TOO_FEW_ARGUMENTS=2
ERROR_INVALID_DIRECTORY="You have specified an invalid directory."
INVALID_DIRECTORY=3
ERROR_INVALID_FILE="You have specified an invalid file."
INVALID_FILE=4

# Argument checker
arg_check() {
  ## 2 arguments only
  if [ $# -gt 2 ]; then
    echo "$ERROR_TOO_MANY_ARGUMENTS"
    return $TOO_MANY_ARGUMENTS
  elif [ $# -lt 2 ]; then
    echo "$ERROR_TOO_FEW_ARGUMENTS"
    return $TOO_FEW_ARGUMENTS
  fi

  ## $1 is directory
  # TODO testar se funciona caso o argumento seja "./directoria/" vs "directoria"
  if [ ! -d "$1" ]; then
    echo "$ERROR_INVALID_DIRECTORY"
    return $INVALID_DIRECTORY
  else
    curr_folder=$1
    curr_folder=${curr_folder%/} #removes extra slash
  fi

  ## $2 is file
  if [ ! -f "$2" ] || [ ! -r "$2" ]; then
    echo "$ERROR_INVALID_FILE"
    return $INVALID_FILE
  else
    curr_file="$2"
  fi
}

# Main

# Exit if error found
arg_check "$@"
error_code=$?

# Alternativa: if ! arg_check "$@"; then

if [ ! "$error_code" -eq 0 ]; then
  echo "$HELP_MESSAGE"
  exit $error_code
fi

# Finds each file in curr_folder, alculates their hashes, sorts them and saves them to a temporary file
# print0 z and r0 strip newlines from the feed
find "$curr_folder" -type f -exec sha1sum {} \; | sort -k 2 > "$TMP_FILE"
# Alt: find "$curr_folder" -type f -print0 | sort -z | xargs -r0 sha1sum > "$TMP_FILE"

# compara compares both text files and returns the line numbers of differing lines
diff_lines=$(./compara "$TMP_FILE" "$curr_file")

echo "$diff_lines"

#if [ "$diff_lines" == "OK" ]; then # if there are no different files
#  echo "OK"
#else
#  files=$(find "$curr_folder"/* -type f | sort)
#  for n in $diff_lines; do
#    # echo the last line (tail) of the first N lines (head) == echo the nth line
#    echo "$n $(echo "$files" | head -n "$n" | tail -1)"
#  done
#fi

exit $SUCCESS
