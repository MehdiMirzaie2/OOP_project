NAME := royal_clash

OS := $(shell uname)
CC := g++
CFLAGS := -std=c++17 -Wall -Wextra -Werror -g
INCS_DIR := include
CPPFLAGS := -I$(INCS_DIR)

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

SRCS := $(shell find $(SRCS_DIR) -type f -name '*.cpp')
OBJS := $(SRCS:$(SRCS_DIR)/%.cpp=$(OBJS_DIR)/%.o)
TEST_DEPENDENCIES := test.o Game.o map.o User.o Entity.o Unit.o Director.o Deck.o UnitBuilder.o BattleWindow.o StatsWindow.o MainMenu.o Attack.o Elixir.o Drawable.o 
TEST_DEPENDENCIES_ACTUAL = $(addprefix $(OBJS_DIR)/, $(TEST_DEPENDENCIES))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $< -> $@"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SFML_INCLUDE) $(OBJS) $(SFML_LIBS) $(EXTENSIONS) -o $@

test: ${TEST_DEPENDENCIES_ACTUAL}
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(SFML_INCLUDE) $^ $(SFML_LIBS) $(EXTENSIONS) -o $@

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

.PHONY: all test clean fclean re 
