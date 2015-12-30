# Makefile for Learning for Earning
# =================================
#
# Add each problem as target. 'all' will build everything
# Output to 'bin' directory inside sub-dir named as target

TARGETS= xorList threadedBinTree queueUsingStacks findLCA findLCABST isBST treeListRecursion treeLvlOrder

#include xorList/Makefile

all:
	@echo Building all targets ...
	@mkdir -p bin
	@for dir in $(TARGETS); do \
		($(MAKE) -C $$dir); \
	done

clean:
	@echo Cleaning all targets ...
	@rm -rf bin
