# Ass3
Our implementation:
As we focused our efforts in seperating code parts responsibility areas', our code is designed to disconnenct the dependence of the client and the server in one another. While the client mostly operates as a communicator between the server and the user, most of the code program operation located in the server. In the server we placed the commands, which polymorphiclly proggrammed, The CLI and the ability to control the data and the settings.  
Each command extends Abstract command class and operate as needed in the excercise. 
In order to quickly run, we support many clients connenction by many threads, a thread to a client.

Note: We both have equally worked on this, from convenience considerations Noam has uploaded all files.
