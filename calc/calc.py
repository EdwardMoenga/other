# Program make a simple calculator
import math

# This function adds two numbers
def add(x, y):
    return x + y

# This function subtracts two numbers
def subtract(x, y):
    return x - y

# This function multiplies two numbers
def multiply(x, y):
    return x * y

# This function divides two numbers
def divide(x, y):
    return x / y

# This function gives the powers of two numbers
def power(x, y):
    return math.pow(x, y)

# This function gives the factorial of a number
def factorial(x):
    return math.factorial(x)

# This function gives log to base 10 of a number
def log10(x):
    return math.log(x, 10)

# This function gives the natural log of a number
def nlog(x):
    return math.log(x)

print("Select operation.")
print("1.Add")
print("2.Subtract")
print("3.Multiply")
print("4.Divide")
print("5.Power")
print("6.Factorial")
print("7.Log")
print("8.Ln")
print("9.Quit")

while True:
    # take input from the user
    choice = input("Enter choice(1/2/3/4/5/6/7/8/9): ")

    # check if choice is one of the five options
    if choice in ('1', '2', '3', '4', '5', '6', '7', '8', '9'):
        if choice == '9':
            break
        elif choice in ( '6', '7', '8'):
            num1 = float(input("Enter number: "))
        else:
            num1 = float(input("Enter first number: "))
            num2 = float(input("Enter second number: "))

        if choice == '1':
            print(num1, "+", num2, "= ", add(num1, num2))

        elif choice == '2':
            print(num1, "-", num2, "= ", subtract(num1, num2))

        elif choice == '3':
            print(num1, "*", num2, "= ", multiply(num1, num2))

        elif choice == '4':
            print(num1, "/", num2, "= ", divide(num1, num2))

        elif choice == '5':
            print(num1, " power ", num2, "= ", power(num1, num2))

        elif choice == '6':
            print(num1, "! =", factorial(num1))

        elif choice == '7':
            print("Log10", num1, "= ", log10(num1))                       

        elif choice == '8':
            print("Ln", num1, "= ", nlog(num1))

    else:
        print("Invalid Input")