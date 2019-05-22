CPP=g++
CPPSRC=main.cpp filemanager.cpp cliente.cpp
HSRC=cliente.h filemanager.h

all: $(CPPSRC) $(HSRC)
	$(CPP) -o ex $(CPPSRC)
