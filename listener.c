#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sqlite3.h>
typedef struct socketData
{
    int listener_fd,conn_fd;
    struct sockaddr_in listener_addr, client_addr;
}socketData;





socketData * listenerSocket(int port) 
{
 socketData *sock;

 sock=(socketData *)malloc(sizeof(socketData));
 
 sock->listener_fd=socket(AF_INET,SOCK_STREAM,0);
    if(sock->listener_fd==-1)
    {
        perror("Unable to initiate listener socket");
        exit(1);
    }

 memset(&sock->listener_addr,'0',sizeof(sock->listener_addr));     //fill addr with '0'

 sock->listener_addr.sin_family = AF_INET;
 sock->listener_addr.sin_addr.s_addr = htonl(INADDR_ANY);
 sock->listener_addr.sin_port=htons(port);

 if(bind(sock->listener_fd , (struct sockaddr *) &sock->listener_addr , sizeof(sock->listener_addr) ) == -1)
 {
     fprintf(stdout,"Address Binding Failed");
     exit(1);
 }

 if(listen(sock->listener_fd,50) == -1)
 {
    fprintf(stdout,"Not Listening");
    exit(1);
 }


 return sock; 
}


int insertIntoDb(char *mess)
{
  sqlite3 *db;
   char *errMsg = 0;
// const char *mess = message.c_str();
  int rc;
  const char *sql;
  sqlite3_stmt *stmt;
  const char *pzTest;
  rc = sqlite3_open("sagar.db",&db);
   if( rc ) 
   {
     fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
     return(0);
   } 
   else {
	         sql = "CREATE TABLE if not exists messages("  \
         "mess_ID integer PRIMARY KEY  autoincrement," \
         "message  text );";

          /* Execute SQL statement */
          rc = sqlite3_exec(db, sql, NULL, 0, &errMsg);
   
          if( rc != SQLITE_OK ){
          fprintf(stderr, "SQL error: %s\n", errMsg);
          sqlite3_free(errMsg);
        } 
      sql = "insert into messages(message)\
             values (?)";
      rc = sqlite3_prepare(db, sql, strlen(sql), &stmt, &pzTest);
       if( rc == SQLITE_OK ) {
//     	cout<<"values inserted\n"; 
    	sqlite3_bind_text(stmt, 1, mess, strlen(mess), 0);
   	 // commit 
    	sqlite3_step(stmt);
    	sqlite3_finalize(stmt);
  }
   else
     printf("error\n");
       
  sqlite3_close(db);
} 
}

int main(int argc, const char *argv[])
{
    socketData *sock;
    sock=listenerSocket(8889);
    char username[20],msg[1024];
    int addrlen,i=-1;
    
    addrlen=sizeof(sock->client_addr);

    
    while(1)
    {
        sock->conn_fd=accept(sock->listener_fd , (struct sockaddr *) &sock->client_addr  , &addrlen );
            if(sock->conn_fd == -1)
            {
                perror("Unable to Accept Connection");
            }



        memset(msg,'\0',1024);
        read(sock->conn_fd,msg,1024);
        // fputs(msg,stdout);
        insertIntoDb(msg);
        printf("Sagar : %s",msg);


        close(sock->conn_fd);
   }

   return 0;
}


