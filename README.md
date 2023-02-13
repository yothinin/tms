# tms
compile

gcc -g -Wall -std=gnu18 -c "%f" functions.c station_widget_fnct.c mysql_fnct.c `pkg-config --cflags --libs gtk+-3.0` -lm -lX11 -lxkbfile -rdynamic  
gcc -g -Wall -std=gnu18 -o "%e" "%f"  functions.c station_widget_fnct.c mysql_fnct.c `pkg-config --cflags --libs gtk+-3.0` -lm -lX11 -lxkbfile -rdynamic  


MySQL use .mysql_options file to store about client for connect to db  

in file: .mysql_options

[client]  
database = *** db name ***  
user = *** user name ***  
password = *** your password ***  
