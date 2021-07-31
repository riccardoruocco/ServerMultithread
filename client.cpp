#include "procedure.h"


int main(int argc,char* argv[]){

	int IdCodaInvio;
	int IdCodaRicezione;
	int MioPid;
	msg messaggioDaInviare;
	msg messaggioRicevuto;
	int valore1;
	int valore2;
	


	MioPid=getpid();
	InstanziaCode(IdCodaInvio,IdCodaRicezione);
	UtenteInserisceValori(valore1,valore2);
	CostruisciMessaggioDaInviare(messaggioDaInviare,valore1,valore2);	
	InviaMessaggio(messaggioDaInviare,IdCodaInvio);
	RiceviMessaggio(messaggioRicevuto,IdCodaRicezione,MioPid);
	if((messaggioRicevuto.valore1!=-1) && (messaggioRicevuto.valore2!=-1)){
	StampaRisultato(messaggioRicevuto.risultato);
	}
	
	return 0;
}
