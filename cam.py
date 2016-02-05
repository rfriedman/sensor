from SimpleCV import Camera
from SimpleCV import Image
# Initialize the camera
cam = Camera()
# Loop to continuously get images
    # Get Image from camera
img = cam.getImage()
img.save()
    # Make image black and white
    #img = img.binarize()
    # Draw the text "Hello World" on image
   # img.drawText("Hello World!")
    # Show the image
#    img.show()
