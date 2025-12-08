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