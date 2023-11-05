import csv
import sys


def main():
    # TODO: Check for command-line usage
    database_name, sequence_name = check_arguments()
    # TODO: Read database file into a list of dictionaries
    humans = open_database(database_name)
    # TODO: Read DNA sequence file into a string
    sequences = open_sequence(sequence_name)
    # TODO: Find longest match of each STR in DNA sequence
    # Creando un diccionario iterando a traves de otro diccionario con clave key
    values = dict()
    for key in humans[0].keys():
        if key != "name":
            values[key] = longest_match(sequences, key)

    # TODO: Check database for matching profiles

    for human in humans:
        match = True
        for key, value in values.items():
            if human.get(key) != str(value):
                match = False
                break
        if match:
            print(human["name"])
            break
    if match == False:
        print("No match")

    return


def check_arguments():
    while True:
        try:
            database_name = sys.argv[1]
            sequence_name = sys.argv[2]
            return database_name, sequence_name
        except IndexError:
            print("Usage: python dna.py data.csv sequence.txt")


def open_database(d):
    with open(d, "r") as file:
        reader = csv.DictReader(file)
        humans = []
        for row in reader:
            humans.append(row)
        return humans


def open_sequence(s):
    with open(s, "r") as file:
        sequence = file.read()
        return sequence


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
