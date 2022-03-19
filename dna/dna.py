import csv
import sys


def main():

    # TODO: Check for command-line usage

    if len(sys.argv) != 3:
        print("Usage : python dna.py CSV TXT")
        exit(1)

    # TODO: Read database file into a variable

    with open(sys.argv[1], "r") as csvfile:
        reader = csv.DictReader(csvfile)
        dict_list = list(reader)

    # TODO: Read DNA sequence file into a variable

    with open(sys.argv[2], "r") as txtfile:
        sequence = txtfile.read()

    # TODO: Find longest match of each STR in DNA sequence
    max_counts = []

    for i in range(1, len(reader.fieldnames)):
        subsequence = reader.fieldnames[i]
        max_counts.append(longest_match(sequence, subsequence))

    # TODO: Check database for matching profiles

    list1 = []
    for z in range(len(max_counts)):
        list1.append(str(max_counts[z]))

    for i in range(len(dict_list)):
        list2 = []
        list_difference = []

        for j in range(1, len(reader.fieldnames)):
            list2.append(dict_list[i][reader.fieldnames[j]])

        for item in list1:
            if item not in list2:
                list_difference.append(item)

        if len(list_difference) > 1:
            yes = False
        elif list_difference == []:
            yes = True
            break

    if yes == True:
        print(dict_list[i]['name'])
    else:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
