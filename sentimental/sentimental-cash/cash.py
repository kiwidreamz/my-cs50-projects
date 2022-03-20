import cs50

# takes a float input
change_owed = cs50.get_float("How much change is owed? ")

# checking input is a positive number
while True:
    if change_owed > 0.0:
        break
    else:
        change_owed = cs50.get_int("How much change is owed? ")

# printing how much change is owed
print("Change owed: " + str(change_owed))

# converting to cents for easy calculation using only integers
cents_owed = round(change_owed * 100)

# initializing variables for later use
quarters, dimes, nickels, pennies = 0, 0, 0, 0
a, b, c = 0, 0, 0

# conditional statement checking if there are any quarters,
# how many of them and taking the rest (modulus) into variable a
if cents_owed / 25:
    quarters = cents_owed // 25
    a = cents_owed % 25

# conditional statement checking if there are any dimes,
# how many of them and taking the rest (modulus) into variable b
if a / 10:
    dimes = a // 10
    b = a % 10

# conditional statement checking if there are any nickels,
# how many of them and taking the rest (modulus) into variable c
if b / 5:
    nickels = b // 5
    c = b % 5

# conditional statement checking if there are any cents left and how many of them
if c / 1:
    pennies = c / 1

# adding up all the coins
minimum_amount_of_coins = int(quarters + dimes + nickels + pennies)

# printing out the final result
print(minimum_amount_of_coins)