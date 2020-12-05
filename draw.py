import matplotlib.pyplot as plt
import sys
import os


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


def plot(image, pause=None):
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
    # use black and white colors
    plt.set_cmap('Greys')
    plt.xticks(range(ncols), col_labels)
    plt.yticks(range(nrows), row_labels)
    if pause:
        plt.pause(pause)
        plt.close()
    else:
        plt.show()


def readfile(filename, ncols, nrows):
    image = list()
    idx = nrows
    with open(filename, 'r') as f:
        charline = list()
        for char in f.read():
            if char == '\n':
                # check line size
                if len(charline) != ncols:
                    raise Exception(f'invalid line count img:{image}')
                # add line
                image.append(charline)
                idx -= 1
                charline = list()
                continue
            # end the image
            if idx <= 0:
                break
            # add value in line
            charline.append(int(char))
    return image


def plotdir(path):
    for file in os.scandir(path):
        if file.is_file() and file.name.endswith('.txt'):
            try:
                image = readfile(file.name, 8, 8)
            except Exception as e:
                print(f'file:{file.name} is not readable error:{e}')
                continue
            print(f'file:{file.name}')
            plot(image, pause=1)


if __name__ == "__main__":
    # image = get_from_stdin(ncols, nrows)
    # plot(image)
    if len(sys.argv) == 2:
        filename = sys.argv[1]
        image = readfile(filename, 8, 8)
        print(f'file:{filename}')
        plot(image)
    plotdir('.')
