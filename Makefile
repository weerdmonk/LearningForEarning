# Top-level Makefile for Learning for Earning
# ===========================================
#
# Add each problem as target. 'all' will build everything
# Output to 'bin' directory inside sub-dir named as target

SUBDIRS = xorList threadedBinTree queueUsingStacks findLCA findLCABST isBST treeListRecursion treeLvlOrder mirrorTree countLeaves shuntYard

out_dir = bin

#get_debug_targets = $(shell grep -Po "(?<=^\.PHONY:\s)([]debug_[a-zA-Z]+)" $(dir)/Makefile)
#debug_targets = $(foreach dir,$(SUBDIRS),$(get_debug_targets))

debug_targets = $(addprefix debug_, $(SUBDIRS))

all: $(SUBDIRS)
	@echo Building all targets ...

$(SUBDIRS):
	@echo Building $@ ...
	@mkdir -p bin
	@export out_dir
	@($(MAKE) -C $@)

debug: $(debug_targets)

$(debug_targets): CXXFLAGS+=-g
$(debug_targets): target_name = $(subst debug_, ,$@)
$(debug_targets): out_dir = debug
export
$(debug_targets):
	@echo Building $@ ...
	@mkdir -p debug
	@($(MAKE) -C $(target_name))

clean:
	@echo Cleaning all targets ...
	@rm -rf bin
	@rm -rf debug 

.PHONY: all $(SUBDIRS) debug $(debug_targets)
