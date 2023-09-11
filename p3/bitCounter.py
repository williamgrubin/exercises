while True:
    userInput = int(input("Enter an integer whose bits you'd like counted: "))
    ourBinary = bin(userInput)
    bits = 0

    # print(ourBinary)

    for i in ourBinary:
        if i == "1":
            bits += 1

    print("The total number of bits with a value of 1 in the value that you entered is " + str(bits) + ".")
