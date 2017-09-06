# .name "TBE"
# .comment "Say hi to dady!"

# ld %1, r3
# ld %100, r6

# l2:		sti r1, %:live, %1
# 		# and r1, %0, r1 #set le carry a 1 car le result est 0

# live:	
# 		live %42
# 		add r2, r3, r2 ; incr r2
# 		xor r2, r6, r4 ;if (r4) {carry = 0}
# 		zjmp %:endwhile ;if (carry)
# 		and %0, %0, r8
# 		zjmp %:live 

# endwhile:
# 		#zjmp %:live

# .name "TBE"
# .comment "Say hi to dady!"

# ld %-151005696, r2
# ld %150994944, r1

# beginning:
# 	or	r3, r4, r8
# 	sti r1, %:lfork, %0
# 	add r1, r2, r1
# 	fork %:beginning

# 	and r3, %0, r3
# 	ld %0, r12
# lfork:
# 	zjmp %42

# .name "TBE"
# .comment "Say hi to dady!"

# ld %10752, r2
# ld %150994944, r1

# beginning:
# 	sti r1, %:lfork, %0
# 	add r1, r2, r1
# 	fork %:beginning

# 	and r3, %0, r3
# lfork:
# 	zjmp %42


.name "TBE"
.comment "Say hi to dady!"

ld %1, r99
