from PIL import Image
im = Image.open('kirbypequeno2.jpg', 'r')
width, height = im.size
print(width)
print(height)
pixel_values = list(im.getdata())


texto = open("testdos.ppm", "w")
texto.write("P3\n")
texto.write(str(height) + " " +str(width)+"\n")
texto.write("255\n")
counter = 0


for x in pixel_values:
    for y in x:
        texto.write(str(y)+"\n")
texto.close()
