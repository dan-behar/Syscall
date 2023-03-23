#include <linux/kernel.h>

asmlinkage long sys_myexpresion_eval(char *cadena, int *valor, int handler(char *)) {
  // retorna 1 cuando la expresion está correctamente cerrada
  // retorna 0 cuando no está correctamente cerrada
  // retorna -1 cuando la expresión es demasiado larga
  printk("Se entro al syscall myexpresion_eval correctamente...\n");
  char *cadena2 = cadena;
  int maximo = 100;
  int indice = -1;
  char signos[maximo];
  maximo = maximo - 1;

  while (*cadena != '\0') {

    if (indice >= maximo) {
      printk("WARNING: La expresion es demasiado larga para ser evaluada\n");
      return -1;
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
	  printk("ERROR: La expresión no está correctamente cerrada...\n");
          return 0; // no está bien cerrada
        }
      } else {
	printk("ERROR: La expresión no está correctamente cerrada...\n");
        return 0; // no está bien cerrada
      }
    } else if (*cadena == ']') {
      if (indice != -1) {
        if (signos[indice] == '[') {
          indice--;
        } else {
	  printk("ERROR: La expresión no está correctamente cerrada...\n");
          return 0; // no está bien cerrada
        }
      } else {
        return 0; // no está bien cerrada
      }
    } else if (*cadena == '}') {
      if (indice != -1) {
        if (signos[indice] == '{') {
          indice--;
        } else {
          return 0; // no está bien cerrada
        }
      } else {
        return 0; // no está bien cerrada
      }
    }

    cadena++;
  }

  // cuando se termina de hacer el recorrido
  if (indice == -1) {
    cadena = cadena2; 
    
    // convertimos todos los corchetes y llaves a parentesis para hacer la evaluacion
    while (*cadena2 != '\0') {
      if(*cadena2 == '['){
        *cadena2 = '('; 
      }
      else if(*cadena2 == '{'){
        *cadena2 = '('; 
      }
      else if(*cadena2 == ']'){
        *cadena2 = ')'; 
      }
      else if(*cadena2 == '}'){
        *cadena2 = ')'; 
      }      
      cadena2++;
    }

    // mandamor la funcion al handler para evaluar la expresion y lo guardamos en valor
    *valor = handler(cadena); 
    printk("Se mandó la expresion: %s a evaluar\n", cadena);
    return 1;
  }
  printk("ERROR: La expresión no está correctamente cerrada...\n");
  return 0;
}
