#==============================================================================#
#                                 Files and Paths                              #
#==============================================================================#

SRCS = $(addprefix $(SRCS_PATH)/, main.c activity.c philo_free.c ini_philos.c threads.c \
			 philo_utils.c time_utils.c) 

OBJS = $(addprefix $(BUILD_PATH)/, $(notdir $(SRCS:.c=.o)))


NAME = philo 

BUILD_PATH = .build
SRCS_PATH = ./srcs

#==============================================================================#
#                                   Alias                                      #
#==============================================================================#

RM = rm -rf
AR = ar rcs
CFLAGS = -g -Wall -Werror -Wextra
LEAKS = -fsanitize=leak
TH = -fsanitize=thread

#==============================================================================#
#                                    Rules                                     #
#==============================================================================#

all: $(BUILD_PATH) $(OBJS) $(NAME)

$(NAME):
	@cc $(CFLAGS) $(TH) $(OBJS) -o $(NAME)
	@echo "$(GRN)[philo successfully created]$(D)"

$(BUILD_PATH):
	@mkdir $(BUILD_PATH)
	
$(BUILD_PATH)/%.o: $(SRCS_PATH)/%.c
	@cc $(CFLAGS) -o $@ -c $<

clean: 
	@$(RM) $(BUILD_PATH)
	@echo "$(BCYA)[clean] Objects removed$(D)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(BCYA)[fclean] Executable removed$(D)"

re: fclean all

#==============================================================================#
#                                  UTILS                                       #
#==============================================================================#

# Colors
#
# Run the following command to get list of available colors
# bash -c 'for c in {0..255}; do tput setaf $c; tput setaf $c | cat -v; echo =$c; done'
#
B  		= $(shell tput bold)
BLA		= $(shell tput setaf 0)
RED		= $(shell tput setaf 1)
GRN		= $(shell tput setaf 2)
YEL		= $(shell tput setaf 3)
BLU		= $(shell tput setaf 4)
MAG		= $(shell tput setaf 5)
CYA		= $(shell tput setaf 6)
WHI		= $(shell tput setaf 7)
GRE		= $(shell tput setaf 8)
BRED 	= $(shell tput setaf 9)
BGRN	= $(shell tput setaf 10)
BYEL	= $(shell tput setaf 11)
BBLU	= $(shell tput setaf 12)
BMAG	= $(shell tput setaf 13)
BCYA	= $(shell tput setaf 14)
BWHI	= $(shell tput setaf 15)
D 		= $(shell tput sgr0)
BEL 	= $(shell tput bel)
CLR 	= $(shell tput el 1)
