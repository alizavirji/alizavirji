#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec  6 17:08:34 2023

@author: alizavirji
"""

class Bear:
    #takes rows and column and direction 
    def __init__(self, row, col, dirr):
        self.row = row
        self.col = col
        self.dir = dirr
        self.berry_huger = 0 
        self.sleep_number = 0
    
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

