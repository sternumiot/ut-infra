#v1.0

define sternum_analyse
	@echo "################################# Running Valgrind #################################"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(1) 2>&1 | tee $(2)
	@echo "###################################################################################"
	
	#@echo "################################# Running gcov #################################"
endef