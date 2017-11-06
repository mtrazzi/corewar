
ifeq ($(OPTIONS_OP), yes)
export OPTIONS_OP="yes"
endif
ifeq ($(COMPARE), yes)
export COMPARE="yes"
endif

all:
	@$(MAKE) -C libs
	@$(MAKE) -C compiler asm
	@$(MAKE) -C vm corewar
	/bin/cp compiler/asm .
	/bin/cp vm/corewar .

clean:
	@$(MAKE) -C libs clean
	@$(MAKE) -C compiler clean
	@$(MAKE) -C vm clean

fclean:
	@/bin/rm -f asm
	@/bin/rm -f corewar
	@$(MAKE) -C libs fclean
	@$(MAKE) -C compiler fclean
	@$(MAKE) -C vm fclean

re:
	@/bin/rm -f asm
	@/bin/rm -f corewar
	@$(MAKE) -C libs re
	@$(MAKE) -C compiler re
	@$(MAKE) -C vm re
	/bin/cp compiler/asm .
	/bin/cp vm/corewar .

.PHONY: all fclean clean re
