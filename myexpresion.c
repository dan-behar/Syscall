#include <linux/kernel.h>

asmlinkage long sys_myexpresion(char *cadena) {
  // retorna 1 cuando la expresion está correctamente cerrada
  // retorna 0 cuando no está correctamente cerrada
  // retorna 2 cuando la expresión es demasiado larga
  printk("Entraste al syscall myexpresion\n");
  

  int maximo = 100;
  int indice = -1;
  char signos[maximo];
  maximo = maximo - 1;

  while (*cadena != '\0') {
    //printf("Caracter: %c\n", *cadena);

    if (indice >= maximo) {
      printk("La expresion es demasiado larga para ser evaluada\n");
      return 2;
    }

    // Almacenamiento de signos de apertura
    if (*cadena == '(') {
      indice++;
      signos[indice] = *cadena;
    } else if (*cadena == '[') {
      indice++;
      signos[indice] = *cadena;
    } else if (*cadena == '{') {
      indice++;
      signos[indice] = *cadena;
    }

    // Eliminacion de signos de apertura
    if (*cadena == ')') {
      if (indice != -1) {
        if (signos[indice] == '(') {
          indice--;
        } else {
          printk("La expresion no está bien cerrada\n"); 
          return 0; // no está bien cerrada
        }
      } else {
        printk("La expresion no está bien cerrada\n");
        return 0; // no está bien cerrada
      }
    } else if (*cadena == ']') {
      if (indice != -1) {
        if (signos[indice] == '[') {
          indice--;
        } else {
          printk("La expresion no está bien cerrada\n");
          return 0; // no está bien cerrada
        }
      } else {
        printk("La expresion no está bien cerrada\n");
        return 0; // no está bien cerrada
      }
    } else if (*cadena == '}') {
      if (indice != -1) {
        if (signos[indice] == '{') {
          indice--;
        } else {
          printk("La expresion no está bien cerrada\n");
          return 0; // no está bien cerrada
        }
      } else {
        printk("La expresion no está bien cerrada\n");
        return 0; // no está bien cerrada
      }
    }


    cadena++;
  }

  // cuando se termina de hacer el recorrido
  if (indice == -1) {
    printk("¡La expresion esta cerrada correctamente!\n");
    return 1;
  }
  printk("La expresion no está bien cerrada\n");
  return 0;
}
