.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
		and r1, %0, r1
	st r1, 564545465456456546454564454354354435435435453735425452442725727

live:	live %1
		zjmp %:live
