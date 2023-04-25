/*
uint64_t focus = 0
for (j = 0 to h-1)

HOW TO TELL IF A REGISTER IS ODD OR EVEN?
suppose x0 = some number
10101010100110110 rightmost bit tells odd or even (this even)


bittest
  and x1, x0, #1 //x1 = x0 and 1
  cmp x1, #0
  bne odd
  //even

  tst x0, #1
  bne odd
  //even

  tst x0, #1
  beq even
  //odd

  umull x5, x5, #19

even:
  tst x0, #1
  umulne x5, x5, #19
  b gothere //always go there
  beq somewhere // go to somehwere if z=1

int main(){
  int a = 2;
  int b = 3;
  int c = a <<b; //00000000000000000000010000
  //lsl w0, w1
  //lsl w0, #3

  uint64_t d =0xFEED001U

  2s compliment arithmetic
  int8_t e = 0b10010011
               01101100
                63
                42 84 1
      +1       01101101  64+45 = -109
 1000>> 1 --> divide by 2
 11111111
 11010100

 int32_t e = 7 >>1; 00000000111  7/2=3
                    00000000011
}
                  
int main(){
int a = 2*3;
int x[2*3]

int b;
cin>>b;
int c = b*2; //b<<1
int d =b *32; //b<<5
int e =b/16; //b<<4
uint64_t f b % 5; //b-b /5*5
uint64_t f b % 64; //AND x1, x0, #63

uint32_t h = (b >> 2) | (b << (32-2)); //ror w0, #2

}


*