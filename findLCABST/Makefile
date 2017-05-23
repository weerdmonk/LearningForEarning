ifeq ($(out_dir),)
  out_dir = bin
endif
$(shell mkdir -p ../$(out_dir))
findLCABST: main.cpp
	@ g++ -g $^ -o ../$(out_dir)/$@
