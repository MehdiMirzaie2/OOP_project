NAME = royal_clash

OS := $(shell uname -s)

# SFML paths (can be empty on Linux)
SFML_INCLUDE = 
SFML_LIBS = 

ifeq ($(OS), Darwin)
SFML_INCLUDE += -I/opt/homebrew/Cellar/sfml/3.0.0_1/include
SFML_LIBS += -L/opt/homebrew/Cellar/sfml/3.0.0_1/lib
endif

EXTENSIONS := -lsfml-graphics -lsfml-window -lsfml-system

INCS_DIR := include
SRCS_DIR := src
OBJS_DIR := obj

SRCS := $(shell find $(SRCS_DIR) -type f -name '*.cpp')
OBJS := $(SRCS:$(SRCS_DIR)/%.cpp=$(OBJS_DIR)/%.o)

CC := g++
CFLAGS := -std=c++17 -Wall -Wextra -Werror
CPPFLAGS := $(addprefix -I,$(INCS_DIR))

all: $(NAME)
	@echo "FINISHED BUILDING PROJECT"

# Rule to compile source files into object files
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(SFML_INCLUDE) -c $< -o $@

# Rule to link object files into final binary
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(SFML_INCLUDE) $(OBJS) $(SFML_LIBS) $(EXTENSIONS) -o $@

clean:
	@rm -rf $(OBJS_DIR)
	@echo "Cleaned"

fclean: clean
	@rm -f $(NAME)
	@echo "Force cleaned"

re: fclean all

.PHONY: all clean fclean re


# NAME = royal_clash

# OS := $(shell uname)

# # these can be empty if we are on linux
# SFML_INCLUDE = 
# SFML_LIBS = 

# ifeq ($(OS), Darwin)
# # mac includes
# SFML_INCLUDE += -I/opt/homebrew/Cellar/sfml/3.0.0_1/include
# SFML_LIBS += -L/opt/homebrew/Cellar/sfml/3.0.0_1/lib
# endif

# # extensions required
# EXTENSIONS := -lsfml-graphics -lsfml-window -lsfml-system

# INCS_DIR := include
# SRCS_DIR := src
# OBJS_DIR := obj
# DIR_DUP  := mkdir -p $(@D)


# # INCS := $(shell find $(SRCS_DIR) -type dir -name 'header')

# SRCS := $(shell find $(SRCS_DIR) -type f -name '*.cpp')
# OBJS := $(SRCS:$(SRCS_DIR)/%.cpp=$(OBJS_DIR)/%.o)

# CC := g++
# CFLAGS := -std=c++17 -Wall -Wextra -Werror
# CPPFLAGS := $(addprefix -I,$(INCS_DIR))

# all: $(NAME)
# 	# @echo $(CPPFLAGS)
# 	@echo "FINISHED BUILIDING PROJECT"

# $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
# 	@echo "Hello world"
# 	@mkdir -p $(dir $@)
# 	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# $(NAME): $(OBJS)
# 	@echo "Hello world"
# 	@$(CC) $(CFLAGS) $(CPPFLAGS) $(SFML_INCLUDE) $(OBJS) $(SFML_LIBS) $(EXTENSIONS) -o $@

# $(OBJS): $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
# 	@echo "hello whats up"
# 	$(DIR_DUP)
# 	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
# 	@$(call print_obj,$@)

# clean:
# 	@rm -rf $(OBJS_DIR)
# 	@echo "Cleaned"

# fclean: clean
# 	@rm -f $(NAME)
# 	@echo "Force cleaned"

# re: fclean all

# .PHONY: all clean fclean re
