``# ServerMultithread``

Si vuole realizzare in linguaggio C/C++ un processo Server che riceve,attraverso una coda di messaggi,una coppia di valori interi da uno o più processi client .
Il processo server per ogni messaggio ricevuto crea un nuovo thread,gli passa il messaggio  e poi si pone di nuovo in attesa di altri messaggi dallo stesso client o altri client.
Il processo server termina quando uno qualsiasi dei client invia la coppia di valori(-1,-1). 
Ciascun thread si occupa di moltiplicare i due valori fra loro e di restituire il risultato al client che ha richiesto l'elaborazione.
Ciascun client infine stampa a video il risultato.


1)copiare l'intero contenuto della cartella

2)aprire una shell nella cartella copiata e compilare l'applicazione con il comando
```c
$make
```
3)lanciare il processo server in background digitando nella shell
```c
$ ./server &
```


4)lanciare il client con il comando
```c
$./client
```

Aprendo più shell è possibile lanciare più client in contemporanea.
