#include <iostream>

int main(){
  int* p1; 
  int* p2;
  p1 = new int[3];
  
  p1[1] = 0;
  p2[1]=p1[1];
  std::cout << p2[1] << std::endl;
  delete[] p1;
}