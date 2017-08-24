.name "my champ"
.comment "I'm michael's champ"

live:	live %4242422
		fork %:live	
		sti r1 ,%:live, %1
		zjmp %:live
