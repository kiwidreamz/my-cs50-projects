import cs50

height = cs50.get_int("Height: ")

# checking input is valid
while True:
    if int(height) < 9 and int(height) > 0:
        break
    else:
        height = input("Height: ")

# turning input into integer
a = int(height)

# loop
for y in range(a):
    print((a - 1 - y) * " ", end='')
    print((y + 1) * "#")
