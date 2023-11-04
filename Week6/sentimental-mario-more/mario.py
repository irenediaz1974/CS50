# prints bricks using code from the conference (src6)


def main():
    height = get_height()
    for i in range(height):
        print(" " * (height - (i + 1)) + "#" * (i + 1) + "  " + "#" * (i + 1))


def get_height():
    while True:
        try:
            n = int(input("Height: "))
            if n > 0 and n < 9:
                return n
        except ValueError:
            print("Not an integer")


main()
