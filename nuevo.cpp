#include <iostream>
#include <vector>
#include <climits>
using namespace std;

//Subprogramas utilizados

//Subprograma Ejercicio 3
int total_de_defectos(int n,int m,const vector<vector<int>>& matriz){
    int total = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            total += matriz[i][j];
        }
    }
    return total;
}


//Subprograma Ejercicio 4
void menor_cantidad_de_defectos(int n, int m, const vector<vector<int>>& matriz){
    int menor_total_defectos = INT_MAX; 
    int tirada_optima = 0;
    for(int j = 0; j < m; j++){
        int total_defectos_tirada = 0;
        for(int i = 0; i < n; i++){
            total_defectos_tirada += matriz[i][j];
        }
        if(total_defectos_tirada < menor_total_defectos){
            menor_total_defectos = total_defectos_tirada;
            tirada_optima = j + 1; 
        }
    }
    
    cout << "La tirada donde existió la menor cantidad de defectos en los productos fue la: Tirada " << tirada_optima << "." << endl;
}


//Subprograma Ejercicio 5
int encontrar_tirada_critica(int n, int m, const std::vector<std::vector<int>>& matriz){
    int mayor_total_defectos = INT_MIN; 
    int tirada_critica = 0;
    for(int j = 0; j < m; j++){
        int total_defectos_tirada = 0;
        for(int i = 0; i < n; i++){
            total_defectos_tirada += matriz[i][j];
        }

        if(total_defectos_tirada > mayor_total_defectos){
            mayor_total_defectos = total_defectos_tirada;
            tirada_critica = j + 1; 
        }
    }
    return tirada_critica;
}


//Subprograma Ejercicio 6
bool verificar_mantenimiento(int n, int m, const vector<vector<int>>& matriz){
    if (m<2) {
        cout <<"ADVERTENCIA:Se requieren al menos 2 tiradas para esta verificación."<<endl;
        return false; 
    }
    int limite_defectos = 150;
    int total_ultima_tirada = 0;
    int total_penultima_tirada = 0;
    for (int i = 0; i < n; i++) {
        total_ultima_tirada += matriz[i][m - 1]; 
        total_penultima_tirada += matriz[i][m - 2];
    }
    return (total_ultima_tirada > limite_defectos && total_penultima_tirada > limite_defectos);
}


//Subprograma Ejercicio 7
bool verificar_eficiencia(int n, int m, const vector<vector<int>>& matriz){
    int tiradas_eficientes = 0;
    const int limite_defectos = 50;
    const int limite_tiradas_eficientes = 5;
    for(int j = 0; j < m; j++){
        int total_defectos_tirada = 0;
        for(int i = 0; i < n; i++){
            total_defectos_tirada += matriz[i][j];
        }
        if(total_defectos_tirada < limite_defectos){
            tiradas_eficientes++;
        }
    }
    if (tiradas_eficientes > limite_tiradas_eficientes) {
        return true;
    } else {
        return false;
    }
}


//Subprograma Ejercicio 8
//Subprograma auxiliar para calcular el total de defectos por producto
int total_defectos_producto(int producto_index, int m, const vector<vector<int>>& matriz) {
    int total = 0;
    // Recorre las tiradas (columnas) para el producto dado (fila)
    for (int j = 0; j < m; j++) {
        total += matriz[producto_index][j];
    }
    return total;
}
//Subprograma principal
void obtener_relacion_equivalencia(int n, int m, const vector<vector<int>>& matriz) {
    const int NUM_REQUERIDOS = 5;
    if (n < NUM_REQUERIDOS) {
        cout << "ADVERTENCIA: Se necesitan al menos 5 productos. Usando todos los " << n << " productos disponibles." << endl;
        return; 
    }
    vector<int> productos_seleccionados(NUM_REQUERIDOS); 
    cout << "Por favor, introduzca los ID de " << NUM_REQUERIDOS << " productos para el análisis (ID de 0 a " << n - 1 << "):" << endl;

    for (int i = 0; i < NUM_REQUERIDOS; i++) {
        int id_ingresado;
        bool valido = false;
        while (!valido) {
            cout << "  - ID Producto " << i + 1 << ": ";
            if (cin >> id_ingresado) {
                if (id_ingresado >= 0 && id_ingresado < n) {
                    bool duplicado = false;
                    for (int j = 0; j < i; j++) {
                        if (productos_seleccionados[j] == id_ingresado) {
                            duplicado = true;
                            break;
                        }
                    }
                    if (!duplicado) {
                        productos_seleccionados[i] = id_ingresado;
                        valido = true;
                    } else {
                        cout << " ID ya seleccionado. Intente de nuevo." << endl;
                    }
                } else {
                    cout << " ID fuera de rango (0 a " << n - 1 << "). Intente de nuevo." << endl;
                }
            } else {
                cout << " Entrada inválida. Intente de nuevo." << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
        }
    }

    cout << "\nProductos seleccionados (ID en la matriz): ";
    for (int id : productos_seleccionados) {
        cout << id << " ";
    }
    cout << endl;
    vector<pair<int, int>> defectos_por_producto; 
    cout << "Totales de Defectos:" << endl;
    for (int id : productos_seleccionados) {
        int total = total_defectos_producto(id, m, matriz);
        defectos_por_producto.push_back({total, id});
        cout << "  - Producto " << id << ": " << total << " defectos." << endl;
    }
    cout << "\nClases de Equivalencia (Productos con el mismo total de defectos):" << endl;
    
    vector<bool> ya_procesado(NUM_REQUERIDOS, false);
    for (int i = 0; i < NUM_REQUERIDOS; i++) {
        if (!ya_procesado[i]) {
            int defecto_base = defectos_por_producto[i].first;
            cout << "  [Clase de Defectos = " << defecto_base << "]: {";
            
            bool primer_elemento = true;
            for (int j = i; j < NUM_REQUERIDOS; j++) {
                if (defectos_por_producto[j].first == defecto_base) {
                    if (!primer_elemento) {
                        cout << ", ";
                    }
                    cout << "Producto " << defectos_por_producto[j].second; 
                    ya_procesado[j] = true;
                    primer_elemento = false;
                }
            }
            cout << "}" << endl;
        }
    }
}


//Subprograma Ejercicio 9
// Subprograma auxiliar: Multiplica dos matrices 2x2 (A y B) y retorna el resultado C
vector<vector<int>> multiplicar_matrices_2x2(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    vector<vector<int>> C(2, vector<int>(2, 0)); 
    
    C[0][0] = (A[0][0] * B[0][0]) + (A[0][1] * B[1][0]);
    C[0][1] = (A[0][0] * B[0][1]) + (A[0][1] * B[1][1]);
    C[1][0] = (A[1][0] * B[0][0]) + (A[1][1] * B[1][0]);
    C[1][1] = (A[1][0] * B[0][1]) + (A[1][1] * B[1][1]);
    
    return C;
}

// Subprograma auxiliar: Muestra una matriz 2x2 en la consola
void mostrar_matriz_2x2(const string& nombre, const vector<vector<int>>& matriz) {
    cout << "\nMatriz " << nombre << ":" << endl;
    cout << "  | " << matriz[0][0] << "  " << matriz[0][1] << " |" << endl;
    cout << "  | " << matriz[1][0] << "  " << matriz[1][1] << " |" << endl;
}
//Subprograma principal
void procesar_y_multiplicar_matrices(int n, int m, const vector<vector<int>>& matriz_defectos) {
    if (n < 2 || m < 2) {
        cout << "ADVERTENCIA: Se necesitan al menos 2 productos y 2 tiradas para formar matrices 2x2." << endl;
        return;
    }
    int id1, id2;
    cout << "Ingrese el ID del primer producto (0 a " << n - 1 << "): ";
    if (!(cin >> id1) || id1 < 0 || id1 >= n) {
        cout << " ID de producto no válido o fuera de rango." << endl;
        return;
    }
    cout << "Ingrese el ID del segundo producto (0 a " << n - 1 << "): ";
    if (!(cin >> id2) || id2 < 0 || id2 >= n) {
        cout << " ID de producto no válido o fuera de rango." << endl;
        return;
    }
    if (id1 == n - 1) { 
        cout << " El ID original del Producto 1 corresponde al último. Se usará el ID " << id1 - 1 << " para la Matriz A." << endl;
        id1 = n - 2; 
    }
    if (id2 == n - 1) {
        cout << " El ID original del Producto 2 corresponde al último. Se usará el ID " << id2 - 1 << " para la Matriz B." << endl;
        id2 = n - 2; 
    }

    vector<vector<int>> MatrizA(2, vector<int>(2));
    MatrizA[0][0] = matriz_defectos[id1][0];      // Producto ID1, Tirada 0
    MatrizA[0][1] = matriz_defectos[id1][1];      // Producto ID1, Tirada 1
    MatrizA[1][0] = matriz_defectos[id1 + 1][0];  // Producto ID1+1, Tirada 0
    MatrizA[1][1] = matriz_defectos[id1 + 1][1];  // Producto ID1+1, Tirada 1
    

    vector<vector<int>> MatrizB(2, vector<int>(2));
    MatrizB[0][0] = matriz_defectos[id2][0];      // Producto ID2, Tirada 0
    MatrizB[0][1] = matriz_defectos[id2][1];      // Producto ID2, Tirada 1
    MatrizB[1][0] = matriz_defectos[id2 + 1][0];  // Producto ID2+1, Tirada 0
    MatrizB[1][1] = matriz_defectos[id2 + 1][1];  // Producto ID2+1, Tirada 1

    cout << "\nIDs utilizados para formar matrices:" << endl;
    cout << "  - Matriz A: Productos ID " << id1 << " y ID " << id1 + 1 << "." << endl;
    cout << "  - Matriz B: Productos ID " << id2 << " y ID " << id2 + 1 << "." << endl;
    mostrar_matriz_2x2("A (Defectos)", MatrizA);
    mostrar_matriz_2x2("B (Defectos)", MatrizB);
    vector<vector<int>> MatrizC = multiplicar_matrices_2x2(MatrizA, MatrizB);
    cout << "\nEl resultado de la multiplicación C = A x B es:" << endl;
    mostrar_matriz_2x2("C (Resultado de la Multiplicación)", MatrizC);
}


int main(){
cout<<endl<<"#####Bienvenido al Trabajo Final de IP de Pedro Enrique Perez Lopez#####"<<endl<<endl;

cout<<"Ejercicio 1"<<endl;
int n; //Este va a ser numero de productos a analizar
int m; //Este va a ser la cantidad de tiradas realizadas
cout<<"Ingrese la cantidad de productos a analizar: ";cin>>n;
cout<<"Ingrese la cantidad de tiradas realizadas: ";cin>>m;
vector<vector<int>> matriz_defectos(n, vector<int>(m));
for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
        cout<<"Ingrese la cantidad de defectos para el producto actual en la tirada actual["<<i<<"]["<<j<<"]: ";
        cin>>matriz_defectos[i][j];    
    }
}



cout<<endl<<"Ejercicio 2"<<endl;
for (int i = 0; i < n; i++) {
        // Inicializa el acumulador a CERO para CADA NUEVO producto
        int total_defectos_producto = 0; 
        
        // Bucle Interior (Recorre las Tiradas - Columnas de la fila actual)
        for (int j = 0; j < m; j++) {
            // Suma el defecto de la posición actual [i][j] al total de la fila
            total_defectos_producto += matriz_defectos[i][j];
        }

        // Mostrar el resultado una vez que la fila completa ha sido sumada
        cout << "El Producto " << i + 1 << " tuvo un total de " 
             << total_defectos_producto << " defectos." << endl;
    }



cout<<endl<<"Ejercicio 3"<<endl;
    int defectos_totales_horno = total_de_defectos(n,m,matriz_defectos);
    cout << "El horno ha provocado un total de " <<defectos_totales_horno<<" defectos en toda la producción." << endl;


cout<<endl<<"Ejercicio 4"<<endl;
    menor_cantidad_de_defectos(n,m,matriz_defectos);


cout<<endl<<"Ejercicio 5"<<endl;
int tirada_mayor = encontrar_tirada_critica(n,m,matriz_defectos);
cout << "La tirada mayor del horno fue la tirada: "<<tirada_mayor<<endl;


cout<<endl<<"Ejercicio 6"<<endl;
bool necesita_mantenimiento = verificar_mantenimiento(n,m,matriz_defectos);
cout<<"El Horno necesita mantenimiento?: "<<necesita_mantenimiento<<endl;


cout<<endl<<"Ejercicio 7"<<endl;
bool es_eficiente = verificar_eficiencia(n,m,matriz_defectos);
cout<<"El horno trabaja eficientemente?: "<<es_eficiente;


cout<<endl<<endl<<"Ejercicio 8"<<endl;
obtener_relacion_equivalencia(n,m,matriz_defectos);


cout<<endl<<"Ejercicio 9"<<endl;
procesar_y_multiplicar_matrices(n,m,matriz_defectos);

return 0;
}
