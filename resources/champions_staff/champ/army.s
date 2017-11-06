.name "je_pete_un_cable"
.comment "AAAAAAAHHHHHHHHH!!!"

		sti r1, %:train_army, %1
		ld %1, r2
defense:
		st  r2, -220
		st	r1, -221
		ld %57672192, r3
		ld %3691212801, r4
		ld %14353264, r5
		ld %50387459, r6
		ld %1879310553, r7
		ld %57672960, r8
		ld %3624103942, r9
		ld %14091120, r10
		ld %117495299, r11
		ld %1879572693, r12
		ld %57673984, r13
		ld %3556995082, r14
		ld %117495299, r16
train_army:	live %1
			fork %:attack
			and r1, r15, r15
			zjmp %:train_army

attack:		st  r2, 220
			st	r1, 219
			st	r3, 218
			st	r4, 217
			st r5, 216
			st r6, 215
			st r7, 214
			st r8, 213
			st r9, 212
			st r10, 211
			st r11, 210
			st r12, 209
			st r13, 208
			st r14, 207
			st r16, 206
			ld %1879572693, r16
			st r16, 196
			ld %57673984, r16
			st r16, 186
			ld %3556995082, r16
			st r16, 176
