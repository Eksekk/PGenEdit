format PE64 console
entry start

include 'win64a.inc'
include 'fasm.ash'

section '.data' data readable writeable

 _source db 0Dh,0Ah
	 db ' org 100h',0Dh,0Ah
	 db 0Dh,0Ah
	 db ' mov ah,09h ',' ; write',0Dh,0Ah
	 db ' mov dx,text',0Dh,0Ah
	 db ' int 21h',0Dh,0Ah
	 db ' int 20h',0Dh,0Ah
	 db 0Dh,0Ah
	 db ' text db "Hello!",24h',0Dh,0Ah
	 db 0

 digits db '0123456789ABCDEF'

 bytes_count dd ?

 buffer rb 10000h

 fasm_memory:
   fasm_state FASM_STATE
   rb 800000h-($-fasm_memory)		; reserve total 8 MB for assembler

section '.text' code readable executable

start:
	sub	rsp,8

	invoke	fasm_Assemble,_source,fasm_memory,800000h,100,NULL
	cmp	eax,FASM_OK
	je	show_output

	invoke	ExitProcess,1

show_output:
	mov	esi,[fasm_state.output_data]
	mov	ecx,[fasm_state.output_length]
	lea	rbx,[digits]
	lea	rdi,[buffer]
	xor	edx,edx
	jecxz	output_ok
      output_to_hex:
	test	dl,15
	jz	@f
	mov	al,20h
	stosb
      @@:
	mov	al,[esi+edx]
	shr	al,4
	xlatb
	stosb
	mov	al,[esi+edx]
	and	al,0Fh
	xlatb
	stosb
	inc	edx
	test	dl,15
	jnz	@f
	mov	ax,0D0Ah
	stosw
      @@:
	loop	output_to_hex
      output_ok:
	invoke	GetStdHandle,STD_OUTPUT_HANDLE
	lea	rcx,[buffer]
	sub	rdi,rcx
	invoke	WriteFile,rax,buffer,rdi,bytes_count,0

	invoke	ExitProcess,0

section '.idata' import data readable writeable

  library kernel32,'KERNEL32.DLL',\
	  fasm,'FASMX64.DLL'

  include 'api/kernel32.inc'

  import fasm,\
	 fasm_GetVersion,'fasm_GetVersion',\
	 fasm_Assemble,'fasm_Assemble',\
	 fasm_AssembleFile,'fasm_AssembleFile'