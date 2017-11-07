.name "je suis un bonus"
.comment "lol"

l2:		ld %20, r15
		st r15, -100
		st r15, -100
		mul r1, r1, r1
		injury %42
		injury %42
		injury %42
		injury %42
		injury %42
		injury %42
		sti r1, %:live, %1
		sti r1, %:live2, %1
		sti r1, %:live3, %1
		sti r1, %:live3, %6
		sti r1, %:live3, %11
		sti r1, %:live3, %16
		sti r1, %:live3, %21
		sti r1, %:live3, %26
		sti r1, %:live3, %31
		sti r1, %:live3, %36
		sti r1, %:live3, %41
		sti r1, %:live3, %46
		sti r1, %:live3, %51
		sti r1, %:live3, %56
		sti r1, %:live3, %61
		sti r1, %:live3, %66
		sti r1, %:live3, %71
		sti r1, %:live3, %76
		sti r1, %:live3, %81
		sti r1, %:live3, %86
		sti r1, %:live3, %91
		sti r1, %:live3, %96
		sti r1, %:live3, %101
		sti r1, %:live3, %106
		sti r1, %:live3, %111
		sti r1, %:live3, %116
		nand r1, r1, r1
		fork %:live

live:	live %1
		fork %:live2
		copy r1, r2, r3
		mul r2, r2, r2
		jmp %:live

live2:	live %1
		fork %:live3
		jmp %:live2

live3:
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		zjmp %:live3
