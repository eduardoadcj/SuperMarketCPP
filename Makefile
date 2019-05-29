CPP=g++
CPPSRC=main.cpp filemanager.cpp keymanager.cpp cliente.cpp produto.cpp
HSRC=cliente.h filemanager.h keymanager.h produto.h

all: $(CPPSRC) $(HSRC)
	$(CPP) -o ex $(CPPSRC)
