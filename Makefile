CC=gcc
CFLAGS=-c -g -Wall
LDFLAGS=-lm -lX11 -lxkbfile -rdynamic `pkg-config --cflags --libs gtk+-3.0`
SOURCES=station.c functions.c station_widget_functions.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=your_executable

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
    $(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
    $(CC) $(CFLAGS) $< -o $@

# Clean up rule
.PHONY: clean
clean:
    rm -f $(EXECUTABLE) $(OBJS)
