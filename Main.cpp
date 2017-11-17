#include <iostream>
using namespace std;

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

 
int main() { 
	inodo.setInodo(1001);
	cout << inodo.getInodo() << endl;
   	direntry.setNinodo(1002);
	cout << direntry.getNinodo() << endl;
 
   return 0; 
}
