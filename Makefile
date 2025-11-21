CXX := g++
TARGET := build/main

SRC := $(wildcard src/*.cpp src/*/*.cpp)
OBJ := $(patsubst src/%.cpp, build/src/%.o, $(SRC))

ASSETS := $(wildcard src/assets/*)
ASSET_HEADERS := $(patsubst src/assets/%, build/assets/%.h, $(ASSETS))

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)
EXT_LIBS := -lSDL2_image -lSDL2_mixer -lSDL2_ttf

all: $(TARGET)

$(TARGET): $(ASSET_HEADERS) $(OBJ)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJ) -o $(TARGET) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(EXT_LIBS)

build/src/%.o: src/%.cpp $(ASSET_HEADERS)
	@mkdir -p $(dir $@)
	$(CXX) $(SDL_CFLAGS) -Isrc -Ibuild -Ibuild/assets -c $< -o $@

build/assets/%.h: src/assets/%
	@mkdir -p $(dir $@)
	name=$$(basename $< | tr . _); \
	xxd -i -n $$name $< > $@


clean:
	rm -rf build

.PHONY: all clean
