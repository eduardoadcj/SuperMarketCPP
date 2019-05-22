CPP=g++
CPPSRC=main.cpp filemanager.cpp keymanager.cpp cliente.cpp
HSRC=cliente.h filemanager.h keymanager.h

all: $(CPPSRC) $(HSRC)
	$(CPP) -o ex $(CPPSRC)
