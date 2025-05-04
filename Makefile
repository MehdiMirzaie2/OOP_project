NAME := royal_clash
CC := g++
CFLAGS := -std=c++17 -Wall -Wextra -Werror

OS := $(shell uname)

ifeq ($(OS), Darwin)
# mac includes
SFML_INCLUDE += -I/opt/homebrew/Cellar/sfml/3.0.0_1/include
SFML_LIBS += -L/opt/homebrew/Cellar/sfml/3.0.0_1/lib

# need to know where the libs are on your computers, might even work if i don't define it for linux.
else
SFML_INCLUDE += 
SFML_LIBS += 
endif

# extensions required
EXTENSIONS := -lsfml-graphics -lsfml-window -lsfml-system

SRCS_DIR := src
OBJS_DIR := obj

SRCS := $(shell find $(SRCS_DIR) -type f -name '*.cpp')
OBJS := $(SRCS:$(SRCS_DIR)/%.cpp=$(OBJS_DIR)/%.o)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(SFML_INCLUDE) $(OBJS) $(SFML_LIBS) $(EXTENSIONS) -o $@

all: $(NAME)
	@echo "FINISHED BUILIDING PROJECT"

clean:
	@rm -rf $(OBJS_DIR)
	@echo "Cleaned"

fclean: clean
	@rm -f $(NAME)
	@echo "Force cleaned"

re: fclean all

.PHONY: all clean fclean re





# g++ -std=c++17 main.cpp -I/opt/homebrew/Cellar/sfml/3.0.0_1/include -o program -L/opt/homebrew/Cellar/sfml/3.0.0_1/lib -lsfml-graphics -lsfml-window -lsfml-system 
