; ----------------------------
; Lib to create the eden
; ----------------------------


; ----------------------------------------------------------
;	buildEden (int VRAMAddr, char* RAMAddr, unsigned int blockLength)
;
_buildEden::
	ld		hl,		#2
	add		hl,		sp

	ld		a,		(hl)
	out		(#0x99),a
	inc		hl
	ld		a,		(hl)
;	and		#0x3f
	or		#0x40
	out		(#0x99),a

	inc		hl
	ld		e,		(hl)
	inc		hl
	ld		d,		(hl)

	inc		hl
	inc		hl
	ld		b,		(hl)
;	ld		c,		#0x98
	push	bc
	dec		hl
	ld		b,		(hl)
	ld		l,		e
	ld      h,		d
	
_newChar:
	ld		a,		(hl)
	inc		hl
	cp		#0xaf
	jr nz,	outToVRAM
	ld		a,		r
	rlca
	ld		r,		a
	and		#0x0f ;16 tiles
	add		#0xa8 ;TILE_GRASS

outToVRAM:
	out		(#0x98), a
	djnz	_newChar

	pop		bc
	xor		a		; = ld a, 0
	cp		b
	ret		z

	dec		b
	push	bc
	ld		b,		#255
	jr		_newChar