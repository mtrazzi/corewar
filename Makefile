
ifeq ($(OPTIONS_OP), yes)
export OPTIONS_OP="yes"
endif
ifeq ($(COMPARE), yes)
export COMPARE="yes"
endif

all:
	@$(MAKE) -C libs
	@$(MAKE) -C asm asm && /bin/cp ./asm/asm .
	@$(MAKE) -C vm corewar && /bin/cp ./vm/corewar .

clean:
	@$(MAKE) -C libs clean
	@$(MAKE) -C asm clean
	@$(MAKE) -C vm clean

fclean:
	@$(MAKE) -C libs fclean
	@$(MAKE) -C asm fclean
	@$(MAKE) -C vm fclean

re:
	@$(MAKE) -C libs re
	@$(MAKE) -C asm re
	@$(MAKE) -C vm re

.PHONY: all fclean clean re
