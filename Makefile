# ----------------------------------
# PROJECT NAME
# ----------------------------------
NAME = minishell
# ----------------------------------
# COMPILATION AND FLAGS
# ----------------------------------
CC     = cc
CCFLAGS= -Wall -Wextra -Werror -g -I ./

# ----------------------------------
# PATH
# ----------------------------------
PARS_DIR	= prepare_input
UTILS_DIR	= utils
OBJ_DIR    = obj

# ----------------------------------
# COLORS
# ----------------------------------
RESET       = \033[0m
BLACK       = \033[0;30m
RED         = \033[0;31m
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
BLUE        = \033[0;34m
MAGENTA     = \033[0;35m
CYAN        = \033[0;36m
WHITE       = \033[0;37m

# ----------------------------------
# SOURCES
# ----------------------------------
SRCS    = minishell.c \
		exit.c \
		$(PARS_DIR)/read_input.c \
		$(PARS_DIR)/signals.c \
		$(PARS_DIR)/tokenize.c \
		$(PARS_DIR)/free.c \
		$(PARS_DIR)/parser.c \
		$(UTILS_DIR)/utils_libft.c \
		$(UTILS_DIR)/utils_token.c \
		$(UTILS_DIR)/utils_cmd.c \


OBJS    = $(SRCS:.c=.o)

# ----------------------------------
# RULES
# ----------------------------------

all: $(NAME)

# Final link
$(NAME): $(OBJS)
	@echo "\033[1;34m[LINK] -> Creating $(NAME)...\033[0m"
	@$(CC) $(CCFLAGS) $(OBJS) -o $(NAME) -lreadline
	@echo "\033[1;32m[OK] -> $(NAME) ready!\033[0m"

# Compilation of .c in .o
%.o: %.c
	@echo "$(CYAN)[COMPILING]$(RESET) $<"
	@sleep 0.1
	@$(CC) $(CCFLAGS) -c $< -o $@

# Clean
clean:
	@echo "$(RED)[CLEAN]$(RESET) Removing object files..."
	@for file in $(OBJS); do \
		if [ -f $$file ]; then \
			echo "  $(YELLOW)→ removing$(RESET) $$file"; \
			rm -f $$file; \
			sleep 0.05; \
		fi \
	done

# Full Clean
fclean: clean
	@echo "$(RED)[FCLEAN]$(RESET) Removing executable..."
	@echo "  $(YELLOW)→ removing$(RESET) $(NAME)";
	@sleep 0.08
	@rm -f $(NAME)

# Rebuild
re: fclean all

# ----------------------------------
# PHONY
# ----------------------------------
.PHONY: all clean fclean re