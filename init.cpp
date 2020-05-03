#include <iostream>
#include <stdio.h>
using namespace std;

void introduce();
void inits(int* user_count);

int main() {
	int user_count;
	introduce();
	inits(&user_count);
	cout << user_count;	
}

void introduce() {
	cout << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "Olá :)" << endl;
	cout << endl;
	cout << "Este programa ira simular um protocolo de assinaturas multiplas." << endl;
	cout << "Para a simulacao serao criados uma AC, usuarios normais e um usuario admin." << endl;
	cout << "Todos os usuarios requesitarao um certificado para a AC e o usuario admin" << endl;
	cout << "ira escolher um documento para todos os usuarios assinarem." << endl;
	cout << "Quando todos tiverem assinado o documento, a assinatura sera verificada." << endl;
	cout << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << endl;
	cout << "Vamos la?" << endl << endl;
}

void inits(int* user_count) {
	cout << "Quantos usuarios devem existir? (Incluindo o admin)" << endl;
	cin >> *user_count;
	cout << endl;
	
	for (int i = 0; i < *user_count; ++i) {
		pid_t pid
		fork();
	}

}
