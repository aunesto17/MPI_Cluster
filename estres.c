/* File:     mpi_estres.c
 *
 * Purpose:  programa simple para probar el cluster con MPI
 * y ocupa el 100 por ciento de los CPUs
 *
 * Compile:  mpicc -g -Wall -o mpi_estres mpi_estres.c
 * Run:      mpirun -np "numero de procesos" --hostfile hosts ./mpi_estres
 */

#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // Inicializar el entorno MPI
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("Nodo %d: ¡Iniciando carga máxima de CPU! (Presiona Ctrl+C en el master para detener)\n", rank);

    // Variable basura para realizar cálculos pesados
    double multiplicador = 1.000001;
    double resultado = 1.0;

    // Bucle infinito para disparar el uso de la CPU al 100%
    while (1) {
        resultado = resultado * multiplicador;
        
        // Un pequeño reseteo para que el número no colapse la memoria (Overflow)
        if (resultado > 1000000.0) {
            resultado = 1.0;
        }
    }

    // Estas líneas nunca se alcanzarán debido al bucle infinito, pero es buena práctica ponerlas
    MPI_Finalize();
    return 0;
}