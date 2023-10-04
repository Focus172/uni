# Week 3 - Assignment - Question 2
In the code on the first page of this week’s notes, write the output of each of the
five “cout” statements in the main function. Give justification of each output value. One
point per statement

## The First Statement
```cpp
int x(1), y(-1);
int main() {
    cout << x++ << ", " << ++y << endl;
    // -- cut --
```

This will write the out put of x and one more than y. In this scope, x and y are
only defined in the global scope. So this will output "1, 0\n" and the value of
x and y will be 'x=2;y=0'.

## The Second Statement
```cpp
{
    int x(10);
    cout << x++ << ", " << ++y << endl;
}
```

This will do the same incrementation of x and y put as this is in a new scope it
will use the new value of x. As such it will output "10, 1\n" and in the global
scope `x=2;y=1`.

## The Third Statement
```cpp
value(x, y);
cout << x++ << ", " << ++y << endl;
```

`value` is a function that take value by value. Withing it no global variables
are changed. As such its contents can be ignored. X and y are incremented in the
same way as prior loops. There for the output is "2, 2\n" and `x=3;y=2` in the
global scope.

## The Fourth Statement
```cpp
reference(x, y);
cout << x++ << ", " << ++y << endl;
```

The `reference` function takes mutable references to x and y so lets look at 
its content.

```cpp
void reference(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
    a *= x;
}
```
In this funtion the value of the two variables are swaped and then a
(priviously b) is multiplied by the global x. In this case a is the global x.
By the third line of this function `a=y=2'b=x=3`. So the final line translates
to `x=2*2`. There fore at the end of the function `x=4;y=3`. Therefore the line,
outputs "4, 3\n".

# The Fith Statement
```cpp
reference(x, y);
cout << x++ << ", " << ++y << endl;
```

This the same code as the fourth statement. As such it is left as an exersices 
to the reader to prove the output is "9, 4\n".
