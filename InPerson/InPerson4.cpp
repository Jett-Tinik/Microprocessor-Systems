/* Review shittttt
uint32_t b = 7/2; // 3
double x = 1 / 0 // program terminates (hardware trap)
double g = 1.0 / 0.0; // infinity
double h = 0.0 / 0.0; // NaN
uint32_t h = 5 % 3 + 6 % 2 = 2 + 0 = 2
*/

/* Arm shitttttt
int f(int a) --- w0
int f (uint_t b) ---- x0

sub w1, w1, 1 // n-1
ldr x2, [x0], 8 // x2 = mem [x0], x0 = x0 + 8
sub w1, w1, 1
cmp w1, 0
bne 1b
*/
