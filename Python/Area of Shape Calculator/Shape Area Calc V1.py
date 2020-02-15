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
global shape
global Area
shape = 0

def TriangleDimentions():
    global Area
    TriangleBase = float(input("What is the length of the BASE?"))
    TriangleHeight = float(input("What is the HEIGHT?"))
    Area = (TriangleBase * TriangleHeight)/2    
    
def RectangleDimentions():
    global Area
    RectangleLength = float(input("What is the LENGTH?"))
    RectangleWidth = float(input("What is the WIDTH?"))
    Area  = (RectangleLength * RectangleWidth)

def CircleDimentions():
    global Area
    CircleRadius = float(input("What is the RADIUS?"))
    Area = (math.pi * CircleRadius * CircleRadius)
    Area = round(Area,2)
    print(Area)
    
def FirstTry():
    global UserAnswer
    Check1 = "N"
    while (Check1 != "Y"):
        UserAnswer = float(input("What Was Your Answer To Two Decimal Places?"))
        print("Are You Sure",UserAnswer,"Is Your Answer?")
        Check1 = input("Y/N:")
        Check1 = Check1.upper()

def SecondTry():
    while (UserAnswer != Area):
        Check2 = "N"
        while (Check2 != "Y"):
            Check2 = input("You are incorrect. Would you like to try again?")
            Check2 = Check2.upper()
            if Check2 == "N" and Check2 != "Y":
                print("The Correct Answer is",Area)
                Run()
        FirstTry()
        
    print("Congratulations!")
    
def Run():
    Again = "Y"
    while (Again == "Y"):
        Shape()
        Again = input("Would you like to do another one?\n"
                      "Press Y Then Enter To Do Another One\n"
                      "Press Any Other Button Then Enter To Quit\n")
        Again = Again.upper()
    print("Thank you for using this program")
    quit()

def Shape():
    shape = int(input(
        "If your shape is a triangle, enter 1.\n"
        "If your shape is a rectangle, enter 2.\n"
        "If your shape is a circle, enter 3.\n"))
    if shape == 1:
        TriangleDimentions()
        FirstTry()
        SecondTry()
    elif shape == 2:
        RectangleDimentions()
        FirstTry()
        SecondTry()
    elif shape == 3:
        CircleDimentions()
        FirstTry()
        SecondTry()

Run()
