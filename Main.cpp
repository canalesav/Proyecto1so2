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
//	*/
}inodo;

struct directoryEntry{
	string nombre;
	short t_nombre;
	short n_inodo;
	short t_registro;
	void setNombre(string nom){
		nombre = nom;
	}
	string getNombre(){
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
    bool inodo[128];
}i_bitmap;
// 8KB
struct BitmapDatos{
    bool datos[8192];
}d_bitmap;
// 144KB
struct TablaInodos{
    iNodoEntry inodos[1024];
} t_inodos;

//Datos

void CrearArchivo(){
    ofstream archivo("archivo.dat", ios::binary);
    for(int i=0; i<128; i++){
        i_bitmap.inodo[i] = false;
    }
    for(int i=0; i<8192; i++){
        d_bitmap.datos[i] = false;
    }
    cout<<"tamaño B_Datos: "<<sizeof(BitmapDatos)/1024<<" KB"<<endl;
    cout<<"tamaño B_iNodos: "<<sizeof(iNodoBitmap) << " B" <<endl;
    cout<<"tamaño iNodoEntry: "<<sizeof(iNodoEntry)<< " B"<<endl;
    cout<<"tamaño T_Inodos: "<<sizeof(TablaInodos)/1024<<" KB"<<endl;
    int total = (sizeof(TablaInodos)+sizeof(iNodoBitmap)+sizeof(BitmapDatos));
    cout<<"Total reservado: "<<(total)<<" B"<<endl;
    int t_archivo = 262144*1024;
    cout<<"tamaño Datos: "<<(t_archivo-total)<<" KB"<<endl;
    char datos[3353496];
    //cout<<"Datos: "<<sizeof(datos)<<endl;

    archivo.write((char*)&d_bitmap, sizeof(BitmapDatos));
    archivo.write((char*)&i_bitmap, sizeof(iNodoBitmap));
    archivo.write((char*)&t_inodos, sizeof(TablaInodos));
    for(int i=0; i<80; i++){
        archivo.write((char*)&datos, sizeof(datos));
    }
    archivo.close();
}
int main() {
    CrearArchivo();
   return 0;
}