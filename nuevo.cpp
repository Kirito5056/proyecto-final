#include <iostream>
#include <vector>
#include <random>

using namespace std;

// --- SUBPROGRAMAS (EJERCICIOS) ---

// Ejercicio 3: Retorna el total de defectos
int calcularTotalDefectos(int m, int n, const vector<vector<int>>& matriz) {
    int total = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            total += matriz[i][j];
        }
    }
    return total;
}

// Ejercicio 4: Tirada con menor cantidad de defectos
void mostrarTiradaMenorDefectos(int m, int n, const vector<vector<int>>& matriz) {
    int menor_suma = 0;
    int indice_tirada = 0;
    for (int i = 0; i < m; i++) {
        int suma_actual = 0;
        for (int j = 0; j < n; j++) suma_actual += matriz[i][j];
        if (i == 0 || suma_actual < menor_suma) {
            menor_suma = suma_actual;
            indice_tirada = i;
        }
    }
    cout << "La tirada con menor cantidad de defectos fue la: " << indice_tirada + 1 << endl;
}

// Ejercicio 5: Indice de tirada con mayor cantidad de PRODUCTOS defectuosos
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

// Ejercicio 6: Mantenimiento (ultimas 2 tiradas > 150 cada una)
bool verificarMantenimiento(int m, int n, const vector<vector<int>>& matriz) {
    if (m < 2) return false;
    int suma_ultima = 0, suma_penultima = 0;
    for (int j = 0; j < n; j++) {
        suma_ultima += matriz[m - 1][j];
        suma_penultima += matriz[m - 2][j];
    }
    return (suma_ultima > 150 && suma_penultima > 150);
}

// Ejercicio 7: Eficiencia (> 5 tiradas con < 50 defectos)
bool verificarEficiencia(int m, int n, const vector<vector<int>>& matriz) {
    int tiradas_eficientes = 0;
    for (int i = 0; i < m; i++) {
        int suma = 0;
        for (int j = 0; j < n; j++) suma += matriz[i][j];
        if (suma < 50) tiradas_eficientes++;
    }
    return (tiradas_eficientes > 5);
}

// Ejercicio 8: Relacion de equivalencia (5 productos aleatorios)
void realizarRelacionEquivalencia(int m, int n, const vector<vector<int>>& matriz) {
    if (n < 5) {
        cout << "\n[Aviso] Se requieren al menos 5 productos para este ejercicio." << endl;
        return;
    }
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

    cout << "\nProductos seleccionados aleatoriamente (IDs): ";
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
    
    // Validacion entrada ID 1
    cout << "\nIngrese ID del Producto A: ";
    while (!(cin >> id1) || id1 < 0 || id1 >= n) {
        cout << "Error. Ingrese un ID valido entre 0 y " << n-1 << ": ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    // Validacion entrada ID 2
    cout << "Ingrese ID del Producto B: ";
    while (!(cin >> id2) || id2 < 0 || id2 >= n) {
        cout << "Error. Ingrese un ID valido entre 0 y " << n-1 << ": ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    // Regla del enunciado: si es el ultimo, se elige el anterior
    if (id1 == n - 1) id1 = n - 2;
    if (id2 == n - 1) id2 = n - 2;

    // Matriz A (Filas 0 y 1, Columnas id1 e id1+1)
    int matA[2][2] = { {matriz[0][id1], matriz[0][id1+1]}, {matriz[1][id1], matriz[1][id1+1]} };
    // Matriz B (Filas 0 y 1, Columnas id2 e id2+1)
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

    // Validacion N (productos)
    cout << "Ingrese cantidad de productos (Y): ";
    while (!(cin >> n) || n <= 0) {
        cout << "Error. Ingrese un numero entero positivo: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    // Validacion M (tiradas)
    cout << "Ingrese cantidad de tiradas (X): ";
    while (!(cin >> m) || m <= 0) {
        cout << "Error. Ingrese un numero entero positivo: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    vector<vector<int>> matriz(m, vector<int>(n));

    cout << "\n--- LLENADO DE LA MATRIZ ---" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << "Tirada " << i << ", Producto " << j << " (defectos): ";
            while (!(cin >> matriz[i][j]) || matriz[i][j] < 0) {
                cout << "Error. Ingrese un numero de defectos valido (0 o mas): ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
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
