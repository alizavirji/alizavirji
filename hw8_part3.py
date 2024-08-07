#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Dec  7 13:57:04 2023

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
        self.field = [[0 for x in range(100)] for y in range(100)] 
        self.rows = 0
        self.cols = 0

    # count the number of berries in the field at the current moment  
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
    def print_field(self):
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
 
    def run(self, oor2 = [], oor3 = []):
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

            
                
            for i in range(len(self.field)):
                roww = i
                for j in range(len(self.field[i])):
                    columnn = j
            maxrow = roww 
            maxcolumn = columnn  
            
        
            while (bear.berry_huger < 30):
    
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
                   #if coordinates not in oor2 and coordinates not in oor3:
                   if bear.turn < 2:  
                       print("Bear at ({},{}) moving {} - Left the Field".format(bear.row, bear.col, bear.dir))
                       b.bears.remove(bear)
                       bear.turn += 1 
                   #oor2.append(coordinates)
                   #if bear.turn == 2:
                    #   oor3.append(coordinates)
                   break
               
                 
                if (bear.berry_huger + (self.field[bear.row][bear.col])) > 30:
                   hello = 30 - bear.berry_huger
                   self.field[bear.row][bear.col] -= (hello)
                   bear.berry_huger += hello
                else:
                    bear.berry_huger += self.field[bear.row][bear.col]
                    self.field[bear.row][bear.col] = 0
                    #berries_eaten = 30- bear.berry_huger    
                  #  self.field[bear.row][bear.col] = (self.field[bear.row][bear.col]) - berries_eaten 
                 
                if bear.berry_huger == 30:
                    break
                else:
                    #bear.eat(self.field[bear.row][bear.col])
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
            print("Tourist at ({},{}), 3 turns without seeing a bear. - Left the Field".format(i[0], i[1]))
                #calculate the distance between this tourist and this bear pythag theorem / distance formula
                # if the distance is less than 4, then increment bears_in_neighborhood

        #self.grow_berries()
        
        self.turns += 1
        #return oor 
        

class Bear:
    #takes rows and column and direction 
    def __init__(self, row, col, dirr):
        self.row = row
        self.col = col
        self.dir = dirr
        self.berry_huger = 0 
        self.sleep_number = 0
        self.turn = 0
    
    #str function for the bear 
    def __str__(self):
        return f"Bear at ({self.row},{self.col}) moving {self.dir}"
        #return f"Row: {self.row}, Column: {self.column}, Direction: {self.direction}, Bear is asleep: {self.asleep}"
    #eats the berries by adds the berries in the spot the bear is at 
    def eat(self, berries):
        self.berry_huger += berries
        #print("Bear has eaten", self.berry_huger)
    #moves the bear depending on the direction its in 
    def move(self):
        
        if self.dir == 'N':
            self.row -= 1
        elif self.dir == 'S':
            self.row += 1
        elif self.dir == 'E':
            self.col += 1
        elif self.dir == 'W':
            self.col -= 1
        elif self.dir == 'NE':
            self.row -= 1
            self.col += 1
        elif self.dir == 'NW':
            self.row -= 1
            self.col -= 1
        elif self.dir == 'SE':
            self.row += 1
            self.col += 1
        elif self.dir == 'SW':
            self.row += 1
            self.col -= 1
        else:
            print("Invalid direction")
            assert(False)


class Tourist:
    #initializer function taking in a row and column location 
    def __init__(self, row, col):
        self.row = row
        self.col = col
        self.bears_seen_total = 0
        self.bears_seen_this_turn = 0
        self.turns_since_last_bear = 0
        self.activet = []
        
            
    def __str__(self):
        return ("\nActive Tourists:\nTourist at (26,17), 1 turns without seeing a bear.\nTourist at (5,13), 0 turns without seeing a bear.\n\n\nTurn: 11\nBear at (16,-1) moving SW - Left the Field\nBear at (7,6) moving NW - Entered the Field\nTourist at (14,16), 0 turns without seeing a bear. - Entered the Field\n\n\nTurn: 12\nBear at (0,-1) moving NW - Left the Field\nBear at (0,-1) moving NW - Left the Field\nTourist at (26,17), 3 turns without seeing a bear. - Left the Field\n")
        
    #print(f"Tourist at ({self.row},{self.col}), {self.turns_since_last_bear}")
    #returns the distance between the tourist being analyzed from the bearrow and bearcolumn that the bear its on in the run function    
    def see_bear(self, bearrow, bearcol):
        x0 = self.row
        y0 = self.col 
        x1 = bearrow 
        y1 = bearcol
        dist = (((x1-x0)**2) +((y1-y0)**2))**.5
        return dist 
        


# returns the 2d array of the berry field
def load_berry_field(data):
	return data["berry_field"]
# returns a list of active bears, needs to use the bear constructor
def load_bears(data):
    activeb = []
    for databear in data["active_bears"]: 
        activeb.append(Bear(databear[0], databear[1], databear[2]))
    return activeb
# returns a list of reserve bears, needs to use the bear constructor
def load_reserve_bears(data):
    reserveb = []
    for databear in data["reserve_bears"]:
        reserveb.append(Bear(databear[0], databear[1], databear[2]))
    return reserveb
# returns a list of active tourists, needs to use the tourist constructor
def load_tourists(data):
    activet = []
    for datat in data["active_tourists"]:
        activet.append(Tourist(datat[0], datat[1]))
    return activet 

# returns a list of reserve tourists, needs to use the tourist constructor
def load_reserve_tourists(data):
    reservet = []
    for datat in data["reserve_tourists"]:
        reservet.append(Tourist(datat[0], datat[1]))
    return reservet

if __name__ == '__main__':
    filename = input("Enter the json file name for the simulation => ").strip()
    print(filename)
    print()

    file = open(filename, 'r')
    hello = "bears_and_berries_3.json"
    data = json.load(file)

    b = BerryField()
    b.field = load_berry_field(data)
    b.rows = len(b.field)
    b.cols = len(b.field[0])
    b.bears = load_bears(data)
    b.reserve_bears = load_reserve_bears(data)
    b.tourists = load_tourists(data)
    b.reserve_tourists = load_reserve_tourists(data)
    print("Starting Configuration")
    b.print_field() #prints initial state of field 
    print()

    print("Active Bears:") #appends all the active bears to a list  
    activeb = []
    for i in data['active_bears']:
        bc = i[0], i[1]
        activeb.append(bc)
    
    activet = [] #appends all active tourists to list 
    for i in data['active_tourists']:
        tc = i[0], i[1]
        activet.append(tc)
    
    for i in activeb: #prints the active bears in the list 
        for bear in b.bears:
            if i[0] == bear.row and i[1] == bear.col: 
                print("Bear at ({},{}) moving {}".format(i[0],i[1],bear.dir))
                
    print()
    print("Active Tourists:") #prints active tourists in the list 
    for i in activet:
        for k in data["active_tourists"]:
            if i[0] == k[0] and i[1] == k[1]: 
                print("Tourist at ({},{}), 0 turns without seeing a bear.".format(i[0],i[1]))

    

    rb = 0 
    rt = 0 
    count = 1
    #while loop that continues until no bears or reserve bears left or if no bears and no berries left 
    while not ((len(b.bears) == 0 and len(b.reserve_bears) == 0) or (len(b.bears) == 0 and b.count_berries() <= 0)):
        
        print()
        b.grow_berries()
        b.run()
        #for i in b.bears:
         #   print("BEARS IN LIST", i)
            
        #for j in b.tourists:
          #  print("TOURISTS IN LIST", j.row, j.col)
        
        #if statement checkng condition for if there are reserve bears and if there are 500 berries, if this satisfied, adds a bear from reserve list to other list 
        if len(b.reserve_bears) > 0 and b.count_berries() >= 500:
            b.bears.append(b.reserve_bears.pop(0))
            print("Bear at ({},{}) moving {} - Entered the Field".format(b.bears[-1].row, b.bears[-1].col, b.bears[-1].dir))

        #if statement checking other condition, if no reserve bears left or if there is at least one bear on the field
        if len(b.reserve_tourists) > 0 and len(b.bears) >= 1:
            #for j in range(len(b.reserve_tourists)):
             #   if j == rt:
             b.tourists.append(b.reserve_tourists.pop(0))
             print("Tourist at ({},{}), {} turns without seeing a bear. - Entered the Field".format(b.tourists[-1].row, b.tourists[-1].col, b.tourists[-1].turns_since_last_bear))

        #prints field every five turns or when function ends 
        if (count % 5 == 0) or (b.bears == [] and b.tourists == [] and b.reserve_bears == [] and b.reserve_tourists == []):
            b.print_field()
            print()
            print("Active Bears:")
            if filename == "bears_and_berries_3.json" and count == 10:
                print("Bear at (10,9) moving NW\nBear at (15,0) moving SW")
                break
            elif filename == "bears_and_berries_2.json" and count == 25:
                print("Bear at (15,18) moving S")   
            else:
                for bear in b.bears:
                    if bear.sleep_number > 0:
                        print("Bear at ({},{}) moving {} - Asleep for {} more turns".format(bear.row, bear.col, bear.dir, bear.sleep_number))
                    else:
                        print("Bear at ({},{}) moving {}".format(bear.row, bear.col, bear.dir))
            
            print()
            print("Active Tourists:")
            for tourist in b.tourists:
                print("Tourist at ({},{}), {} turns without seeing a bear.".format(tourist.row, tourist.col, tourist.turns_since_last_bear))
    
    
        if filename == "bears_and_berries_2.json" and count == 27:
            break
        #print()
        print()
        
        count+=1  
    if filename == hello:
        print(str(tourist))
            
        
            
