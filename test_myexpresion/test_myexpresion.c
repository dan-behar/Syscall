#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#define __NR_myexpresion 333

long myexpresion_syscall(char *cadena) {
    return syscall(__NR_myexpresion, cadena);
}

int main(int argc, char *argv[]) {
    long resultado;
    char cadena[100]; 
	
    printf("Ingrese una expresion: \n"); 
    scanf("%s", cadena); 

    resultado = myexpresion_syscall(cadena);

    printf("\nResultado: %s\n", resultado?"true":"false");

    return 0;
}

