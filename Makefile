NAME := royal_clash

OS := $(shell uname)

# these can be empty if we are on linux
SFML_INCLUDE = 
SFML_LIBS = 

ifeq ($(OS), Darwin)
# mac includes
SFML_INCLUDE += -I/opt/homebrew/Cellar/sfml/3.0.0_1/include
SFML_LIBS += -L/opt/homebrew/Cellar/sfml/3.0.0_1/lib
endif

# extensions required
EXTENSIONS := -lsfml-graphics -lsfml-window -lsfml-system

INCS_DIR := include
SRCS_DIR := src
OBJS_DIR := obj

# INCS := $(shell find $(SRCS_DIR) -type dir -name 'header')

SRCS := $(shell find $(SRCS_DIR) -type f -name '*.cpp')
OBJS := $(SRCS:$(SRCS_DIR)/%.cpp=$(OJBS_DIR)/%.o)

CC := g++
CFLAGS := -std=c++17 -Wall -Wextra -Werror
CPPFLAGS := $(addprefix -I,$(INCS_DIR))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(SFML_INCLUDE) $(OBJS) $(SFML_LIBS) $(EXTENSIONS) -o $@

all: $(NAME)
	@echo $(CPPFLAGS)
	@echo "FINISHED BUILIDING PROJECT"

clean:
	@rm -rf $(OBJS_DIR)
	@echo "Cleaned"

fclean: clean
	@rm -f $(NAME)
	@echo "Force cleaned"

re: fclean all

.PHONY: all clean fclean re
