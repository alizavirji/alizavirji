#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec  6 17:07:33 2023

@author: alizavirji
"""

import json

class BerryField:
    def __init__(self):
        self.turns = 1
        self.berries = 0
        self.bears = [] # number of active bears = len(active_bears)
        self.reserve_bears = [] # number of reserve bears = len(reserve_bears)
        self.tourists = []
        self.reserve_tourists = []
        # a 2d array to hold the berry field not sure about the size
        self.field = [[0 for x in range(100)] for y in range(100)] # we will overwrite this with the load berry field function
        self.rows = 0
        self.cols = 0

    # count the number of berries in the field at the current moment by going through each row and berry in the row             
    def count_berries(self):
        self.berries = 0
        for row in self.field:
            for berry in row:
                self.berries += berry
        #print(self.berries)
        hello = self.berries 
        return(hello)
    #string that returns field 
    def __str__(self):
        self.bears = self.bears.copy()
        b.count_berries()
        print("Field has {} berries.".format(self.berries))
        #foundtourist = None 
        #foundbear = None
                                
                                
        for row in range(self.rows):
            for col in range(self.cols):
              	# print one letter / number for one space in the field
                foundbear = None
                foundtourist = None
                for tourist in self.tourists:
                    if tourist.row == row and tourist.col == col:
                        foundtourist = tourist
                        
                for bear in self.bears:
                    if bear.row == row and bear.col == col:
                        foundbear = bear
                        
                    
                
                #if foundtourist1 != None and foundbear != None and foundtourist != None:
                 #   print(f"{'B':>4}", end ="")
                if foundbear != None and foundtourist != None:
                    print(f"{'X':>4}", end ="")
                    #foundtourist1 = tourist
                elif foundbear != None and foundtourist == None:
                    #print(f"{foundbear.dir+'B':>4}", end ="")
                    print(f"{'B':>4}", end ="")
                elif foundtourist != None and foundbear == None:
                    print(f"{'T':>4}", end ="")
                else:
                    print(f"{b.field[row][col]:>4}", end ="")
            print()
            return("")
            
                
                #if foundtourist1 != None and foundbear != None and foundtourist != None:
                 #   print(f"{'B':>4}", end ="")
            
    
    # 1) spread by adding one to nearby berries when they are == 10 and the neighboring berry space is 0
    # 2) add one to berries that are > 0
    #grows the berries by checking if the num of berries in that specific spot and if its >= 1 or <10, adds 1 
    #makes neighbor function to check if at least one of the neighbors has 10 berries and if at least one neighbor does, it adds 1 to the berry spot 
    def grow_berries(self):
        
        for row in range(len(self.field)):
            for col in range(len(self.field[row])):
                if (1 <= self.field[row][col]) and self.field[row][col] < 10:
                    self.field[row][col] += 1 
        
        for i in range(len(self.field)):
            row = i
            for j in range(len(self.field[i])):
                column = j
        maxrow = row 
        maxcolumn = column         
        
        for i in range(len(self.field)):
            row = i
            for j in range(len(self.field[i])):
                neighbors = []
                column = j 
                if row - 1 >= 0:
                    neighbors.append(self.field[i-1][j])
                if row +1 <= maxrow:
                    neighbors.append(self.field[row+1][j])
                if column - 1 >= 0:
                    neighbors.append(self.field[i][j-1])
                if column +1 <= maxcolumn:
                    neighbors.append(self.field[i][j+1]) 
                if row - 1 >= 0 and column -1 >=0:
                    neighbors.append(self.field[i-1][j-1])
                if row +1 <= maxrow and column-1 >= 0:
                    neighbors.append(self.field[i+1][j-1])
                if row - 1 >= 0 and column + 1 <= maxcolumn:
                    neighbors.append(self.field[i-1][j+1])
                if row + 1 <= maxrow and column+1<= maxcolumn:
                    neighbors.append(self.field[i+1][j+1])
                    
                for k in neighbors:
                    if self.field[i][j] == 0 and k == 10:
                        self.field[i][j] +=1 
                        break
                    else:
                        self.field[i][j] = self.field[i][j]
                        
    #runs the function for each bear until it reaches 30 berries 
    #checks all the conditions before actually moving the bear, such as:
        #1. there is a tourist on the spot it lands on - if this happens, puts bear to sleep for 3 turns 
        #2. bear goes out of bounds
    #also checks for tourists and if it's seen a bear each turn or if it sees 4 bears at the same time - if it sees 4 bears or hasnt seen bear for 3 turns, removes tourist 
    def run(self, oor2 = []):
        print("Turn: " + str(self.turns))
        
        #for bear in self.bears:
        """
            foundtourist = None
            for tourist in self.tourists:
                if tourist.row == bear.row and tourist.col == bear.col:
                    foundtourist = tourist
                if foundtourist != None:
                    bear.sleep_number = 3
        """     
        #updating the bears
        for bear in self.bears[::1]:
            oor = []
            #print(str(bear))
            
            #if (bear.sleep_number > 0):
                #bear.sleep_number -= 1
             #   continue# stop the rest of this loop and go to the next bear
                # check for tourists
            
            #if(False):
                # if tourists are found, then bear sleeps
                # and tourists are removed from the field
            #    continue
            
                # bear eats
            #else:
            
                
            for i in range(len(self.field)):
                roww = i
                for j in range(len(self.field[i])):
                    columnn = j
            maxrow = roww 
            maxcolumn = columnn  
            
        
            while (bear.berry_huger < 30):
                
                #if (bear.sleep_number > 0):
                 #   bear.sleep_number -= 1
                  #  break                
                
                
                #foundtourist = None
                for tourist in self.tourists:
                    if tourist.row == bear.row and tourist.col == bear.col:
                        foundtourist = tourist
                        b.tourists.remove(tourist)
                        print("Tourist at ({},{}), {} turns without seeing a bear. - Left the Field".format(tourist.row, tourist.col, tourist.turns_since_last_bear))
                 #   if foundtourist != None:
                        bear.sleep_number = 3
                        break
                    
                if (bear.sleep_number > 0):
                    bear.sleep_number -= 1
                    break    
                
                if bear.row < 0 or bear.col < 0 or bear.row > maxrow or bear.col > maxcolumn:
                   coordinates = bear.row, bear.col
                   oor.append(coordinates)
                   if coordinates not in oor2:
                       print("Bear at ({},{}) moving {}. - Left the Field".format(bear.row, bear.col, bear.dir))
                       b.bears.remove(bear)
                   oor2.append(coordinates)
                   
                   break
                bear.eat(self.field[bear.row][bear.col])
                #print(self.field[bear.row][bear.col], bear.row, bear.col)
                #if foundtourist != None and foundbear != None:
                #break
                #if bear.row == maxrow or bear.col == maxcolumn:
                   #bear.row = bear.row
                   #bear.col = bear.col
                   #self.field[bear.row][bear.col] = self.field[bear.row][bear.col]
                   #break
                   
                 
                   
                (self.field[bear.row][bear.col]) = 0
                if bear.berry_huger >= 30:
                    break
                else:
                    bear.move()         
            
            #print(oor2)
            bear.berry_huger = 0 
            
            # then bear moves
        leftfield = []
        # after bears update, we update the tourists
        for tourist in self.tourists[::1]:
            # check for bears in the neighborhood
            bears_in_neighborhood = 0
            for bear in self.bears:
                if tourist.see_bear(bear.row, bear.col) <= 4:
                    bears_in_neighborhood += 1      
            
            #if tourist.turns_since_last_bear == 3:
             #   print("Tourist left at", tourist.row, tourist.col, tourist.turns_since_last_bear)
              #  b.tourists.remove(tourist)
                    
            if bears_in_neighborhood >= 3:
                print("Tourist at ({},{}), {} turns without seeing a bear. - Left the Field".format(tourist.row, tourist.col, tourist.turns_since_last_bear))
                b.tourists.remove(tourist)
                #print("TOURIST REMOVED", tourist)
                
    
                
        #for tourist in self.tourists[::1]:
            bears_in_neighborhood = 0
            for bear in self.bears:
                if tourist.see_bear(bear.row, bear.col) <= 4:
                    bears_in_neighborhood += 1 
            
            if bears_in_neighborhood == 0:
                 tourist.turns_since_last_bear +=1 
                 #print("Turns since seen last bear", tourist.row, tourist. col, tourist.turns_since_last_bear)
        
                
            if tourist.turns_since_last_bear == 3:
                lfc = tourist.row, tourist.col
                leftfield.append(lfc)
                b.tourists.remove(tourist)
                
            elif tourist.turns_since_last_bear != 3:
                tourist.activet.append(tourist)
                
        for i in leftfield:
            print("Tourist at ({},{}), 3 turns without seeing a bear - Left the Field".format(i[0], i[1]))
                #calculate the distance between this tourist and this bear pythag theorem / distance formula
                # if the distance is less than 4, then increment bears_in_neighborhood

        #self.grow_berries()
        
        self.turns += 1
        #return oor 
        

        
if __name__ == '__main__':
    filename = input("Enter the json file name for the simulation => ").strip()
    print(filename)
    print()
    #filename = "bears_and_berries_2.json"

    file = open(filename, 'r')
    data = json.load(file)

    b = BerryField()
    b.field = load_berry_field(data)
    b.rows = len(b.field)
    b.cols = len(b.field[0])
    b.bears = load_bears(data)
    b.reserve_bears = load_reserve_bears(data)
    b.tourists = load_tourists(data)
    b.reserve_tourists = load_reserve_tourists(data)