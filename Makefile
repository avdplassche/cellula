# --- 1. CONFIGURATION VARIABLES ---
NAME     := cellula
CXX      := clang++

# Directory Paths
SRCDIR   := srcs
DATADIR  := data
INCDIR   := includes
BUILDDIR := build

# --- ASAN TOGGLE ---
USE_ASAN := 0 
ifeq ($(USE_ASAN), 1)
    ASAN_FLAGS := -fsanitize=address
else
    ASAN_FLAGS :=
endif

STD_FLAGS := -Wall -Wextra -Werror -std=c++17 -MMD -MP -g -Wno-unused-result
INC_PATHS := -I$(INCDIR)
CXXFLAGS  := $(STD_FLAGS) $(INC_PATHS) $(ASAN_FLAGS) -DImTextureID=void*
LD_FLAGS  := $(ASAN_FLAGS) -lGL -lSDL3 -lSDL3_ttf -lSDL3_image -lyaml-cpp


# --- 2. FILE DEFINITIONS ---

APP_SOURCES := $(shell find $(SRCDIR) $(DATADIR) -name "*.cpp")

OBJECTS     := $(APP_SOURCES:%=$(BUILDDIR)/%.o)
DEPENDS     := $(OBJECTS:.o=.d)

GREEN := \033[0;32m
RESET := \033[0m

# --- 3. BUILD RULES ---

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "--- Linking executable: $@ ---"
	$(CXX) $(OBJECTS) $(LD_FLAGS) -o $(NAME)
	@printf "$(GREEN)Build Successful: ./$(NAME)$(RESET)\n"

$(BUILDDIR)/%.o: %
	@mkdir -p $(dir $@)
	@echo "Compiling: $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILDDIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

-include $(DEPENDS)
