#include <iostream>
#include <vector>
#include <random> // Librería para números aleatorios según lo solicitado

using namespace std;

// --- SUBPROGRAMAS ---

// Ejercicio 3: Retorna el total de defectos de toda la matriz (del horno)
int total_defectos_horno(int m, int n, const vector<vector<int>>& matriz) {
    int total = 0;
    for (int i = 0; i < m; i++) { // i = Tirada (X)
        for (int j = 0; j < n; j++) { // j = Producto (Y)
            total += matriz[i][j];
        }
    }
    return total;
}

// Ejercicio 4: Muestra la tirada (fila) con menor cantidad de defectos
void mostrar_tirada_menor_defectos(int m, int n, const vector<vector<int>>& matriz) {
    int menor_suma = 9999999; // Valor inicial alto para comparar
    int indice_tirada = 0;

    for (int i = 0; i < m; i++) {
        int suma_tirada = 0;
        for (int j = 0; j < n; j++) {
            suma_tirada += matriz[i][j];
        }
        if (suma_tirada < menor_suma) {
            menor_suma = suma_tirada;
            indice_tirada = i;
        }
    }
    // Mostramos i + 1 para que el usuario vea "Tirada 1" en vez de "Tirada 0"
    cout << "La tirada con menor cantidad de defectos fue la: " << indice_tirada + 1 << endl;
}

// Ejercicio 5: Retorna el índice de la tirada donde hubo más productos defectuosos
// Un producto es defectuoso si tiene al menos 1 defecto (> 0)
int encontrar_tirada_critica(int m, int n, const vector<vector<int>>& matriz) {
    int max_productos_malos = -1;
    int indice_critico = 0;

    for (int i = 0; i < m; i++) {
        int contador_productos = 0;
        for (int j = 0; j < n; j++) {
            if (matriz[i][j] > 0) { // Si el producto tiene defectos
                contador_productos++;
            }
        }
        if (contador_productos > max_productos_malos) {
            max_productos_malos = contador_productos;
            indice_critico = i;
        }
    }
    return indice_critico;
}

// Ejercicio 6: Verifica mantenimiento (últimas 2 tiradas > 150 defectos cada una)
bool verificar_mantenimiento(int m, int n, const vector<vector<int>>& matriz) {
    if (m < 2) return false; // No hay suficientes tiradas para comparar

    int suma_ultima = 0;
    int suma_penultima = 0;

    // Sumamos la última fila (m-1)
    for (int j = 0; j < n; j++) suma_ultima += matriz[m - 1][j];
    // Sumamos la penúltima fila (m-2)
    for (int j = 0; j < n; j++) suma_penultima += matriz[m - 2][j];

    return (suma_ultima > 150 && suma_penultima > 150);
}

// Ejercicio 7: Verifica eficiencia (más de 5 tiradas con total defectos < 50)
bool verificar_eficiencia(int m, int n, const vector<vector<int>>& matriz) {
    int contador_tiradas_eficientes = 0;

    for (int i = 0; i < m; i++) {
        int suma_tirada = 0;
        for (int j = 0; j < n; j++) {
            suma_tirada += matriz[i][j];
        }
        if (suma_tirada < 50) {
            contador_tiradas_eficientes++;
        }
    }
    return (contador_tiradas_eficientes > 5);
}

// Ejercicio 8: Relación de equivalencia de 5 productos aleatorios
// Agrupa productos por su total de defectos histórico
void relacion_equivalencia_aleatoria(int m, int n, const vector<vector<int>>& matriz) {
    if (n < 5) {
        cout << "No hay suficientes productos para elegir 5 aleatorios." << endl;
        return;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, n - 1);

    vector<int> elegidos;
    while (elegidos.size() < 5) {
        int id = distrib(gen);
        bool repetido = false;
        for (int e : elegidos) if (e == id) repetido = true;
        if (!repetido) elegidos.push_back(id);
    }

    cout << "Productos seleccionados para la relación: ";
    for(int id : elegidos) cout << id << " ";
    cout << "\nClases de equivalencia (por total de defectos):" << endl;

    vector<int> totales_defectos;
    for (int id : elegidos) {
        int suma = 0;
        for (int i = 0; i < m; i++) suma += matriz[i][id];
        totales_defectos.push_back(suma);
    }

    vector<bool> procesado(5, false);
    for (int i = 0; i < 5; i++) {
        if (!procesado[i]) {
            cout << "  - Clase [" << totales_defectos[i] << " defectos]: Productos { ID:" << elegidos[i];
            for (int j = i + 1; j < 5; j++) {
                if (totales_defectos[j] == totales_defectos[i]) {
                    cout << ", ID:" << elegidos[j];
                    procesado[j] = true;
                }
            }
            cout << " }" << endl;
        }
    }
}

// Ejercicio 9: Multiplicación de matrices 2x2 basadas en IDs de productos
void multiplicar_matrices_productos(int m, int n, const vector<vector<int>>& matriz) {
    if (m < 2 || n < 2) {
        cout << "Se requieren al menos 2 tiradas y 2 productos." << endl;
        return;
    }

    int id1, id2;
    cout << "Ingrese ID del Producto 1: "; cin >> id1;
    cout << "Ingrese ID del Producto 2: "; cin >> id2;

    // Validación según nota: si es el último, elegir el anterior
    if (id1 >= n - 1) id1 = n - 2;
    if (id2 >= n - 1) id2 = n - 2;
    if (id1 < 0) id1 = 0; 
    if (id2 < 0) id2 = 0;

    // Formamos Matriz A (Producto id1 e id1+1 en tiradas 0 y 1)
    int A[2][2] = { {matriz[0][id1], matriz[0][id1+1]}, 
                    {matriz[1][id1], matriz[1][id1+1]} };

    // Formamos Matriz B (Producto id2 e id2+1 en tiradas 0 y 1)
    int B[2][2] = { {matriz[0][id2], matriz[0][id2+1]}, 
                    {matriz[1][id2], matriz[1][id2+1]} };

    // Multiplicación de matrices 2x2: C = A * B
    int C[2][2];
    C[0][0] = A[0][0]*B[0][0] + A[0][1]*B[1][0];
    C[0][1] = A[0][0]*B[0][1] + A[0][1]*B[1][1];
    C[1][0] = A[1][0]*B[0][0] + A[1][1]*B[1][0];
    C[1][1] = A[1][0]*B[0][1] + A[1][1]*B[1][1];

    cout << "\nResultado de la multiplicacion 2x2:\n";
    cout << "| " << C[0][0] << " " << C[0][1] << " |\n";
    cout << "| " << C[1][0] << " " << C[1][1] << " |\n";
}

// --- PROGRAMA PRINCIPAL ---

int main() {
    int n, m;
    cout << "--- SISTEMA DE CONTROL DE FUNDICION ---" << endl;
    cout << "Ingrese cantidad de productos a analizar (Y): "; cin >> n;
    cout << "Ingrese cantidad de tiradas realizadas (X): "; cin >> m;

    // Construcción de la matriz: matriz[Tirada][Producto] según enunciado (x, y)
    vector<vector<int>> matriz_defectos(m, vector<int>(n));

    // Llenado aleatorio para agilizar la prueba
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 20); // Defectos entre 0 y 20

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matriz_defectos[i][j] = dist(gen);
        }
    }

    cout << "\n--- RESULTADOS ---" << endl;
    
    // Ejercicio 3
    cout << "Total de defectos del horno: " << total_defectos_horno(m, n, matriz_defectos) << endl;

    // Ejercicio 4
    mostrar_tirada_menor_defectos(m, n, matriz_defectos);

    // Ejercicio 5
    cout << "Indice de la tirada con mas productos defectuosos: " << encontrar_tirada_critica(m, n, matriz_defectos) << endl;

    // Ejercicio 6
    if (verificar_mantenimiento(m, n, matriz_defectos))
        cout << "El horno necesita mantenimiento: SI" << endl;
    else
        cout << "El horno necesita mantenimiento: NO" << endl;

    // Ejercicio 7
    if (verificar_eficiencia(m, n, matriz_defectos))
        cout << "El horno trabaja eficientemente: SI" << endl;
    else
        cout << "El horno trabaja eficientemente: NO" << endl;

    // Ejercicio 8
    cout << "\n--- RELACION DE EQUIVALENCIA ---" << endl;
    relacion_equivalencia_aleatoria(m, n, matriz_defectos);

    // Ejercicio 9
    cout << "\n--- OPERACION DE MATRICES 2x2 ---" << endl;
    multiplicar_matrices_productos(m, n, matriz_defectos);

    return 0;
}
