#include<iostream>
#include<string.h>
#include"Process.h"
using namespace std;

int main() {
	Process unoProcess;
	bool flagEndUno = unoProcess.execute();
	if (!flagEndUno) {
		cout << "��Ϸ����δ֪���������˳���Ϸ" << endl;
		exit(0);
	}	

}