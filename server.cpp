#include "procedure.h"
#define TUTTI 0
#define DIM 1000
int main(int argc,char* argv[]){

	int IdCodaInvio;
	int IdCodaRicezione;
	pthread_attr_t attributo;
	pthread_t Thread_Server[DIM];
	buf* b;
	int numeroT;



	numeroT=0;

	pthread_attr_init(&attributo);
	pthread_attr_setdetachstate(&attributo,PTHREAD_CREATE_JOINABLE);
	InstanziaCode(IdCodaInvio,IdCodaRicezione);
	
	while(1){
		
		msg NuovoMessaggio;
		RiceviMessaggio(NuovoMessaggio,IdCodaInvio,TUTTI);



		b=(buf*) malloc(sizeof(buf));
		//inizializziamo il monitor		
		pthread_mutex_init(&(b->mutex),0);


		b->pid=NuovoMessaggio.pid;
		b->valore1=NuovoMessaggio.valore1;
		b->valore2=NuovoMessaggio.valore2;
		b->idCoda=IdCodaRicezione;

		//verifico se è il terminatore
		if((NuovoMessaggio.valore1 == -1) && (NuovoMessaggio.valore2 == -1))
		{
			NuovoMessaggio.msgtype=NuovoMessaggio.pid;
			InviaMessaggio(NuovoMessaggio,IdCodaRicezione);

			printf("\nTerminatore ricevuto,inizio procedure di terminazione\n");
			for(int i=0;i<=numeroT;i++){
				pthread_join(Thread_Server[numeroT],0);
			}
			pthread_attr_destroy(&attributo);
			pthread_mutex_destroy(&(b->mutex));
			sleep(5); //do il tempo ai client di consumare gli ultimi messaggi
						
			RimuoviCode(IdCodaInvio,IdCodaRicezione);
			exit(0);
		}
		pthread_create(&(Thread_Server[numeroT]),&attributo,consuma,(void*)b);
		numeroT=numeroT+1;


	}
	return 0;
}
