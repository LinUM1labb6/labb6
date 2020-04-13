# Makefile for electrotest
#
# 
# Put object files in variable objs
objs = main.o
libs = component power resistance
libs_c = component.c power.c resistance.c
libs_o = component.o power.o resistance.o
libs_so = libcomponent.so libresistance.so libpower.so
libs_l = -lcomponent -lpower -lresistance
# Define 'functions' in Makefil
.PHONY: all
.PHONY: install
.PHONY: uninstall
.PHONY: clean
.PHONY: clean_objects
.PHONY: lib
# Define how to update object files using implicit rules
component.o:	component.c
power.o:	power.c
resistance.o:	resistance.c
# Build shared library and electrotest
all: electrotest
electrotest: lib
	cc -L../lib -Wl,-rpath=../lib -Wall -o electrotest main.c $(libs_l)
# Build library
lib:
	cc -c -Wall -Werror -fpic component.c
	cc -shared -o ../lib/libcomponent.so component.o
	
	cc -c -Wall -Werror -fpic power.c
	cc -shared -o ../lib/libpower.so power.o -lm
	
	cc -c -Wall -Werror -fpic resistance.c 
	cc -shared -o ../lib/libresistance.so resistance.o -lm

# Install @ /usr/bin
install:
	sudo cc -c -Wall -Werror -fpic component.c
	sudo cc -shared -o /usr/lib/libcomponent.so component.o
	
	sudo cc -c -Wall -Werror -fpic power.c
	sudo cc -shared -o /usr/lib/libpower.so power.o -lm
	
	sudo cc -c -Wall -Werror -fpic resistance.c 
	sudo cc -shared -o /usr/lib/libresistance.so resistance.o -lm
	
	sudo cc -L/usr/lib -Wl,-rpath=/usr/lib -Wall -o /usr/bin/electrotest main.c $(libs_l)

# Uninstall @ /usr/bin
uninstall:
	echo "uninstall electrotest @/usr/bin"
# Remove all object files and electrotest
clean:
	rm *.o electrotest

# Remove all object files
clean_objects:
	rm *.o
