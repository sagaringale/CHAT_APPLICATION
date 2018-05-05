

#  CHAT_APPLICATION_project 

# Message chat application

This project was generated with [C Lang]


#### AUTHOR:

- [Sagar Ingale](https://github.com/sagaringale "Sagar's github profile")


#### DESCRIPTION:
			


# Environment: 
		C Lang.

# Tools: 
	        linux, vim


# Project Description:
			
Folder contains the listner.c, sender.c, whatsapp.c and resolver.txt files.
It sends the message to each other by finding their ip addresses starting at 196.168.43 and write them 
in the file resolver, and then whatsapp program use that file to chat with another machines or users.

Neccessary Database :
    - sqlite3 on linux platform


#### Runing Application:
 
#	- Open terminal.
	Steps to execute project :-
1. run make command in 1st machine
2. run make command in 2nd machine
3. run ./whatsapp on both the machine
4. put the choice with whome you want to chat like 2,3 and so on.

Verify messages by checking in the database :-
using following commonds on terminal: -
$ sqlite3 sagar.db
> select * from messages;


	


Note: Make sure your in project directory.




# CHAT_APPLICATION
