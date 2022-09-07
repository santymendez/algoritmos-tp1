#include <iostream>
#include <fstream>

using namespace std;

void mostrar_mat(float m[][5], int dfil){

    for(int i = 0; i < dfil; i++){
        for(int j = 0; j < 5; j++)
            cout << m[i][j] << '\t';
        cout << endl;
    }
}

void mostrar_vec(float v[], int dim){
    
    for(int i = 0; i < dim; i++){
        cout << i << ": " << v[i] << endl;
    }
}

int max_vec(int v[], int dim){  //busca el valor max de un arraid y devuelve la posicion de ese valor
    
    int max = v[0];
    int pos{0};

    for(int i = 1; i < dim; i++){
        if(v[i] > max){
            max = v[i];
            pos = i;
        }
    }

    return pos;
}

void ordenar(float v[], int dim, int vpos[]){ //algoritmo de seleccion

    for(int pos = 0; pos < dim; pos++){
        int min = pos;
        for(int i = pos + 1; i < dim; i++){
            if(v[i] < v[min]){
                min = i;
            }
        }
        
        swap(v[pos], v[min]); //intercambia valores.
        swap(vpos[pos], vpos[min]); //intercambia posicion de esos valores.
    } 
}

int main(){

    ifstream archi;

    archi.open("Nombres.txt");
    if(!archi){
        cout << "Error al abrir el archivo de nombres" << endl; 
        return 1;
    }

    const int ncli{8}; //numero de clientes.
    const int nprod{5}; //numero de productos.

    float entregas_kg[ncli][nprod]{}; //entregas por peso.
    float entregas_km[ncli][nprod]{}; //entregas por recorrido.
    
    int prodmax[ncli]{}; //contador de tipo de productos entregados con mas de 13.000 kg por cliente.
    int entregas_producto[nprod]{}; //contador de entregas por tipo de producto
    
    float km_prod[nprod]{}; //kilometros recorridos por tipo de producto de un solo cliente.
    int vpos[nprod]{}; //vector posiciones.
    
    string clientes[ncli]{}; //nombres de los clientes.
    string productos[nprod]{}; //nombres tipo de porductos.
    
    for(int i = 0; i < ncli; i++){   //carga los nombres de los clientes.
        archi >> clientes[i];          
    }
    
    for(int i = 0; i < nprod; i++){  //carga los nombres de los productos.
        archi >> productos[i];        
    }
    
    archi.close();

    archi.open("Datos.txt");
    if(!archi){
        cout << "Error al abrir el archivo de nombres" << endl;
        return 1;
    }

    int client, prod;
    float kg, km;       //variables para cargar datos del archivo

    while(archi >> client >> prod >> kg >> km){
        entregas_kg[client][prod] += kg;  //suma los kg por cliente/producto.
        entregas_km[client][prod] += km;  //suma los km por cliente/producto.
        entregas_producto[prod]++;        //cuenta la cantidad de entregas que se hacen por tipo de producto
    }

    cout << "Listado por clientes, de los tipos de productos que superan los 13000 Kg acumulados:" << endl;
    
    bool flag = true;  //variable para controlar si es necesario mostrar el nombre del cliente, o mostrar una coma.
    
    for(int i = 0; i < ncli; i++){
        flag = true;  
        for(int j = 0; j < nprod; j++){
            if(entregas_kg[i][j] > 13000){  
                prodmax[i]++;
                if(flag == true){                  
                    cout << clientes[i] << ": ";    
                    flag = false;
                } else {
                    cout << ", ";
                }
                cout << productos[j]; 
            }
        } 
        cout << endl; 
    } 
    
    cout << endl;

    int max = max_vec(prodmax, ncli); //posicion del cliente con mayor cantidad de tipos de productos que superaron los 13000 kg

    cout << "El cliente con mayor cantidad de tipos de productos que superaron los 13000 kg es: " << clientes[max] << endl << endl;

    cout << "Listado de Km recorridos por tipo de producto (ascendente):" << endl;
    
    for(int i = 0; i < nprod; i++){
        km_prod[i] = entregas_km[max][i]; //carga un vector con los km x producto del cliente que mas entregas hizo.
        vpos[i] = i;                      //vector de posiciones.
    }

    ordenar(km_prod, nprod, vpos);

    for(int i = 0; i < nprod; i++){
        cout << productos[vpos[i]] << ": " << km_prod[i] << endl;  //muestra los kilometros por cada producto en forma ascendente.
    } cout << endl;                                               //utiliza el vector de posiciones para ordenar tambien los nombres en base a los km.
    
    int max_prod = vpos[nprod - 1];  //posicion del producto con mas km
    
    cout << "Cantidad de entregas para el tipo de producto " << productos[max_prod] << ": " << entregas_producto[max_prod] << endl;

    archi.close();
    return 0; 
}