# =========================
# Project hotrace
# =========================
NAME            = hotrace
CC              = cc
CFLAGS          = -Wall -Werror -Wextra -MMD -MP
DEBUG_FLAGS     = -g -DVERBOSE=1


# =========================
# Folders
# =========================
SRC_DIR         = src
OBJ_DIR         = obj

# =========================
# Sources
# =========================

SRCS = \
	main.c \
	hash_key.c\
	hashmap.c \
	arena.c


	
# =========================
# Objects / Deps
# =========================
OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

# =========================
# Rules
# =========================
all: $(NAME)

run: all
	./hotrace

verbose: CFLAGS += $(DEBUG_FLAGS)
verbose: re

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c inc/hotrace.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all verbose clean fclean re
