all:server

server:client server.o procedure.o 
	g++ -pthread -o server server.o procedure.o 

client:client.o procedure.o 
	g++ -pthread -o client client.o procedure.o 

client.o:client.cpp
	g++ -c -g client.cpp

server.o:server.cpp
	g++ -c -g server.cpp

procedure.o:procedure.cpp 
	g++ -c -g procedure.cpp 
	


clean:
	rm -f ./server
	rm -f ./client
	rm -f *.o
	rm -f *~
