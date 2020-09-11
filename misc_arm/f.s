f(int):
        str     fp, [sp, #-4]!
        add     fp, sp, #0
        sub     sp, sp, #20
        str     r0, [fp, #-16]
        mov     r3, #1
        str     r3, [fp, #-8]
        mov     r3, #1
        str     r3, [fp, #-12]
.L3:
        ldr     r2, [fp, #-12]
        ldr     r3, [fp, #-16]
        cmp     r2, r3
        bge     .L2
        ldr     r2, [fp, #-12]
        ldr     r3, [fp, #-8]
        add     r3, r2, r3
        str     r3, [fp, #-12]
        ldr     r3, [fp, #-8]
        add     r3, r3, #1
        str     r3, [fp, #-8]
        b       .L3
.L2:
        ldr     r3, [fp, #-8]
        mov     r0, r3
        add     sp, fp, #0
        ldr     fp, [sp], #4
        bx      lr
