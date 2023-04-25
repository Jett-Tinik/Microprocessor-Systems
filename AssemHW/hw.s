
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