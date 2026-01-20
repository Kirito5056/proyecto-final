#include <iostream>
#include <vector>
#include <random> 

using namespace std;

// --- SUBPROGRAMAS (EJERCICIOS) ---

// Ejercicio 3: Retorna el total de defectos de toda la matriz
int calcularTotalDefectos(int m, int n, const vector<vector<int>>& matriz) {
    int total = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            total += matriz[i][j];
        }
    }
    return total;
}

// Ejercicio 4: Muestra la tirada donde menor cantidad de defectos existieron
void mostrarTiradaMenorDefectos(int m, int n, const vector<vector<int>>& matriz) {
    int menor_suma = 0;
    int indice_tirada = 0;

    for (int i = 0; i < m; i++) {
        int suma_actual = 0;
        for (int j = 0; j < n; j++) {
            suma_actual += matriz[i][j];
        }
        if (i == 0 || suma_actual < menor_suma) {
            menor_suma = suma_actual;
            indice_tirada = i;
        }
    }
    cout << "La tirada con menor cantidad de defectos fue la: " << indice_tirada + 1 << endl;
}

// Ejercicio 5: Retorna el indice de la tirada donde hubo mayor cantidad de productos defectuosos
int obtenerIndiceTiradaCritica(int m, int n, const vector<vector<int>>& matriz) {
    int max_productos_defectuosos = -1;
    int indice_resultado = 0;

    for (int i = 0; i < m; i++) {
        int contador_productos = 0;
        for (int j = 0; j < n; j++) {
            if (matriz[i][j] > 0) contador_productos++;
        }
        if (contador_productos > max_productos_defectuosos) {
            max_productos_defectuosos = contador_productos;
            indice_resultado = i;
        }
    }
    return indice_resultado;
}

// Ejercicio 6: Retorna verdadero si el horno necesita mantenimiento (ultimas 2 tiradas > 150)
bool verificarMantenimiento(int m, int n, const vector<vector<int>>& matriz) {
    if (m < 2) return false;
    int suma_ultima = 0, suma_penultima = 0;
    for (int j = 0; j < n; j++) {
        suma_ultima += matriz[m - 1][j];
        suma_penultima += matriz[m - 2][j];
    }
    return (suma_ultima > 150 && suma_penultima > 150);
}

// Ejercicio 7: Diga si el horno trabaja eficientemente (> 5 tiradas con defectos < 50)
bool verificarEficiencia(int m, int n, const vector<vector<int>>& matriz) {
    int tiradas_eficientes = 0;
    for (int i = 0; i < m; i++) {
        int suma = 0;
        for (int j = 0; j < n; j++) suma += matriz[i][j];
        if (suma < 50) tiradas_eficientes++;
    }
    return (tiradas_eficientes > 5);
}

// Ejercicio 8: Relacion de equivalencia con 5 productos seleccionados ALEATORIAMENTE
void realizarRelacionEquivalencia(int m, int n, const vector<vector<int>>& matriz) {
    if (n < 5) {
        cout << "Se requieren al menos 5 productos para este ejercicio." << endl;
        return;
    }

    // Configuración de librería <random>
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, n - 1);

    vector<int> seleccionados;
    while (seleccionados.size() < 5) {
        int id_azar = distrib(gen);
        bool repetido = false;
        for (int s : seleccionados) if (s == id_azar) repetido = true;
        if (!repetido) seleccionados.push_back(id_azar);
    }

    cout << "Productos seleccionados aleatoriamente (IDs): ";
    for(int id : seleccionados) cout << id << " ";
    cout << "\nClases de equivalencia (por total historico de defectos):" << endl;

    vector<int> totales(5);
    for (int i = 0; i < 5; i++) {
        int suma = 0;
        for (int k = 0; k < m; k++) suma += matriz[k][seleccionados[i]];
        totales[i] = suma;
    }

    vector<bool> visitado(5, false);
    for (int i = 0; i < 5; i++) {
        if (!visitado[i]) {
            cout << "  - Clase [" << totales[i] << " defectos]: { ID " << seleccionados[i];
            for (int j = i + 1; j < 5; j++) {
                if (totales[j] == totales[i]) {
                    cout << ", ID " << seleccionados[j];
                    visitado[j] = true;
                }
            }
            cout << " }" << endl;
        }
    }
}

// Ejercicio 9: Multiplicacion de matrices 2x2
void realizarOperacionMatrices(int m, int n, const vector<vector<int>>& matriz) {
    if (m < 2 || n < 2) return;
    int id1, id2;
    cout << "Ingrese ID del Producto A: "; cin >> id1;
    cout << "Ingrese ID del Producto B: "; cin >> id2;

    if (id1 >= n - 1) id1 = n - 2;
    if (id2 >= n - 1) id2 = n - 2;
    if (id1 < 0) id1 = 0; if (id2 < 0) id2 = 0;

    int matA[2][2] = { {matriz[0][id1], matriz[0][id1+1]}, {matriz[1][id1], matriz[1][id1+1]} };
    int matB[2][2] = { {matriz[0][id2], matriz[0][id2+1]}, {matriz[1][id2], matriz[1][id2+1]} };
    int matC[2][2];
    matC[0][0] = matA[0][0]*matB[0][0] + matA[0][1]*matB[1][0];
    matC[0][1] = matA[0][0]*matB[0][1] + matA[0][1]*matB[1][1];
    matC[1][0] = matA[1][0]*matB[0][0] + matA[1][1]*matB[1][0];
    matC[1][1] = matA[1][0]*matB[0][1] + matA[1][1]*matB[1][1];

    cout << "\nResultado Multiplicacion 2x2:\n";
    cout << "[" << matC[0][0] << " " << matC[0][1] << "]\n[" << matC[1][0] << " " << matC[1][1] << "]" << endl;
}

// --- PROGRAMA PRINCIPAL ---

int main() {
    int m, n;
    cout << "Ingrese cantidad de productos (Y): "; cin >> n;
    cout << "Ingrese cantidad de tiradas (X): "; cin >> m;

    vector<vector<int>> matriz(m, vector<int>(n));

    cout << "\n--- LLENADO MANUAL DE LA MATRIZ ---" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << "Tirada " << i << ", Producto " << j << ": ";
            cin >> matriz[i][j];
        }
    }

    cout << "\n--- RESULTADOS ---" << endl;
    cout << "Total defectos: " << calcularTotalDefectos(m, n, matriz) << endl;
    mostrarTiradaMenorDefectos(m, n, matriz);
    cout << "Indice tirada critica: " << obtenerIndiceTiradaCritica(m, n, matriz) << endl;
    cout << "Mantenimiento: " << (verificarMantenimiento(m, n, matriz) ? "SI" : "NO") << endl;
    cout << "Eficiente: " << (verificarEficiencia(m, n, matriz) ? "SI" : "NO") << endl;

    realizarRelacionEquivalencia(m, n, matriz);
    realizarOperacionMatrices(m, n, matriz);

    return 0;
}
