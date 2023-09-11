from collections import Counter

histogramValues = []

with open("histogramInput.txt", "r") as valueStream:
    for line in valueStream:
        # remove spaces and commas
        line = line.strip()
        line = line.split(", ")
        # print(line)
        # cast string literals to integers before appending
        histogramValues += [eval(i) for i in line]

valueStream.close()
# print(histogramValues)

# count the values we read
histogramMap = Counter(histogramValues)
# convert to a dictionary to allow use of update() member function
histogramMap = dict(histogramMap)
# sorted(histogramMap, key=histogramMap.get, reverse = True)

# store absent N values as N : 0 in the dictionary
for i in range(10):
    if(histogramMap.get(i) is None):
        histogramMap.update({i: 0})
'''
print("histogramMap: " + str(histogramMap))
print("histogramMap most common value: " + str(max(histogramMap, key=histogramMap.get)) + " total: " + str(histogramMap.get(max(histogramMap, key=histogramMap.get))))
print("Most common number: " + str(histogramMap.most_common()[0][0]) + " with " + str(histogramMap.most_common()[0][1]) + " instances.")
'''
ourHistogram = ""
# from the maximum value count in our dictionary to 0
for i in range(histogramMap.get(max(histogramMap, key=histogramMap.get)), 0, -1):
    # y-axis
    print(str(i) + "\t|\t", end = "")
    ourHistogram += (str(i) + "\t|\t")
    for j in range(0, 10, 1):
        # x-axis
        print({True: "*", False: ""} [histogramMap.get(j) >= i], end = {True: "\n", False: "\t"} [j == 9])
        ourHistogram += ({True: "*\t", False: "\t"} [histogramMap.get(j) >= i]) + ({True: "\n", False: ""} [j == 9])

# 11 tab margins (8 spaces each for standard output)
for i in range(11 * 8 + 1):
    print("-", end = "")
    ourHistogram += "-"
print("\n\t\t", end = "")
ourHistogram += "\n\t\t"
# x-values range from 0-9
for i in range(10):
    print({True: str(i) + "\t", False: str(i)} [i != 9], end = "")
    ourHistogram += ({True: str(i) + "\t", False: str(i)} [i != 9])

# print(ourHistogram)

outputStream = open("histogramOutput.txt", "w")
outputStream.write(ourHistogram)
outputStream.close()
