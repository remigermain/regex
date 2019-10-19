# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgermain <rgermain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/07 13:02:13 by loiberti          #+#    #+#              #
#    Updated: 2019/10/11 19:05:49 by rgermain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #

NAME = regex
TYPE = "of the executable"

LIBFT_M :
	@make -C libft/ all

CFLAGS = -g3 -Wall -Wextra

INCLUDE = -Iincludes -Ilibft/includes

HEADER = regex.h

LIBFT = libft/libft.a

CC = gcc

OBJ = $(SRC:.c=.o)

DSRC = srcs/
DOBJ = obj/
MDOBJ = obj/ obj/tools
ALL_D = $(DSRC)

DHEADER = includes/

CSRC = $(addprefix $(DSRC),$(SRC))
COBJ = $(addprefix $(DOBJ),$(OBJ))
CHEADER = $(addprefix $(DHEADER),$(HEADER))

# *****************************************************************************#
# 								ALL  SCRS									   #
# *****************************************************************************#

SRC =	main.c regex_utils.c regex_exec.c regex_meta.c regex_meta_type.c \
		regex_class.c regex_quantifier.c regex_quantifier_get.c regex_enclosed.c \
		regex_enclosed_capt.c regex_span.c regex_replace.c \

COUNT = "1"
SPACE = "                    "
.DEFAULT_GOAL := all
 ESC = $(shell printf '\033')

print_name :
	@printf "\n----------------------------------------------------------------------\n\n\033[37m"
	@printf " \033[47m  \033[0m\033[37m                    [    REGEX_CORE    ]            "
	@printf "         \033[0m  \033[47m  \033[0m\n"
	@printf "\n----------------------------------------------------------------------\n\n"

print_norme :
	@printf "\n----------------------------------------------------------------------\n\n\033[37m"
	@printf " \033[47m  \033[0m\033[37m                    [   REGEX NORME     ]      "
	@printf "         \033[0m  \033[47m  \033[0m\n"
	@printf "\n----------------------------------------------------------------------\n\n"

all: LIBFT_M print_name $(NAME)
	@if [ $(COUNT) = "1" ]; then \
		echo $(SPACE)"\033[1;34m   Nothing are changed !\033[0m"; \
	fi

$(NAME): $(COBJ) $(LIBFT)
	@echo $(SPACE)"\033[JCompilation\033[38;5;326m completed\033[0m"
	@echo $(SPACE)"Compilation" $(TYPE) "\033[34m" $(NAME) "\033[0m"
	@$(CC) $(COBJ) $(CFLAGS) $(NCURSES) $(LIBFT) -o $(NAME)

$(DOBJ)%.o : $(DSRC)%.c $(CHEADER) $(LIBFT)
	@$(eval COUNT = "0")
	@mkdir -p $(MDOBJ)
	@mkdir -p $(addprefix $(DOBJ), $(ALL_D))
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo $(SPACE)"Compilation from fonction \033[38;5;326m"$< "\033[0m\033[K\033[1A"

clean: print_name
	@rm -rf $(DOBJ)
	@echo $(SPACE)"Deleting \033[38;5;265mobjects\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo $(SPACE)"Deleting \033[38;5;265m"$(NAME) "\033[0m"


re: print_name
	@rm -f $(NAME)
	@rm -rf $(DOBJ)
	@echo $(SPACE)"Deleting \033[38;5;265m"$(NAME) "\033[0m"
	@echo $(SPACE)"Deleting \033[38;5;265mobjects\033[0m"
	@make all

info: print_name
	@printf $(SPACE)"total functions : ${ESC}[1;34m"
	@echo "$(shell cat $(CSRC) $(CHEADER) | sed 's/^[a-z*_]\+[[:blank:]]\+[*a-z_]\+(\(.\)*);/REMIREMIREMI/g' | grep REMIREMIREMI | wc -l)"
	@printf "${ESC}[0m\n";
	@printf $(SPACE)"total lines : ${ESC}[1;34m"
	@echo "$(shell cat $(CSRC) $(CHEADER) | sed '/^\*\*.*/d' | sed '/^\/\*.*/d' | sed '/^\*\/.*/d' | sed '/^[[:blank:]]*\/\/.*/d' | grep . | wc -l)"
	@printf "${ESC}[0m\n";
	@printf $(SPACE)"total commit : ${ESC}[1;34m"	
	@git rev-list --all --count
	@printf "${ESC}[0m\n";
	@printf $(SPACE)"last modifications : ${ESC}[1;34m"	
	@git log| head -n5 | grep Date | cut -c 9-
	@printf "${ESC}[0m\n";
	
norme : print_norme
	@norminette $(CSRC) $(CHEADER) | sed "s,Norme,${ESC}[38;5;326m&${ESC}[0m," | sed "s/Error/  Error/g" | sed "s,Error,${ESC}[31m&${ESC}[0m,"


.PHONY: default all fclean clean re norme print_norme print_name
