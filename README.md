*Este proyecto ha sido creado como parte del currículo de 42 por nde-dieg.*

# ft_printf

## Descripción

`ft_printf` es una reimplementación de la función `printf()` de la biblioteca estándar de C. El objetivo del proyecto es reprogramar esta función tan utilizada para comprender en profundidad su funcionamiento interno: el manejo de un número variable de argumentos, el análisis de una cadena de formato y la conversión de distintos tipos de datos a su representación textual.

El resultado es una biblioteca estática, `libftprintf.a`, que expone la función:

```c
int	ft_printf(char const *format, ...);
```

`ft_printf` recorre una cadena de formato, imprime el texto literal tal cual y sustituye cada especificador de conversión (introducido por `%`) por el argumento correspondiente ya formateado. Al igual que la función original, devuelve el número total de caracteres escritos.

Se han implementado las siguientes conversiones:

| Especificador | Descripción |
|:---:|:---|
| `%c` | Un carácter |
| `%s` | Una cadena de caracteres |
| `%p` | Un puntero (`void *`) en formato hexadecimal, con prefijo `0x` |
| `%d` | Un número decimal (base 10) con signo |
| `%i` | Un entero (base 10) con signo |
| `%u` | Un número decimal (base 10) sin signo |
| `%x` | Un número hexadecimal (base 16) en minúsculas |
| `%X` | Un número hexadecimal (base 16) en mayúsculas |
| `%%` | El símbolo de porcentaje |

## Instrucciones

### Compilación

El proyecto se construye con `make`. El `Makefile` compila primero la `libft` (mediante su propio `Makefile`) y después empaqueta los objetos del proyecto y de la `libft` en una única biblioteca, `libftprintf.a`, en la raíz del repositorio.

```bash
make        # Genera libftprintf.a
make clean  # Elimina los archivos objeto (.o)
make fclean # Elimina los .o y la biblioteca libftprintf.a
make re     # Recompila el proyecto desde cero
```

La compilación utiliza las banderas `-Wall -Werror -Wextra`.

### Uso

Para utilizar la biblioteca en un programa, incluye la cabecera y enlaza contra `libftprintf.a`:

```c
#include "ft_printf.h"

int	main(void)
{
	int	count;

	count = ft_printf("Hola, %s! Tienes %d mensajes nuevos.\n", "mundo", 3);
	ft_printf("Se imprimieron %d caracteres.\n", count);
	return (0);
}
```

Compilación de ese ejemplo:

```bash
cc main.c libftprintf.a -o programa
./programa
```

Salida:

```
Hola, mundo! Tienes 3 mensajes nuevos.
Se imprimieron 39 caracteres.
```

## Decisiones técnicas: algoritmo y estructura de datos

### Estructura de datos: `va_list` y las macros `<stdarg.h>`

La función recibe un número indeterminado de argumentos mediante la elipsis (`...`). Para acceder a ellos se utiliza el tipo `va_list` junto con las macros `va_start`, `va_arg` y `va_end` de `<stdarg.h>`.

Esta es la única estructura de datos que el problema requiere, y viene impuesta por la naturaleza variádica de `printf`: los argumentos no tienen nombre ni información de tipo asociada en tiempo de ejecución, por lo que la única forma de recorrerlos es un cursor secuencial (`va_list`) al que se le indica en cada extracción el tipo esperado. Ese tipo se deduce de la cadena de formato: cada especificador determina con qué tipo se invoca `va_arg` (por ejemplo, `%d` → `int`, `%s` → `char *`, `%u` → `unsigned int`). Los caracteres se extraen como `int` porque las conversiones por defecto de argumentos variádicos promocionan `char` y `short` a `int`.

No se emplean estructuras más complejas (listas, buffers dinámicos, tablas hash) porque el problema no lo exige: además, el enunciado prohíbe explícitamente implementar la gestión de buffer del `printf` original. La escritura se realiza directamente carácter a carácter con `write`, lo que mantiene la implementación simple y sin reservas de memoria en el heap.

### Algoritmo: recorrido lineal con delegación y recursión para las bases

El núcleo de `ft_printf` es un **recorrido lineal** de la cadena de formato. Por cada carácter se decide una de dos acciones: si es un carácter literal, se escribe directamente; si es un `%`, se avanza al siguiente carácter y se delega el trabajo a una función despachadora (`set_format`), que selecciona la función de conversión adecuada según el especificador. Cada función de conversión imprime su contenido y **devuelve el número de caracteres escritos**; ese valor se acumula durante todo el recorrido para producir el retorno final. Este diseño mantiene una única responsabilidad por función y hace que el conteo total sea una simple suma de conteos parciales.

Para las conversiones numéricas (`%d`, `%i`, `%u`, `%x`, `%X`, `%p`) se emplea **recursión**. El motivo es que la extracción de dígitos mediante el operador módulo produce las cifras en orden inverso (de la menos significativa a la más significativa), mientras que la impresión debe hacerse en orden natural. La recursión resuelve esta inversión de forma elegante: cada llamada procesa primero el resto del número (las cifras de mayor peso) antes de imprimir su propia cifra, de modo que los dígitos se emiten en el orden correcto sin necesidad de un buffer intermedio ni de invertir una cadena manualmente. La alternativa iterativa exigiría almacenar los dígitos en un array temporal y recorrerlo al revés, lo que añadiría complejidad y una gestión de memoria innecesaria para este caso.

La conversión de valores a caracteres se apoya en una cadena constante usada como tabla de índices (`"0123456789abcdef"` y su variante en mayúsculas). Se prefiere este método frente a la aritmética con `'0'` porque los símbolos hexadecimales de la `a` a la `f` no son contiguos a los dígitos en la tabla ASCII; indexar una cadena cubre de manera uniforme los 16 símbolos posibles.

### Casos límite considerados

Se replica el comportamiento de la implementación de referencia (glibc) en los casos especiales: `%s` con un puntero nulo imprime `(null)`, `%p` con un puntero nulo imprime `(nil)`, y el valor `INT_MIN` se maneja de forma segura (la longitud del entero se calcula usando un tipo `long` para evitar el desbordamiento al negar el mínimo). La función también contempla defensivamente una cadena de formato nula y un `%` final sin especificador.

### Organización del código

El código se reparte en varios archivos fuente según la naturaleza de cada conversión, respetando el límite de funciones por archivo de la Norma de 42: la función principal y el despachador; las conversiones de texto (`%c`, `%s`); las conversiones numéricas y de puntero; y las funciones auxiliares (cálculo de longitudes y tablas de conversión hexadecimal).

## Recursos

Referencias consultadas sobre el tema:

- Página de manual de la función original: `man 3 printf`.
- Especificación del estándar C (ISO/IEC 9899) sobre `fprintf` y las conversiones de formato.
- Documentación de `<stdarg.h>` y las macros de argumentos variádicos (promociones por defecto de argumentos).
- *The C Programming Language* (Kernighan & Ritchie), como referencia general del lenguaje.
- [Python Tutor](https://pythontutor.com) (con soporte para C), utilizado para visualizar la pila de llamadas y comprender el flujo de la recursión paso a paso.
