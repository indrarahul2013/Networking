#include<bits/stdc++.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fstream>
#include<unistd.h> 

using namespace std;
#define BACKLOG 5
#define SIZE 100
string getFileContents (ifstream&);

char ip[INET6_ADDRSTRLEN];
int len;

class sock{
public:
	
	struct sockaddr_in addr;
	socklen_t addr_size;
 	struct addrinfo hints, *res;
 	int sockfd, comm,yes=1,check;

	void gainfo(char ip[INET6_ADDRSTRLEN], char *port)
	{
		memset(&hints, 0, sizeof(hints));
 		hints.ai_family = AF_INET;
 		hints.ai_socktype = SOCK_STREAM;
 		hints.ai_flags = AI_PASSIVE;

 		if(getaddrinfo(ip, port, &hints, &res)!=0)
 			{
 				cout << "Error getaddrinfo()\n";
 				exit(1);
 			}

	}

	void create_socket()
	{
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if(sockfd<0)
		{
			cout << "Error Creating Socket\n";
			exit(1);
		}
	}

	void sock_connect()
	{
		if(connect(sockfd,res->ai_addr,res->ai_addrlen)==-1)
		{
			cout << "Error Connecting\n";
			exit(1);
		}
	}


	
	void sock_close()
	{
		close(sockfd);
	}

	int sock_recv(char buf[])
	{
		check = recv(sockfd,buf,SIZE-1,0);
		if(check==-1)
		{
			"Error Receiving";
			
		}	
		buf[check]='\0';
		return check;
	}

	void sock_send(char *msg)
	{
		if(send(sockfd,msg,strlen(msg),0)==-1)			// Have to implement lost data logic. 
			cout << "Not Sent ! Error Sending\n";
	}


	
};


int main()
{
	
	char port[5];
	char new_msg[100],buf[100];
	string msg;
	ifstream Reader ("k.txt");
	string Art = getFileContents (Reader);
	cout << Art << endl;
	cout << "Enter IP address : ";
	cin >> ip;
	cout << "Enter the Port No : ";
	cin >> port;
	cout << "Connecting......." << endl;

	sock a;
	a.gainfo(ip,port);
	a.create_socket();
	a.sock_connect();
	cout << "Connection Established with : " << ip <<endl <<endl;

	cout << "Enter your message : \n";
	cin >> new_msg;
	// cout << new_msg;
	a.sock_send(new_msg);
	a.sock_recv(buf);
	cout << ip << " says back : " << buf <<endl; 
	a.sock_close();
	return 0;
}




string getFileContents (ifstream& File)
{
    string Lines = "";        
    
    if (File)                      
    {
	while (File.good ())
	{
	    string TempLine;                  
	    getline (File , TempLine);        
	    TempLine += "\n";                      
	    
	    Lines += TempLine;                     
	}
	return Lines;
    }
    else                           
    {
	return "ERROR File does not exist.";
    }
}