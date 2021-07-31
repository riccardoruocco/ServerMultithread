#include "procedure.h"
#include "semafori.h"

void InstanziaCode(int& IdCodaInvio,int& IdCodaRicezione){

	int ChiaveCodaInvio;
	int ChiaveCodaRicezione;


	ChiaveCodaInvio=ftok(".",'a');
	ChiaveCodaRicezione=ftok(".",'b');

	IdCodaInvio=msgget(ChiaveCodaInvio,IPC_CREAT|IPC_EXCL|0664);
	if(IdCodaInvio==-1){
		IdCodaInvio=msgget(ChiaveCodaInvio,0|0664);
	}
	if(IdCodaInvio==-1){
		printf("\nErrore msgget CodaInvio\n");
		_exit(0);
	}

	IdCodaRicezione=msgget(ChiaveCodaRicezione,IPC_CREAT|IPC_EXCL|0664);
	if(IdCodaRicezione==-1){
		IdCodaRicezione=msgget(ChiaveCodaRicezione,0|0664);
	}
	if(IdCodaRicezione==-1){
		printf("\nErrore msgget CodaRicezione\n");
		_exit(0);
	}
}
void RimuoviCode(int& IdCodaInvio,int& IdCodaRicezione){
	msgctl(IdCodaInvio,IPC_RMID,NULL);
	msgctl(IdCodaRicezione,IPC_RMID,NULL);
}
void CostruisciMessaggioDaInviare(msg& m,int valore1,int valore2){
	int MioPid=getpid();	

	m.msgtype=1;
	m.pid=MioPid;
	m.valore1=valore1;
	m.valore2=valore2;
}
void InviaMessaggio(msg& m,int IdCoda){
	msgsnd(IdCoda,(void*)&m,sizeof(msg)-sizeof(long),0);
}
void RiceviMessaggio(msg& m,int IdCoda,int mittente){
	msgrcv(IdCoda,(void*)&m,sizeof(msg)-sizeof(long),mittente,0);
}
void UtenteInserisceValori(int& v1,int& v2){
	printf("\nBuongiorno\n");
	printf("\nPrego inserire il primo valore:");
	scanf("%d",&v1);
	printf("\nPrego inserire il secondo valore:");
	scanf("%d",&v2);

}
void StampaRisultato(int risultato){

	printf("\nIl risultato è: %d \n",risultato);
}
void* consuma(void* p){
	msg mRisposta;
	buf* b;

	b=(buf*)p;
	//costruiamo il messaggio di risposta
	mRisposta.msgtype=b->pid;
	mRisposta.pid=b->pid;
	mRisposta.valore1=b->valore1;
	mRisposta.valore2=b->valore2;
	mRisposta.risultato=(b->valore1)*(b->valore2);

	pthread_mutex_lock(&(b->mutex));
	InviaMessaggio(mRisposta,b->idCoda);
	pthread_mutex_unlock(&(b->mutex));
	
	free((void*)b);
	pthread_exit(0);
}




