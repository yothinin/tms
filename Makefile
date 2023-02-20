CC=gcc
CFLAGS=-g -Wall
LIBS=`pkg-config --libs --cflags gtk+-3.0` -lmariadbclient -I/usr/include/glib-2.0 -lm -lX11 -lxkbfile -rdynamic
STATION_SOURCES=station.c functions.c station_mysql_fnct.c station_widget_fnct.c
ROUTE_SOURCES=route.c functions.c route_mysql_fnct.c route_widget_fnct.c
STATION_OBJECTS=$(STATION_SOURCES:.c=.o)
ROUTE_OBJECTS=$(ROUTE_SOURCES:.c=.o)
STATION_EXECUTABLE=station
ROUTE_EXECUTABLE=route

.PHONY: all station route clean

all: $(STATION_EXECUTABLE) $(ROUTE_EXECUTABLE)

station: $(STATION_EXECUTABLE)

route: $(ROUTE_EXECUTABLE)

$(STATION_EXECUTABLE): $(STATION_OBJECTS)
	$(CC) $(STATION_OBJECTS) $(LIBS) -o $(STATION_EXECUTABLE)

$(ROUTE_EXECUTABLE): $(ROUTE_OBJECTS)
	$(CC) $(ROUTE_OBJECTS) $(LIBS) -o $(ROUTE_EXECUTABLE)

.c.o:
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

clean:
	rm -f $(STATION_OBJECTS) $(ROUTE_OBJECTS) $(STATION_EXECUTABLE) $(ROUTE_EXECUTABLE)
