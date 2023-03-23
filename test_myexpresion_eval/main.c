#include "tinyexpr.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>


// definicion del syscall
#define __NR_expresion 334

long expresion_eval_syscall(char *cadena, int *valor, int handler(char *)) {
    return syscall(__NR_expresion, cadena, valor, handler);
}


int funcionEval(char * parametro){
  int result = (int) floor(te_interp(parametro, 0));
  return result;
}

int main(void) {
  int resultado;
  int valor; 
  char entrada[100];

  printf("Ingrese una expresion: ");
  scanf("%s", entrada);
  printf("\n");

  resultado = expresion_eval_syscall(entrada, &valor, funcionEval);

  printf("\nResultado: %s\n", resultado?"true":"false");
  printf("\nResultado de eval: %d\n", valor);

  return 0;
}
