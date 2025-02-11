CXX := g++
CFLAGS := -std=c++17 -Wall -Werror -Wextra -pedantic -O2 -I./include -I./tests

TEST := test
TARGET := main
OBJDIR := obj

OBJECTS := $(OBJDIR)/bit_writer.o $(OBJDIR)/bor.o $(OBJDIR)/compressor.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CFLAGS) -o $@ $^ src/main.cpp

$(TEST): $(OBJECTS) tests/*.hpp
	$(CXX) $(CFLAGS) -o $@ $^ tests/test.cpp -lgtest_main -lgtest -lpthread

$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	$(CXX) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)
	rm -f $(TARGET)

.PHONY: clean
