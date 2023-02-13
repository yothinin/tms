# tms
compile

gcc -g -Wall -std=gnu18 -c "%f" functions.c station_widget_fnct.c `pkg-config --cflags --libs gtk+-3.0` -lm -lX11 -lxkbfile -rdynamic

gcc -g -Wall -std=gnu18 -o "%e" "%f"  functions.c station_widget_fnct.c `pkg-config --cflags --libs gtk+-3.0` -lm -lX11 -lxkbfile -rdynamic
