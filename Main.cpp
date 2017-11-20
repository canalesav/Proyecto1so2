#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

// 144 bytes
struct iNodoEntry{
    char m_acceso;
    short i_nodo;
    int l_archivo,f_creo,f_mod,t_archivo;
    long d_directo[12];
    long p_isimple,p_idoble,p_itriple;

    void setMacceso(char a){
        m_acceso = a;
    }
    char getMacceso(){
        return m_acceso;
    }
    void setInodo(short a){
        i_nodo = a;
    }
    short getInodo(){
        return i_nodo;
    }
    void setLarchivo(int a){
        l_archivo = a;
    }
    int getLarchivo(){
        return l_archivo;
    }
    void setFcreo(int a){
        f_creo = a;
    }
    int getFcreo(){
        return f_creo;
    }
    void setFmod(int a){
        f_mod = a;
    }
    int getFmod(){
        return f_mod;
    }
    void setTarchivo(int a){
        t_archivo = a;
    }
    int getTarchivo(){
        return t_archivo;
    }
    void setDdirecto(long a[]){
        //d_directo = a;
    }
    long* getDdirecto(){
        return d_directo;
    }
    void setPisimple(long a){
        p_isimple = a;
    }
    long getPisimple(){
        return p_isimple;
    }
    void getPidoble(long a){
        p_idoble = a;
    }
    long getPidoble(){
        return p_idoble;
    }
    void setPitriple(long a){
        p_itriple = a;
    }
    long getPitriple(){
        return p_itriple;
    }
//  */
}inodo;

struct directoryEntry{
    char *nombre;
    short t_nombre;
    short n_inodo;
    short t_registro;
    void setNombre(char* nom){
        nombre = nom;
    }
    char* getNombre(){
        return nombre;
    }
    void setTnombre(short t){
        t_nombre = t;
    }
    short getTnombre(){
        return t_nombre;
    }
    void setNinodo(short t){
        n_inodo = t;
    }
    short getNinodo(){
        return n_inodo;
    }
    void setTregistro(short t){
        t_registro = t;
    }
    short getTregistro(){
        return t_registro;
    }

}direntry;

// 128 B
struct iNodoBitmap{
    bool inodo[1024];

    int getInodoLibre(){
        for(int i=0; i<1024; i++){
            if(inodo[i] == false){
                return i;
            }
        }
        return -1;
    }
    int getInodo(int numero){
        return inodo[numero];
    }
    void initBitmapI(){
        for(int i=0; i<1024; i++){
            inodo[i] = 0;
        }
    }
}i_bitmap;
// 8KB
struct BitmapDatos{
    bool datos[8192];

    int getDatoLibre(){
        for(int i=0; i<1024; i++){
            if(datos[i] == false){
                return i;
            }
        }
        return -1;
    }
    int getDato(int numero){
        return datos[numero];
    }
    void initBitmapD(){
        datos[0] = 1;
        for(int i=1; i<1024; i++){
            datos[i] = 0;
        }
    }
}d_bitmap;

// 144KB
struct TablaInodos{
    iNodoEntry inodos[1024];
} t_inodos;

//Datos
struct Cluster{
    directoryEntry direntry;
    char* datos;

    void setDatos(char *dat){
        datos = dat;
    }
};
void CrearArchivo(){
    ofstream archivo("archivo.dat", ios::binary);
    for(int i=0; i<1024; i++){
        i_bitmap.inodo[i] = false;
    }
    d_bitmap.datos[0] = true;
    for(int i=1; i<8192; i++){
        d_bitmap.datos[i] = false;
    }
    cout<<"tamaño B_Datos: "<<sizeof(BitmapDatos)/1024<<" KB"<<endl;
    cout<<"tamaño B_iNodos: "<<sizeof(iNodoBitmap) << " B" <<endl;
    cout<<"tamaño iNodoEntry: "<<sizeof(iNodoEntry)<< " B"<<endl;
    cout<<"tamaño T_Inodos: "<<sizeof(TablaInodos)/1024<<" KB"<<endl;
    cout<<"tamaño dir_entry: "<<sizeof(directoryEntry)<<" B"<<endl;
    cout<<"tamaño: "<<sizeof(Cluster)<<"B"<<endl;
    int total = (sizeof(TablaInodos)+sizeof(iNodoBitmap)+sizeof(BitmapDatos));
    cout<<"Total reservado: "<<(total)<<" B"<<endl;
    int t_archivo = 262144*1024;
    cout<<"tamaño Datos: "<<(t_archivo-total)<<" KB"<<endl;
    //char datos[3353496];
    //cout<<"Datos: "<<sizeof(datos)<<endl;

    archivo.write((char*)&d_bitmap, sizeof(BitmapDatos));
    archivo.write((char*)&i_bitmap, sizeof(iNodoBitmap));
    archivo.write((char*)&t_inodos, sizeof(TablaInodos));
    //for(int i=0; i<80; i++){
    //    archivo.write((char*)&datos, sizeof(datos));
    //}
    archivo.close();
}
/*
struct Archivotxt{
    char nombre[30];
    char contenido[200];//este tamaño creo que es suficiente para contenido
    char tipo = 'rw';
};
*/
void cat_Escribir(char* nombre){

    string temp;
    getline(cin, temp, '\n');
    cout<<temp<<endl;
    char contenido[temp.length()];
    for(int i=0; i<temp.length(); i++){
        contenido[i] = temp[i];
    }
    char * temp1 = nombre;
    char * temp2 = contenido;
    cout<<"ingresado: "<<temp2<<endl;

    BitmapDatos datos;
    iNodoBitmap inodos;
    TablaInodos tabla;

    ifstream archivol("archivo.dat", ios::binary);
    archivol.read((char*)&datos, sizeof(BitmapDatos));
    archivol.read((char*)&inodos, sizeof(iNodoBitmap));
    archivol.read((char*)&tabla, sizeof(TablaInodos));

    int d_libre = datos.getDatoLibre();
    int i_libre = inodos.getInodoLibre();

    inodos.inodo[i_libre] = 1;

    tabla.inodos[i_libre].setMacceso('rw');
    tabla.inodos[i_libre].setInodo(i_libre);
    tabla.inodos[i_libre].setLarchivo(sizeof(Cluster));
    long ddirectos[12];
    /*
    if(d_libre == 0){
        ddirectos[0] = 160764;
    }*/
    for(int i=0; i<12; i++){
        ddirectos[i] = (d_libre+i)* 160764;
        datos.datos[d_libre+i] = 1;
    }
    cout<<"current_pos:"<<archivol.tellg()<<endl;
    tabla.inodos[i_libre].setDdirecto(ddirectos);
    int primera_dir = d_libre * 160764;
    archivol.close();
    cout<<"dir direction:"<<primera_dir<<endl;

    ofstream escribir("archivo.dat", ios::binary);
    cout<<"cur_inicial: "<<escribir.tellp()<<endl;
    escribir.write((char*)&datos, sizeof(BitmapDatos));
    escribir.write((char*)&inodos, sizeof(iNodoBitmap));
    escribir.write((char*)&tabla, sizeof(TablaInodos));
    cout<<"cur_inicial: "<<escribir.tellp()<<endl;
    escribir.seekp(0, ios::beg);
    escribir.seekp(primera_dir, ios::cur);
    cout<<"cur_pos_w: "<<escribir.tellp()<<endl;
    Cluster clu;
    clu.direntry.setNinodo(i_libre);
    char* nombre1= temp1;
    clu.direntry.setNombre(nombre1);
    clu.direntry.setTnombre(sizeof(nombre1));
    clu.direntry.setTregistro(sizeof(clu.datos));
    cout<<"char *: "<<sizeof(nombre1)<<endl;
    char * contenido1 = temp2;
    clu.setDatos(contenido1);
    cout<<"contenido: "<<clu.datos<<endl;
    cout<<"tamaño: "<<sizeof(clu)<<endl;
    escribir.write((char*)&clu, sizeof(Cluster));
    cout<<"cur_pos_d: "<<escribir.tellp()<<endl;
    escribir.close();


    Cluster clur;
    cout<<"tamaño: "<<sizeof(clur)<<endl;
    ifstream archivo2("archivo.dat", ios::binary);

    archivo2.seekg(primera_dir, ios::cur);
    cout<<"possicion e: "<<archivo2.tellg()<<endl;
    archivo2.read((char*)&clur, sizeof(Cluster));
    cout<<"inodo: "<<clur.direntry.getNinodo()<<endl;
    cout<<"nombre: "<<clur.direntry.getNombre()<<endl;
    cout<<"t_nombre: "<<clur.direntry.getTnombre()<<endl;
    cout<<"t_registro: "<<clur.direntry.getTregistro()<<endl;
    cout<<"datos: "<<clur.datos<<endl;
    cout<<"cur_pos_d: "<<archivo2.tellg()<<endl;

    archivo2.close();

}
void cat_Leer(char* nombre){
/*
    Cluster clur;
    cout<<"tamaño: "<<sizeof(clur)<<endl;
    ifstream archivo2("archivo.dat", ios::binary);

    archivo2.seekg(primera_dir, ios::cur);
    cout<<"possicion e: "<<archivo2.tellg()<<endl;
    archivo2.read((char*)&clur, sizeof(Cluster));
    cout<<"inodo: "<<clur.direntry.getNinodo()<<endl;
    cout<<"nombre: "<<clur.direntry.getNombre()<<endl;
    cout<<"t_nombre: "<<clur.direntry.getTnombre()<<endl;
    cout<<"t_registro: "<<clur.direntry.getTregistro()<<endl;
    cout<<"datos: "<<clur.datos<<endl;
    cout<<"cur_pos_d: "<<archivo2.tellg()<<endl;

    archivo2.close();
*/
}
void borrarArchivo(char* nombre){
    string temp;
    int busqueda=20;
    getline(cin, temp, '\n');
    cout<<temp<<endl;
    char contenido[temp.length()];
    for(int i=0; i<temp.length(); i++){
        contenido[i] = temp[i];
    }
    char * temp1 = nombre;
    char * temp2 = contenido;
    cout<<"ingresado: "<<temp2<<endl;

    BitmapDatos datos;
    iNodoBitmap inodos;
    TablaInodos tabla;

    ifstream archivol("archivo.dat", ios::binary);
    archivol.read((char*)&datos, sizeof(BitmapDatos));
    archivol.read((char*)&inodos, sizeof(iNodoBitmap));
    archivol.read((char*)&tabla, sizeof(TablaInodos));

    int d_libre = datos.getDato(busqueda);
    int i_libre = inodos.getInodo(busqueda);

    inodos.inodo[busqueda] = 0;

    tabla.inodos[busqueda].setMacceso(0);
    tabla.inodos[busqueda].setInodo(0);
    tabla.inodos[busqueda].setLarchivo(sizeof(0));
    long ddirectos[12];
    /*
    if(d_libre == 0){
        ddirectos[0] = 160764;
    }*/
    for(int i=0; i<12; i++){
        ddirectos[i] = (busqueda+i)* 0;
        datos.datos[busqueda+i] = 0;
    }
    cout<<"current_pos:"<<archivol.tellg()<<endl;
    tabla.inodos[busqueda].setDdirecto(ddirectos);
    int primera_dir = d_libre * 160764;
    archivol.close();
    cout<<"Se ha borrado "<<nombre<<"!"<<endl;

    ofstream archivo("archivo.dat", ios::binary);
    cout<<"tamaño B_Datos: "<<sizeof(BitmapDatos)/1024<<" KB"<<endl;
    cout<<"tamaño B_iNodos: "<<sizeof(iNodoBitmap) << " B" <<endl;
    cout<<"tamaño iNodoEntry: "<<sizeof(iNodoEntry)<< " B"<<endl;
    cout<<"tamaño T_Inodos: "<<sizeof(TablaInodos)/1024<<" KB"<<endl;
    cout<<"tamaño dir_entry: "<<sizeof(directoryEntry)<<" B"<<endl;
    cout<<"tamaño: "<<sizeof(Cluster)<<"B"<<endl;
    int total = (sizeof(TablaInodos)+sizeof(iNodoBitmap)+sizeof(BitmapDatos));
    cout<<"Total reservado: "<<(total)<<" B"<<endl;
    int t_archivo = 262144*1024;
    cout<<"tamaño Datos: "<<(t_archivo-total)<<" KB"<<endl;
    archivo.write((char*)&d_bitmap, sizeof(BitmapDatos));
    archivo.write((char*)&i_bitmap, sizeof(iNodoBitmap));
    archivo.write((char*)&t_inodos, sizeof(TablaInodos));
    archivo.close();
}

int main() {
    CrearArchivo();
    string comando;
    getline(cin, comando, '\n');
    cout<<"Ingresado:"<<comando<<endl;
    if(comando[0]=='c' && comando[1]=='a' && comando[2]=='t' && comando[4]=='>'){
        string temp;
        for(int i=6; i<comando.length(); i++){
            temp += comando[i];
        }
        //char *temp = nombre;
        cout<<"cat w"<<endl;
        char nombre[temp.length()];
        for(int i=0; i<temp.length(); i++){
            nombre[i] = temp[i];
        }
        cat_Escribir(nombre);
    }else if(comando[0]=='c' && comando[1]=='a' && comando[2]=='t'){
        string temp;
        for(int i=4; i<comando.length(); i++){
            temp += comando[i];
        }
        //char *temp = nombre;
        cout<<"cat r"<<endl;
        char nombre[temp.length()];
        for(int i=0; i<temp.length(); i++){
            nombre[i] = temp[i];
        }
        cat_Leer(nombre);
    }else if (comando[0]=='r' && comando[1]=='m'){
        string temp;
        for(int i=3; i<comando.length(); i++){
            temp += comando[i];
        }
        //char *temp = nombre;
        cout<<"rm"<<endl;
        char nombre[temp.length()];
        for(int i=0; i<temp.length(); i++){
            nombre[i] = temp[i];
        }
        borrarArchivo(nombre);
    }else if (comando[0]=='c' && comando[1]=='d'){
        string temp;
        for(int i=3; i<comando.length(); i++){
            temp += comando[i];
        }
        //char *temp = nombre;
        char nombre[temp.length()];
        for(int i=0; i<temp.length(); i++){
            nombre[i] = temp[i];
        }
        cout<<"cd "<<temp<<"\\"<<endl;
    }else{
        cout<<"comando incorrecto"<<endl;
    }
    //continuar con lo de los accesos al bitmap y demas para no tener problemas al buscar
   return 0;
}