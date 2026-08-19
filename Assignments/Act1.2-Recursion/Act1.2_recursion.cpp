#include <iostream>
using namespace std;

int factorial(int n) {
    if (n<= 1) {
        return 1;
    }
    return n * factorial(n-1);
};

int sumItery(int n) {
    int suma=0;
    for (int i=1; i<=n; i++) {
        suma +=1;
    }
    return suma;
}

// Esta es mas facil de leer, pero utiliza mas memoria
int sumRecursive(int n) {
    if(n==1) {
        return 1;
    }
    return n +sumRecursive(n-1);
}

int sumFormula(int n) {
    return n*(n+1)/2;
}

int fibonacciIterative(int n) {
    int a=1;
    int b=1;
    int c;
    for (int i=3; i<=n; i++) {
        c=a+b;
        a=b;
        b=c;
    }
    return b;
}

int fibonacciRecursive(int n) {
    if (n<=2) {
        return 1;
    }
    return fibonacciRecursive(n-1)+ fibonacciRecursive(n-2);
}

int bacteriasIterative(int n) {
    double alive=3.78;
    double dead=2.34;
    int sum=1;
    for (int i=1; i<=n; i++) {
        int bacborn = sum*alive;
        int bacdied = sum*dead;
        sum+= bacborn-bacdied;
    }
    return sum;
}

int bacteriasRecursive(int n) {
    if(n==0) {
        return 1;
    }
    int bacteria = bacteriasRecursive(n-1);
    int born = bacteria * 3.78;
    int dead = bacteria * 2.34;
    return bacteria + born - dead;
}

double investmentIterative(int n) {
    double saldo=100;
    double im= 1.1875;
    while (n != 0) {
        saldo=saldo*im;
        n=n-1;
    }

    return saldo;
}

double investmentRecursive(int n) {
    double saldo=100;
    if(n==0) {
        return saldo;
    }
    double im= 1.1875;
    return investmentRecursive(n-1)*im;
}

double powIterative(int n, int x) {
    double result=1;
    while(x > 0) {
        result= result*n;
        x= x-1;
    }

    return result;
}

double powRecursive(int n, int x) {
    if(x==0) {
        return 1;
    }
    return powRecursive(n, x-1) * n;
}   

int main() {
    cout<<"El factrorial de 5 es: "<< factorial(5)<<endl;
    // iterativa
    cout<<"La suma iterativa de 5 es: "<< sumItery(5)<<endl;
    // suma recursiva
    cout<<"La suma recursiva de 5 es: "<< sumRecursive(5)<<endl;
    // formula n*(n+1)/2;
    cout<<"La suma de formula con 5 es: "<<sumFormula(5)<<endl;
    // fibonacci iterativa
    cout<<"Fibonacci iterativa de 8 es: "<<fibonacciIterative(8)<<endl;
    // fibonacci recursiva
    cout<<"Fibonacci recursiva de 8 es: "<<fibonacciRecursive(8)<<endl;
    // bacterias iter
    cout<<"1 bacteria viva en 5 dias iterados seran: "<<bacteriasIterative(5)<<endl;
    // bacterias recursive
    cout<<"1 bacteria viva en 5 dias iterados seran: "<<bacteriasRecursive(5)<<endl;
    // banco iterative
    cout<<"Crecimiento a 5 meses de 100 pesos: "<<investmentIterative(5)<<endl;
    // banco recursive
    cout<<"Crecimiento a 5 meses de 100 pesos: "<<investmentRecursive(5)<<endl;
    // pow
    cout<<"Ingresa 2 numeros enteros para usar:\npowIterative y powRecursive\n(primero base y luego potencia): "<<endl;
    int n;
    int x;
    cin>> n;
    cin>> x; 
    powIterative(n, x); powRecursive(n, x);
    cout<<"Resultado iterative "<<powIterative(n, x)<<endl;
    cout<<"Resultado recursive "<<powRecursive(n, x)<<endl;

    return 0;
}