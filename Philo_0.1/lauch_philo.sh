#!/bin/bash
# echo "Launching minishell"
# make && ./minishell
make && valgrind --leak-check=full --trace-children=yes --quiet --track-fds=yes ./minishell
# make && valgrind --trace-children=yes --track-fds=yes ./minishell
# valgrind --leak-check=full ./minishell
# make && valgrind --leak-check=full --trace-children=yes --show-leak-kinds=all .
