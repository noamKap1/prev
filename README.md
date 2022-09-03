# Ass3
Our implementation:
As we focused our efforts in seperating code parts responsibility areas', our code is designed to disconnenct the dependence of the client and the server in one another. While the client mostly operates as a communicator between the server and the user, most of the code program operation located in the server. In the server we placed the commands, which polymorphiclly proggrammed, The CLI and the ability to control the data and the settings.  
Each command extends Abstract command class and operate as needed in the excercise. 
In order to quickly run, we support many clients connenction by many threads, a thread to a client.

Note: We both have equally worked on this, from convenience considerations Noam has uploaded all files.

# compile and run:

(We used the program MobaXterm) Do and write the commands or actions in this order: Open two frames of the program. Write in one of them: mkdir folderName Write in both of them: cd folderName Download the files and copy it to the program inside the folder named folderName. In one of the frames write: cd server In the second one write: cd client In the frame which we written cd server we compile using the command "g++ *.cpp -std=c++11 -lpthread" and then run with the command:./a.out" Now in the second frame we compile using the command "g++ *.cpp -std=c++11" and then run with the command:./a.out

Note: we used the compile command "g++ *.cpp -std=c++11 -lpthread" instead of "g++ *.cpp -std=c++11" becuase the moba system printed and error which said that multithreading is not allowed with this command (it did compile and run with the new command).
Note: The output file is expected to be in the Client folder.
