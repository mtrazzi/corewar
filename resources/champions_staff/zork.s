.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
		and r1, %0, r1 #set le carry a 1 car le result est 0

live:	live %1
		zjmp %:live
