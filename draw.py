import matplotlib.pyplot as plt
import sys


def get_from_stdin(ncols, nrows):
    image = list()
    idx = nrows
    for line in sys.stdin:
        if idx <= 0:
            break
        idx -= 1
        charline = []

        for i in line:
            if i == '\n':
                break
            charline.append(int(i))
        if len(charline) != ncols:
            raise Exception('invalid line count')
        image.append(charline)
    return image


# Make a grid...
nrows, ncols = 8, 8


def tree():
    image = list()
    image.append([0, 0, 0, 1, 1, 0, 0, 0])
    image.append([0, 0, 1, 1, 1, 1, 0, 0])
    image.append([0, 1, 1, 1, 1, 1, 1, 0])
    image.append([0, 0, 1, 1, 1, 1, 0, 0])
    image.append([0, 1, 1, 1, 1, 1, 1, 0])
    image.append([1, 1, 1, 1, 1, 1, 1, 1])
    image.append([0, 0, 0, 1, 1, 0, 0, 0])
    image.append([0, 0, 0, 1, 1, 0, 0, 0])
    return image


def plot(image):
    # Print lines in hex
    print('{', end='')
    for x in range(ncols):
        hex = 0
        for y in range(nrows):
            # inverted lines are first index
            hex += image[y][x] * pow(2, y)
        print('0x{0:02x}'.format(hex), end='')
        if x < nrows - 1:
            print(','.format(hex), end='')

    print('}')
    # plot grid
    row_labels = range(nrows)
    col_labels = range(ncols)
    plt.matshow(image)
    plt.xticks(range(ncols), col_labels)
    plt.yticks(range(nrows), row_labels)
    plt.show()


if __name__ == "__main__":
    image = get_from_stdin(ncols, nrows)
    plot(image)