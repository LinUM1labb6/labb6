# Makefile for electrotest
#
# Mikael Thoresson
# Put object files in variable objs
objs = main.o
libs = component power resistance
libs_c = component.c power.c resistance.c
libs_o = component.o power.o resistance.o
libs_so = libcomponent.so libpower.so libresistance.so
libs_l = -lcomponent -lpower -lresistance
# Define 'functions' in Makefil
.PHONY: all
.PHONY: install
.PHONY: uninstall
.PHONY: clean
.PHONY: clean_objects
.PHONY: lib
# Define how to update object files using implicit rules
#main.o: main.h
component.o: component.h
power.o: power.h
resistance.o: resistance.h
# Build shared library and electrotest
all: electrotest
electrotest: lib
    # cc -o electrotest $(objs) -L. -l$(static_libs)
    cc -L./lib -Wl,-rpath=./lib -Wall -o electrotest main.c $(libs_l)
# Build library
lib:
    cc -c -Wall -Werror -fpic component.c
    cc -shared -o ./lib/libcomponent.so component.o

    cc -c -Wall -Werror -fpic power.c
    cc -shared -o ./lib/libpower.so power.o

    cc -c -Wall -Werror -fpic resistance.c
    cc -shared -o ./lib/libresistance.so resistance.o

# Install @ /usr/bin
install:
    echo "install electrotest @ /usr/bin"

# Uninstall @ /usr/bin
uninstall:
    echo "uninstall electrotest @/usr/bin"
# Remove all object files and electrotest
clean:
    rm *.o electrotest

# Remove all object files
clean_objects:
    rm *.o
