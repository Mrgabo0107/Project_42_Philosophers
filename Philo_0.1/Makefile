# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gamoreno <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/19 18:59:58 by gamoreno          #+#    #+#              #
#    Updated: 2023/01/19 19:26:24 by gamoreno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### Compilation ###

CC      = cc
FLAGS  = -Wall -Wextra -Werror -pthread -g3
# FLAGS  = -Wall -Wextra -Werror -pthread -g3 -fsanitize=thread
### Executable ###

NAME   = philo

### Includes ###

OBJ_PATH  = objs/
HEADER = includes/
SRC_PATH  = sources/

### Source Files ###
CORE_DIR	=	core/
CORS		=	main.c utils.c time.c actions.c 

ERR_DIR		=	error/
ERR			=	errors.c #debug.c

FREE_DIR	=	free/
FREE		=	free.c free_ret_one.c

INIT_DIR	=	init/
INIT		=	init1.c init2.c

SOURCES		+=	$(addprefix	$(CORE_DIR),$(CORS))
SOURCES		+=	$(addprefix	$(ERR_DIR),$(ERR))
SOURCES		+=	$(addprefix	$(FREE_DIR),$(FREE))
SOURCES		+=	$(addprefix	$(INIT_DIR),$(INIT))

### Objects ###

SRCS = $(addprefix $(SRC_PATH),$(SOURCES))
OBJS = $(addprefix $(OBJ_PATH),$(SOURCES:.c=.o))
DEPS = $(addprefix $(OBJ_PATH),$(SOURCES:.c=.d))

### COLORS ###
NOC         = \033[0m
GREEN       = \033[1;32m
CYAN        = \033[1;36m

### RULES ###

all: header tmp $(NAME)

tmp:
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)$(CORE_DIR)
	@mkdir -p $(OBJ_PATH)$(ERR_DIR)
	@mkdir -p $(OBJ_PATH)$(FREE_DIR)
	@mkdir -p $(OBJ_PATH)$(INIT_DIR)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $@ $^
	@echo "$(GREEN)Project compiled succesfully$(NOC)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(FLAGS) -MMD -c -o $@ $<
	@echo "$(CYAN)Creation of object file -> $(CYAN)$(notdir $@)... $(GREEN)[Done]$(NOC)"

clean:
	@echo "$(GREEN)Cleaning libraries files$(NOC)"
	@rm -rf $(OBJ_PATH)

fclean:
	@echo "$(GREEN)Cleaning all$(NOC)"
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME)

header:
	clear
	@echo "$$HEADER_PROJECT"

re: fclean all

-include $(DEPS)

.PHONY: tmp, re, fclean, clean

define HEADER_PROJECT
d8888b. db   db d888888b db       .d88b.  .d8888.  .d88b.  d8888b. db   db d88888b d8888b. .d8888. 
88  `8D 88   88   `88'   88      .8P  Y8. 88'  YP .8P  Y8. 88  `8D 88   88 88'     88  `8D 88'  YP 
88oodD' 88ooo88    88    88      88    88 `8bo.   88    88 88oodD' 88ooo88 88ooooo 88oobY' `8bo.   
88~~~   88~~~88    88    88      88    88   `Y8b. 88    88 88~~~   88~~~88 88~~~~~ 88`8b     `Y8b. 
88      88   88   .88.   88booo. `8b  d8' db   8D `8b  d8' 88      88   88 88.     88 `88. db   8D 
88      YP   YP Y888888P Y88888P  `Y88P'  `8888Y'  `Y88P'  88      YP   YP Y88888P 88   YD `8888Y' 
endef
export HEADER_PROJECT