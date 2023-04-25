/*

.global _Z4copyPmS_S_

    _Z4copyPmS_S_ : mov x3,
# 0 loop:
    ldr x4,
    [ x1, x3 lsl 2 ]  // lsl
    str x4,
    [ x0, x3 lsl 2 ] add x3, x3, #1 cmp x3,
    x2 bne loopb ret

    int
    main() {
  int a[10], b[10] = {3, 4, 5};

  copy(a, b, 10);
  1.
}  // sorry the format is bad, idk why it is doing this

identify what is in each register



 .global main
main:

0x555550750:	mov x0, #3                      move 3 into x0 x0=3;
0x555550754:	mov x1, #4                      move 4 into x1 x1=4
0x555550758:	stp lr, x0,[sp, #-16]!          writes the link register and x0
                                             into a particular stack
0x55555075C:	bl  f  (0x555550764)            jump foward to 0x555550764
0x555550760:  ldr lr, x0, [sp], #16           reload lr and x0
                                             (what was stored in 0x555550758 )
0x555550764:	ret                             go back (0x555550760),
                                             second time through ret, exits out
                                             of func
0x555550768:	add  x0, x0, x1 // lr=________  will not run because we
                                            have exited func
0x55555076C:	ret	//pc=_________              will not runbecause we have
                                             exited func
*/