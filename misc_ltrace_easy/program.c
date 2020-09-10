#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
	char* flap = "my_m0";
	char* a = "ther_";
	char* why = "could_d0";
	char* e = "_3asy";
	char* d = "_stuff";
	char *f = "_lik3_th15";
	char* well = "his";
	char* no = "_t";
	char* stonk = "m_";
	char* b = "st0rm";
	char* c = "can_d0";
	

	char* pass1 = "p4ssword";
	char* pass2 = "myst3ry";
	char* pass3 = "s3cr3et";
	char* pass4 = "hesl0";
	char* pass5 = "open_sesam3";
	char* pass6 = "mel0n";
	char* pass7 = "cl4ssified";
	char* pass8 = "hidd3n";
	char* pass9 = "l33tp4ssw0rdb0i";

	char* vec = "id";

	char heslo[9];

	if(argc != 2){
		printf("Usage: executable <password>");
	}
	else{
		strcat(heslo, pass4);
		strcat(heslo, vec);

		if(strcmp(argv[1], heslo) == 0){
			printf("Well done the flag is avastCTF{%s%s%s%s%s}", flap, stonk, why, no, well);
		}
		else{
			printf("Wrong");
		}
	}
	return 0;
}
