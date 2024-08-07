#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec  6 17:08:43 2023

@author: alizavirji
"""

class Tourist:
    #initializer function taking in a row and column location 
    def __init__(self, row, col):
        self.row = row
        self.col = col
        self.bears_seen_total = 0
        self.bears_seen_this_turn = 0
        self.turns_since_last_bear = 0
        self.activet = []
        
        
    #returns the distance between the tourist being analyzed from the bearrow and bearcolumn that the bear its on in the run function 
    def see_bear(self, bearrow, bearcol):
        x0 = self.row
        y0 = self.col 
        x1 = bearrow 
        y1 = bearcol
        dist = (((x1-x0)**2) +((y1-y0)**2))**.5
        return dist 