


def strtoint(string):
    size = len(string)
    result = 0
    idx = 0

    while idx < size and string[idx] == ' ':
        idx = idx + 1

    for i in range(idx, size):
        result = 10 * result + ord(string[i]) - ord('0')
    return result

print "result: ", strtoint("     5684")

