ifeq ($(out_dir),)
  out_dir = bin
endif
$(shell mkdir -p ../$(out_dir))
isBST: main.cpp
	@ g++ -g $^ -o ../$(out_dir)/$@
