# HW 1: Social Network Foundations 
Due Apr 11 by 11:59pm Points 100
The Social Network

The assignments in this class are likely larger than you're used to, and I expect you to deliver code to my specifications.  For each assignment, before you start coding, first read the entire assignment carefully at least once.  I suggest you take notes of important points or questions as you do this.  Remember, one of the goals of this class is for you to mature as a programmer, and the ability to follow instructions in a detail-oriented manner is vital to success as a programmer. For this first assignment, I have provided tips at the bottom to help you get started.

In this assignment you will use C++ classes to model a social network, allowing users to be added, friend connections made, etc.

In this assignment you will:

Create your own C++ classes
Use File I/O to read/write text files containing structured data (records)
Understand the abstract representation of graphs (vertices=Users, edges=Friend connections)
Note: In our system edges are ‘undirected’ meaning if I’m a friend with you, you are a friend with me. Thus, when you add a friend connection from user1 to user2, be sure to add the connection from user2 to user1.  Other problems using graphs may require ‘directed’ edges. 


Defining a File Format:
This program requires you to use File I/O techniques to read and write the user database from and to a file. Whenever we write a file containing structured data we need to define a file format (syntax) so we understand how to parse the file. We will represent all information as ASCII text and use the format specified below.
```

1: single number representing how many users are in the database
2: id_0
3: <TAB>user_name
4: <TAB>birth year
5: <TAB>zip code
6: <TAB>ids of friends (separated by spaces) … …
n-4: id_k
n-3: <TAB>user_name
n-2: <TAB>birth year
n-1: <TAB>zip code
n: <TAB>ids of friends (separated by spaces)
```

Here is an example fileLinks to an external site..

We further require that in our file, the users are numbered 0,1,2,...,n-1, where n is the number of users, and the users listed in increasing order of id. So id_0 is always 0, id_1 is always 1, etc.

Note: a <TAB> character is represented as ‘\t’ in C/C++. Note: if you are having issues recognizing tabs, and you want to make more input files by hand, you can use copy-paste from the sample file to create more tab characters.

 

Problem Description:
0a. Important requirements
Please implement the methods and fields exactly as described. I am using an autograder and if you name methods incorrectly or use the wrong type, your code will not work.  You may include additional private methods if you desire.  Global variables must not be used for this project.
Please include pre-condition and post-condition comments for each method.  Here is a file with examples of such comments.Links to an external site.
Create separate header and class files for each class.  Note that we are not working with template classes, so it is fine to separate the method definitions into a separate file.
You may NOT "using namespace std;" in your header or class files.  You may do so in your main file.
0b. Autograder troubleshooting
I will check your code's correctness with an autograder. Passing the autograder tests counts for a significant part of your grade. If your code is not compiling on the autograder, try the following

Make sure you have followed the directions. In particular, make sure your files are named correctly (user.h, NOT User.h), that your methods are named correctly (getZip, NOT getZipCode, NOT get_zip, NOT getZip_), that your classes are named correctly (class User, NOT class user) and that your methods have the correct signature (User constructor takes the correct number of arguments).
Make sure you have all the #include's you need. #include <vector>, #include <set>, etc. Sometimes your machine #include libraries for you, even if you did not specify them, but the autograder may not.
Make sure you are not using any syntax beyond C++11. The autograder only compiles with -std=c++11.
Make sure you are using header guardsLinks to an external site. for your user.h and network.h files.
You can find the autograder tests on GitHubLinks to an external site.. To run the tests locally, copy the tests into your folder, and run g++ test_name.cpp your_file(s).cpp. Here are two examples: 

g++ test_user_1.cpp user.cpp

g++ test_network_.cpp user.cpp network.cpp
Note that test_user_1.cpp only tests user.cpp, so you only need to compile it with user.cpp.  

0c. Hints for getting started: Break this into pieces. Consider the following approach to build up your program:
Write the user.h and user.cpp files with appropriate User methods
Make sure it compiles and runs. Write a small program to test your code.
Submit your user.h and user.cpp files on Gradescope to see if they pass the tests. Fix any bugs.
Write the network.h and network.cpp files implementing the methods to add users.
Write a simple main program that implements the Menu system but with just the options to add users and print all users, and quit.
Continue to add in methods of the Network class (add friend connections, delete friend connections, print all friends of a user) one at a time and implement that option in the menu system, testing each one individually before moving on to the next.
Lastly, implement the File I/O capability to read in the database from a file or write it back out to a file. It might help you to use stringstreams and the getline(istream, string) function to do your parsing of the database file.
Run your program. You can enter menu options manually to test certain features of your program.
Ensure all commands work and that you can write the updated database to a new file. Inspect that file to ensure its format and data are correct. Try loading it up in a new run of the program. 
1. Define the User Class.
An overview is given in the diagram below, where + denotes methods, – denotes fields, and the return type is give after the :   All fields should be private.  Here are more detailed descriptions of User’s methods and fields.

User
+ User(), User(...)
+ addFriend(int id) : void
+ deleteFriend(int id) : void
+ accessors (getters)
- id_ : int
- name_ : string
- year_ : int
- zip_ : int
- friends_ : set<int>
 

2.  Define a Network class.
Its field should be private.  Here are more detailed descriptions of Network’s methods and fields.

Network
+ Network()
+ addUser(User*) : void
+ addConnection(string s1, string s2) : int
+ deleteConnection(string s1, string s2) : int
+ getId(string name) : int
+ readUsers(char* fname) : int
+ writeUsers(char *fname) : int
+ numUsers() : int
+ getUser(int id): user*
- users_:vector<User*> 
Hint: consider using stringstream for readUsers

3.  Test your code
At this point, you can test your code. You can check your code's correctness on the Gradescope autograder. Submit your user.h, user.cpp, network.h, network.cpp files on Gradescope as if you were submitting your assignment. Note that, once you finish the assignment, you will need to resubmit with all of your code files. You can resubmit as many times as you like. Passing the autograder tests counts for a significant part of your grade. I have made the autograder tests available onlineLinks to an external site. in case you'd like to run the tests on your own. If your code works on your computer but not on Gradescope, see the autograder troubleshooting above.

4.  Write a main program
This program should create a Network object and then read Users data from a text file whose name is given by the terminal user. Please name the file social_network.cpp. You must use argc and argv for this.  (If you are not familiar with this, compile and run this basic programLinks to an external site.) From the command line, you should run
./myExecutable users.txt
where myExecutable is replaced with the name of your executable (e.g. a.out, a.exe). The program should then loop through the progression of displaying a menu of options, accepting the user input, and processing the option. The menu options should be as follows. Your menu must accept the Option numbers indicated below.

Here are the 5 actions your program should support, with examples of their use.

Option 1. Add a user.
When chosen the user should provide their name (both first and last), birth year, and zip code input on the same line. A new user is initialized with no friends. Example (where > represents the prompt).

> 1 Jason Chen 2001 95053
Option 2. Add friend connection.
When chosen the user should provide the two usernames to make friends. If a user does not exist, print an error message and continue.

> 2 Aled Montes Sandhya Krish
Option 3. Delete friend connection.
When chosen the user should provide the two usernames whose friend relationship should be deleted. If a user does not exist or the Users are not friends, print an error message and continue.

> 3 Aled Montes Leo Griffin
Option 4. Print users.
Print the id and name of the users in the social network, one user per line.

> 4
Here is example outputLinks to an external site..

Note: Here, you do NOT need to write to a file. That is done in Option 6, and you write it in a different format.

Option 5. Print Friends
When chosen, the user should provide a user's name and then your program should print the ids and names of the friends of that user, one user per line. If the user does not exist, print an error message and continue.

> 5 Haaris George
 Here is example outputLinks to an external site..

Option 6. Write to file.
When chosen, the user should provide a filename to write the user data to. Your program should write the user data to the specified file given by the user in the same format as the input file. E.g.,

> 6 users_new.txt
Your program should print the number of users written to a file if successful, or an error message if not successful.

Option 7, 8, 9, ... . Exit the program.
Your program should exit the program on ANY invalid command number (i.e. -1, 7, 8, etc.)

-If any of your functions returns an error code, please print an appropriate error message to the screen and then return to the menu and accept more commands.

5. Style
Ensure your code is clear and readable. See the Code Style Guide for a rubric.

6. Short Answer Questions
Answer the following questions in a .txt file. Write at most two sentences for each question. With the exception of Question 3, these questions should all be review from your previous CS classes.

In the Network class, we stored the users as a vector of User pointers, rather than a vector of Users. Explain one main advantage of this.
In the User class, the getFriends returns a reference to the set of friends. Explain the main advantage the returning a reference has over returning the set without reference.
Explain one main advantage of storing the friends as a set, rather than a vector, in the User class.
Explain what are header guards. In particular, you should explain (1) why #ifndef, #define, and #endif are used and (2) how they work.
You might have tried implementing readUsers by pushing pointers to Users allocated on the stack, rather than pointers to Users on the heap, such as below. Explain why this will not work.
// Does not work
User u (id, name, zip, year, friends);
users_.push_back(&u);
6. Using big-O notation, in terms of the number of vertices n and/or the number of edges m, describe the runtime of the following methods: User::addFriend, Network::addConnection, Network::deleteConnection, Network::numUsers.

7. In hours, (approximately) how much time did you spend on this assignment? (there are no wrong answers)

Deliverables

Upload user.h, user.cpp, network.h, network.cpp, your main file social_network.cpp, and your .txt with your short answer questions.

(c) Redekopp, Linnell, Li

