# Merry christmas from arduino

This project shows christmas images on a 8x8 rgb led matrix grid

## setup

For this project you'll need :

- an arduino nano
- a matrix RGB grid [see](https://wiki.52pi.com/index.php/RPI-RGB-LED-Matrix_SKU:EP-0075)

## arduino plug

To put it your arduino first plug your arduino as here :

Note MISO is not used so don't plug it

![plug](http://lab.dejaworks.com/wp-content/uploads/2016/08/Arduino-Nano-SD-Card-Connection.png)

## arduino code

run the following
```
arduino christmas.ino
```

## result

TODO add gif

## see patern examples

install deps :

```
pip install -r requierements.txt
```

run the script

```
python draw.py
```

TODO add screeshot

## Generate new paterns

You can add new paterns and visualise it with python

1. create `my_object.txt` file in the repo folder
2. fill it with 1 and 0 with 8 lines of 8 bits (don't forget to add an empty line at the end)
3. show the result with