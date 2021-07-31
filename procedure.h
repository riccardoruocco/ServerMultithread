#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>
#include<sys/wait.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>



typedef struct{
	long msgtype;
	int pid;
	int valore1;
	int valore2;
	int risultato;	
}msg;

typedef struct{
	int pid;
	int valore1;
	int valore2;
	int idCoda;
	pthread_mutex_t mutex;
}buf;


void InstanziaCode(int&,int&);
void RimuoviCode(int&,int&);
void CostruisciMessaggioDaInviare(msg& m,int valore1,int valore2);
void InviaMessaggio(msg& m,int IdCodaInvio);
void RiceviMessaggio(msg& m,int IdCoda,int mittente);
void UtenteInserisceValori(int&,int&);
void StampaRisultato(int);
void* consuma(void* p);




