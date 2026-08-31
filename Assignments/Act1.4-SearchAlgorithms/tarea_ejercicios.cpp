#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

// busca secuencial
template <typename T>
bool buscaSecuencial(const vector<T>& arr, T x, double& tiempo) {
    clock_t inicio = clock();   // medicion de tiempo
    bool encontrado = false;
    for (size_t i = 0; i < arr.size(); i++) {
        if (arr[i] == x) {
            encontrado = true;
            break;
        }
    }
    
    clock_t fin = clock(); // Para el reloj
    // calculo de tiempo en milisegundos
    tiempo = 1000.0 * (fin - inicio) / CLOCKS_PER_SEC;
    
    return encontrado;
}

// busca binaria
template <typename T>
bool buscaBinaria(const vector<T>& arr, T x, double& tiempoMs) {
    clock_t inicio = clock();
    
    bool encontrado = false;
    int izq = 0;
    int der = arr.size() - 1;
    
    while (izq <= der) {
        int mid = izq + (der - izq) / 2;
        if (arr[mid] == x) {
            encontrado = true;
            break;
        }
        if (arr[mid] < x) {
            izq = mid + 1;
        } else {
            der = mid - 1;
        }
    }
    
    clock_t fin = clock();
    tiempoMs = 1000.0 * (fin - inicio) / CLOCKS_PER_SEC;
    
    return encontrado;
}

void secuencialUnico(const string& s) {
    int comps = 0;
    char unico = s[s.length() - 1]; // Asumimos por defecto que es el último

    // Saltamos de 2 en 2 para revisar los pares
    for (int i = 0; i < s.length() - 1; i += 2) {
        comps++;
        if (s[i] != s[i+1]) { // Si el par no coincide, encontramos al intruso
            unico = s[i];
            break;
        }
    }
    // Imprimimos el resultado secuencial
    cout << unico << " " << comps << " ";
}



//  EJERCICIO 2
void binariaUnico(const string& s) {
    int izq = 0;
    int der = s.length() - 1;
    int comps = 0;

    while (izq < der) {
        int mid = izq + (der - izq) / 2;
        
        // mid siempre sera un numero par y se ira restando
        if (mid % 2 != 0) {
            mid--;
        }

        comps++;
        // si coincide el par, el error esta a la derecha
        if (s[mid] == s[mid+1]) {
            izq = mid + 2; 
        } else {
            // Si no coincide, el error esta mas izquierda
            der = mid;
        }
    }
    cout << s[izq] << " " << comps << "\n";
}

int main() {
    cout<<"Ejercicio 1\n Ejercicio 2\n";
    int ejercicio;
    cin>>ejercicio;
    if (ejercicio == 1) {
        //uso de libreria random para generar los numeros
        random_device rd;
        mt19937 gen(rd());  // Motor para generar los numeros
        uniform_int_distribution<int> lista(1, 1000000);

        vector<int> numeros(10000);
        for (int i = 0; i < 10000; i++) {
            numeros[i] = lista(gen);
        }
        cout <<"Lista hecha\n"<<endl;
        cout <<"Ordenando los numeros..."<<endl;
        // ordenar para busqueda binaria
        sort(numeros.begin(), numeros.end());

        // busca de numeros
        int busca;
        while (true) {
            cout << "Ingresa el numero a buscar (0 para salir): ";
            cin >> busca;

            if (busca == 0) {
                break;
                return 0;
            }

            double tiempoSeq = 0, tiempoBin = 0;
            bool resSeq = buscaSecuencial(numeros, busca, tiempoSeq);
            bool resBin = buscaBinaria(numeros, busca, tiempoBin);
            if (resSeq || resBin) {
                cout << "El numero >> " <<busca<< " <<esta en la lista.\n";
            }
            else { 
                cout << "El numero >> " <<busca<< " << no esta en la lista.\n";
            }

            // Resultados de tiempo
            cout << "Tiempo Secuencial: " << tiempoSeq << " ms\n";
            cout << "Tiempo Binaria:    " << tiempoBin << " ms\n\n";
        }
}
    if (ejercicio==2) {
        int n;
        if (!(cin >> n)) return 0; 
        vector<string> strings(n);
        for (int i = 0; i < n; i++) {
            cin >> strings[i];
        }
        for (int i = 0; i < n; i++) {
            secuencialUnico(strings[i]);
            binariaUnico(strings[i]);
        }
}
    return 0;
}