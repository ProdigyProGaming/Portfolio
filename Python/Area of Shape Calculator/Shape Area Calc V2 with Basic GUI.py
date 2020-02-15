#########################################################################################
#Arron Rawstron                                                                         #
#The maths department of a local junior school has asked for you to produce a programme #
#to help students check their calculations of areas of simple shapes                    #
#The shapes are to include triangle, rectangle and circle.                              #
#They want your application to                                                          #
#Ask the user which shape they are working with                                         #
#   Prompt the user for inputs (length, width, height and radius) as required.          #
#   User to enter their calculated answer                                               #
#   Congratulate the user / offer the correct answer                                    #
#   Offer the options of quit and start again.                                          #
#A graphical solution is not needed as the school are keen that their pupils get used   #
#to reading written instructions.                                                       #
#########################################################################################

import math
from tkinter import *

def triangleDimensions():
    triangleBase = getAFloat("What is the length of the BASE?\n")
    triangleHeight = getAFloat("What is the HEIGHT?\n")
    triArea = (triangleBase * triangleHeight)/2 
    return round(triArea,2)    
    
def rectangleDimensions():
    rectangleLength = getAFloat("What is the LENGTH?\n")
    rectangleWidth = getAFloat("What is the WIDTH?\n")
    recArea = (rectangleLength * rectangleWidth)
    return round(recArea,2)

def circleDimensions():
    circleRadius = getAFloat("What is the RADIUS?\n")
    cirArea = (math.pi * circleRadius * circleRadius)
    return round(cirArea,2)
    
    
def answer(calculatedArea):
    userAnswer = -1

    while (userAnswer != calculatedArea):
        check1 = "N"
        while (check1 != "Y"):
            userAnswer = getAFloat("What Was Your Answer To Two Decimal Places?\n")
            print("Are You Sure",userAnswer,"Is Your Answer?")
            check1 = input("Y/N:")
            check1 = check1.upper()
        if (userAnswer == calculatedArea):
            print ("Woo Hoo!!!\n")
        else:
            print ("That's Not Right")
            tryAgain = input("Would you like to try again?\n")
            tryAgain = tryAgain.upper()
            if tryAgain == "Y":
                userAnswer == -1
            else:
                userAnswer = calculatedArea

def run():
    again = "Y"
    while (again == "Y"):
        shape()
        again = input("Would you like to do another one?\n"
                      "Press Y Then Enter To Do Another One\n"
                      "Press Any Other Button Then Enter To Quit\n")
        again = again.upper()
    print("Thank you for using this program")
    quit()

def shape():
    userShape = ""
    while userShape == "":
        userShape = getAFloat(
            "If your shape is a triangle, enter 1.\n"
            "If your shape is a rectangle, enter 2.\n"
            "If your shape is a circle, enter 3.\n"
            "If you require help, enter 4.\n"
            "If you want to quit, enter 5.\n")
        if userShape == 1:
            area = triangleDimensions()
            answer(area)
        elif userShape == 2:
            area = rectangleDimensions()
            answer(area)
        elif userShape == 3:
            area = circleDimensions()
            answer(area)
        elif userShape == 4:
            Help()
            userShape = ""
        elif userShape == 5:
            quit()
        else:
            userShape = ""
            
def getAFloat(message):
    choice = ""
    while True:
        try:
            choice = float(input(message))
            break
        except ValueError:
            print("Invalid Entry")
    return (choice)


def Help():

    def closewindow():
        root.destroy()

    root = Tk()
    root.title("Help Window")
    root.geometry("400x200")
    root.attributes("-topmost", True)

    app = Frame(root)
    app.grid()
    
    label = Label(app, text = "I am designed to help you check your answer.\n"
                              "First enter which shape you worked out.\n"
                              "Then enter the dimensions of the shape.\n"
                              "I will then work out the correct answer.\n"
                              "You will then need to input your answer for me to check.\n"
                              "If your answer is correct, I will congratulate you.\n"
                              "If not, I will give you the opportunity to correct if you would like to.\n"
                              "I will then give you the option to do another one or quit.\n")
    label.grid()

    Exit = Button(root, text = "Close Window", command = closewindow)
    Exit.grid()

    root.mainloop()

run()
