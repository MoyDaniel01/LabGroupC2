

; Function prototype: stopWatchIncrement(displayState_t *pDisplayState);
; This function increment the number shown on the stop watch display. It should be called once every one centisecond.
					.text
					.global stopWatchIncrement	; make this symbol global
					.global stopWatchReset
					.global stopWatchMax
					.global stopWatchMaxFt

stopWatchIncrement	.asmfunc

					; Update c2, continue to c1 if c2 is reset to zero
					LDRB		r1, [r0, #0]			; load c2 to r1, note c2's offset is zero which can be omitted
					ADD		r1, #1				; increment c2 by one
					STRB		r1, [r0, #0]			; store back c2
					CMP		r1, #10				; compare c2 and 10
					BNE		return				; if c2 != 10, jump to return
					MOV		r1, #0				; reset c2 to zero
					STRB		r1, [r0, #0]			; store back again

					LDRB		r2, [r0, #1]			; load c2 to r1, note c2's offset is zero which can be omitted
					ADD		r2, #1				; increment c2 by one
					STRB		r2, [r0, #1]			; store back c2
					CMP		r2, #6				; compare c2 and 10
					BNE		return				; if c2 != 10, jump to return
					MOV		r2, #0				; reset c2 to zero
					STRB		r2, [r0, #1]			; store back again

					LDRB		r3, [r0, #2]			; load c2 to r1, note c2's offset is zero which can be omitted
					ADD		r3, #1				; increment c2 by one
					STRB		r3, [r0, #2]			; store back c2
					CMP		r3, #10				; compare c2 and 10
					BNE		return				; if c2 != 10, jump to return
					MOV		r3, #0				; reset c2 to zero
					STRB		r3, [r0, #2]			; store back again

					LDRB		r4, [r0, #3]			; load c2 to r1, note c2's offset is zero which can be omitted
					ADD		r4, #1				; increment c2 by one
					STRB		r4, [r0, #3]			; store back c2
					CMP		r4, #6				; compare c2 and 10
					BNE		return				; if c2 != 10, jump to return
					MOV		r4, #0				; reset c2 to zero
					STRB		r4, [r0, #3]			; store back again


return				BX		LR					; return
					.endasmfunc

stopWatchReset .asmfunc

					MOV		r1, #0
					STRB	r1, [r0, #0]
					MOV		r2, #0
					STRB	r2, [r0, #1]
					MOV		r3, #0
					STRB	r3, [r0, #2]
					MOV		r4, #0
					STRB	r4, [r0, #3]

                   .endasmfunc

stopWatchMax .asmfunc

					MOV		r1, #9
					STRB	r1, [r0, #0]
					MOV		r2, #9
					STRB	r2, [r0, #1]
					MOV		r3, #9
					STRB	r3, [r0, #2]
					MOV		r4, #9
					STRB	r4, [r0, #3]

                   .endasmfunc

stopWatchMaxFt .asmfunc

					MOV		r1, #2
					STRB	r1, [r0, #0]
					MOV		r2, #1
					STRB	r2, [r0, #1]
					MOV		r3, #9
					STRB	r3, [r0, #2]
					MOV		r4, #9
					STRB	r4, [r0, #3]

                   .endasmfunc
                   .end

