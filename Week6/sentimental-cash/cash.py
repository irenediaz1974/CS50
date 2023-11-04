from cs50 import get_float


def main():
    # Ask how many dollars the customer is owed
    cents = get_dollars()
    # Calculate the number of quarters to give the customer
    quarters = calculate_quarters(cents)
    cents = cents - quarters * 25
    # Calculate the number of dimes to give the customer
    dimes = calculate_dimes(cents)
    cents = cents - dimes * 10
    # Calculate the number of nickels to give the customer
    nickels = calculate_nickels(cents)
    cents = cents - nickels * 5
    # Calculate the number of pennies to give the customer
    pennies = calculate_pennies(cents)
    cents = cents - pennies * 1
    # Sum coins
    coins = quarters + dimes + nickels + pennies
    print(coins)


def get_dollars():
    while True:
        try:
            n = get_float("Change owed: ")
            if n > 0:
                return n * 100
        except ValueError:
            print("Not a valid value")


def calculate_quarters(cents):
    quarters = int(cents / 25)
    return quarters


def calculate_dimes(cents):
    dimes = int(cents / 10)
    return dimes


def calculate_nickels(cents):
    nickels = int(cents / 5)
    return nickels


def calculate_pennies(cents):
    pennies = int(cents / 1)
    return pennies


main()
