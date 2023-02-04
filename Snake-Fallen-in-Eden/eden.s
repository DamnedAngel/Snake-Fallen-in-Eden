; ----------------------------
; Lib to create the eden
; ----------------------------

; ----------------------------------------------------------
;	buildEden (int VRAMAddr, char* RAMAddr, unsigned int blockLength)
;
_buildEden::
	ld		hl, #2
	add		hl, sp

	ld		a, (hl)
	out		(#0x99), a
	inc		hl
	ld		a, (hl)
	and		#0x3f
	or		#0x40
	out		(#0x99), a

	inc		hl
	ld		e, (hl)
	inc		hl
	ld		d, (hl)

	inc		hl
	ld		b, (hl)
	ld		a, b
	inc		hl
	or		a               ; cp 0 ==> tests if lsb is zero
	ld		c, (hl)
	ld		l, e
	ld		h, d
	jr      z, _newChar     ; if lsb is not zero
	inc     c               ;   adjusts (increment) msb

_newChar:
	ld	    a,		(hl)
	inc     hl
	cp      #0xaf
	jr nz,  outToVRAM
	ld      a, r
	rlca
	xor     b               ; enhanced randomness from the version in the video
	ld      r, a
	and     #0x0f           ;16 tiles
	add     #0xa8           ;TILE_GRASS
	
outToVRAM:                  ; b (lsb) controls inner loop; c (msb) controls outer loop
	out		(#0x98), a
	djnz    _newChar

	dec     c
	jr      nz, _newChar
	ret
