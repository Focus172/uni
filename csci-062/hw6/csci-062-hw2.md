# Problem 0
(n,e) = (8876044532898802067,3267000013)
c = 4504511121101132917

## Step 1
```wolfram
factor 8876044532898802067
```
p = 1500450271
q = 5915587277

## Step 2
```wolfram
lcm(1500450271 -1, 5915587277 - 1)
```
h = 4438022262741382260

## Step 3
```wolfram
solve d * 3267000013 = 1 mod 4438022262741382260
```
d = 296676241933172437

## Step 4
c^d % n
```wolfram
4504511121101132917^296676241933172437 mod 8876044532898802067
```
m = 4242424242424242424

# Problem 1
Draw the stack frame for the auth() function.

```
high address
+-------------------------+
|                         |
|                         |
+-------------------------+
|                         |
|                         |
+-------------------------+
|                         |
|                         |
|                         |
+-------------------------+
|                         |
|                         |
+-------------------------+
|                         |
|                         |
+-------------------------+
low address
```

Which line of code has the buffer overflow vulnerability?
10: gets(password);

What is the minimum number of As you need to input in order to get Access Granted?
17

How many bytes are between the addresses of the beginning of password and
auth_flag variables?
16

How many bytes are needed to store auth_flag variable? 
4

What is the value of the auth_flag variable?
-1056964607

Print out the bytes of memory from the starting address of password, using the command, x/40xb &password, and paste a screenshot into your deliverable doc. Note that the hex value for ‘A’ is 0x41 and the int value for 'A' is 65.
See explanation at end of problem 2

Explain what has happened and why you were Granted Access without knowing the
password.
The value of the `auth_flag` was changed to be non zero.

Run again with one additional A. What is the value of auth_flag now? Where does this number come from?
static_cast<int>(0x41410000) == -1052704768

# Problem 2
What is the difference between the addresses of password and auth_flag?
16

How can you change the string from Problem 1 to also get Access Granted for this problem?
Change the final 'A' to 0x01

file: bytes2.txt
```
AA AA BB BB CC CC DD DD 01
```
Working screenshot:
On my computer, my compile chooses to reorder stack variables so that the int
values are always placed at a lower address than the buffer. That means that
the buffer cannot write into other stack variables. This can be fixed by 
creating a struct with the correct layout like such:
```cpp
struct buffer {
    char password[16];
    int auth_flag;
};

int auth() {
  volatile buffer buf = buffer{
      .password = "",
      .flag = 0
  };
  gets(buf.password);

  if (strcmp((char *)password, "brilling") == 0)
    auth_flag = 1;

  return buf.flag;
}
```


# Problem 3
What is the memory address of the granted() function?
0x401150

What is the address in memory where the start of the return address is stored? What is the value of the return address?
0x7fffffff8ff0: 0x004052a0

How many bytes are there between the address of the start of password and the address of the start of the return address?
16

file: bytes3.txt
```
AA AA BB BB CC CC DD DD 00 40 11 50
```
![[hw6-part3-demo.png]]
