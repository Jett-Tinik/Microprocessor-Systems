/*  Assembler code

 .global f2
f2:
  mov w1, w0
  mov w0, 0
  mov w2, 1
loop:
  add w0, w0, w2
  add w2, w2, 1
  cmp w2, w1

  ble loop2
  ret
  .global main
main:
  mov w0, 5
  bl f  //f(5)

  mov w0, 5
  bl f2

  ret
----------------------
int sum(const int x[], int len);

int main (){
  int x[] = {1, 2, 3, 4, 9};
  int s = sum(x,5);
  cout << s<< '\n';
}
---------------------
  .global_Z3sumPKii //pointer to integer (PKi) then just integer (i)
    //x0= adress of the array
    //w1 = len
_Z3sumPKii:
  mov w2, 0 //sum=0
loop:
  ldr w3, [x0]  //store mem of x0 in w3
  add w2, w2, w3 // w2 = w2+w3
  add x0, x0, 4 // advance 4 bits to right to next number (in place of x[1],
                    x[2], etc.)
  sub w1, w1, 1 // count down
  cmp w1, 0
  bgt 1b //backwards to the nearest 1 ----(other way bge 1b)
  ret

  add  6(%edx), %eax
  str w3, [x0] opposite of ldr //go to w3 and str mem in x0

  //grant simmons imd conatct
  --------------------

  Write a func that takes x0=array w1 = len
  add 1 to each element in the array

  1.w
    .global_ZaddonePKii:
    //x0=array w1=length
_ZaddonePKii:
  ldr w3, [x0] ///load memory into w3

  sub w1, w1, 1 // count down
  cmp w1, 0

  2. write a function that takes x0=array1 x1 array2 w2 = len
  compute the dot product:
  example x0 = [1, 2, 3]
  x[3,4,5]
  1*3+2*4+3*5

  return 26

  3. write a function that takes x0=array w1 = len return sum of cubes

  */