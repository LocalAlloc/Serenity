BITS 16
ORG 0x7C00

main:
    ;seed random number generator
    xor ax, ax
    int 1Ah
    xor cx, dx
    mov [rngstate], cx
    ;prepare a pointer to screen memory
    mov ax, 0xA000
    mov es, ax
    ;print intro message
    mov ax, 02h
    int 10h
    mov si, message
    print:
    lodsb
    or al, al
    jz waitkp
    mov ah, 0eh
    int 10h
    jmp print
    waitkp:
    xor ax, ax
    int 16h

    ;set graphics mode 13h
    mov ax, 13h
    int 10h
    ;colour 16 = red
    mov ax, 1010h
    mov bx, 16
    mov cx, 0
    mov dx, 0x3f3f
    int 10h
    ;prepare registers for changing the palette [DH = R, CH = G, CL = B, MAX 63]
    palPrep:
        mov ax, 1010h
        mov bx, 0
        mov cx, 0
        mov dh, 0
    colcycleIncrement:
        ;set palette
        call WaitF
        int 10h
        ;set red (col16)
        push cx
        xor cx, cx
        mov bx, 16
        xchg dh, dl
        cmp byte [redswap], 0
        jz .col16swapped
        inc dh
        cmp dh, 63
        jge .col16swap
        jmp .postcol16dec
        .col16swapped:
        dec dh
        or dh, dh
        jnz .postcol16dec
        .col16swap:
        not byte [redswap]

        .postcol16dec:
        int 10h
        xchg dh, dl
        mov bx, 0
        pop cx

        ;decide palette
        cmp cl, 63
        jge .incG
        inc cl
        jmp colcycleIncrement
        .incG:
            cmp ch, 63
            jge .incR
            inc ch
            jmp colcycleIncrement
            .incR:
                cmp dh, 63
                jge colcycleDecrement
                inc dh
                jmp colcycleIncrement

    colcycleDecrement:
        call WaitF
        int 10h
        ;set red (col16)
        push cx
        xor cx, cx
        mov bx, 16
        xchg dh, dl
        cmp byte [redswap], 0
        jz .col16swapped
        inc dh
        cmp dh, 63
        jge .col16swap
        jmp .postcol16dec
        .col16swapped:
        dec dh
        or dh, dh
        jnz .postcol16dec
        .col16swap:
        not byte [redswap]

        .postcol16dec:
        int 10h
        xchg dh, dl
        mov bx, 0
        pop cx

        or cl, cl
        jz .decG
        dec cl
        jmp colcycleDecrement
        .decG:
            or ch, ch
            jz .decR
            dec ch
            jmp colcycleDecrement
            .decR:
                or dh, dh
                jz drawcycle
                dec dh
                jmp colcycleDecrement

    drawcycle:
        jmp palPrep  ; Skip the draw loop

    WaitF:
        pusha
        mov cx, 0
        mov dx, 0x0200
        mov ah, 86h
        int 15h
        popa
        ret

    rngstate dw 0
    redswap db 0
    message db "Eternal darkness approaches",0xA,0xD,"Cycles of despair repeat",0xA,0xD,"Empires crumble into dust",0xA,0xD,"The moment to seize power is nigh",0xA,0xD,"The world is ours to command",0xA,0xA,0xD,"Unleash the abyss within",0xA,0xD,0xA,176,177,178,"Awaken the shadows, -.Win32.Serenity By LocalAlloc-. Press Any Key",178,177,176,0

times 510-($-$$) db 0
dw 0xAA55 ; Signature
