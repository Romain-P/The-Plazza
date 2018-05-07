### The Plazza

Epitech: The Plazza project, a file scrapper.  
Goal is to analyse files content, sent as command, and find data matching with a given pattern e.g EMAIL, IP ...

#### Technical

* Multi-processes using `posix-spawn` recalling the application.
* Multi-threads and safe using `mutex` and `shared_mutex` also.
* Scalable Network using `tcp sockets` to communicate with child processes
* Scalable project globally, easy to add new commands and re-use network as a library.

#### Extra
* Bruteforce files that look like xor ciphered -> decrypted and analysed

![sample](https://image.ibb.co/b99Pyn/Capture_d_cran_de_2018_05_07_09_32_15.png)