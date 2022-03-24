import cs50

# get input from user
text = cs50.get_string("Text: ")

text_length = len(text)

# initializing variables at 0 except words since the last word doesn't end with a space
words = 1
letters, sentences = 0, 0

# for loop incrementing our three variables
for i in range(text_length):
    if (ord(text[i]) >= 97 and ord(text[i]) <= 122) or (ord(text[i]) >= 65 and ord(text[i]) <= 90):
        letters = letters + 1
    elif (ord(text[i]) == 32):
        words = words + 1
    elif (ord(text[i]) == 46 or ord(text[i]) == 66 or ord(text[i]) == 63):
        sentences = sentences + 1

# initializing a few variables needed for computation of index
letters_per_100, multiplier, sentences_per_100, index = 0.0, 0.0, 0.0, 0.0
answer = 0

# computing per 100 word values
multiplier = 100.0 / words

letters_per_100 = multiplier * letters
sentences_per_100 = multiplier * sentences

# Coleman-Liau formula
index = 0.0588 * letters_per_100 - 0.293 * sentences_per_100 - 15.8
answer = round(index)

# output
if answer < 1:
    print("Before Grade 1")
elif (answer >= 16):
    print("Grade 16+")
else:
    print("Grade " + str(answer))