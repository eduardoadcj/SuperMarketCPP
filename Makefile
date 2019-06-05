CPP=g++
CPPSRC=main.cpp filemanager.cpp keymanager.cpp cliente.cpp produto.cpp venda.cpp
HSRC=cliente.h filemanager.h keymanager.h produto.h venda.h

all: $(CPPSRC) $(HSRC)
	$(CPP) -o ex $(CPPSRC)
