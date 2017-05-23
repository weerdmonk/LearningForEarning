ifeq ($(out_dir),)
  out_dir = bin
endif
$(shell mkdir -p ../$(out_dir))
threadedBinTree: main.cpp
	@ g++ -g $^ -o ../$(out_dir)/$@
