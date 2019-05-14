#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu May  9 10:59:18 2019

@author: ernekz
"""

import pymongo
from pymongo import MongoClient
import pandas as pd
from pymongo import MongoClient
import time
import random
from faker import Faker
import datetime
from datetime import timedelta


client = pymongo.MongoClient("mongodb+srv://admin:admin@sep4y-8ayle.gcp.mongodb.net/test?retryWrites=true")
db = client.sep4database
#Checking the server status to the mongoDB
try:
	db.command("serverStatus")
except Exception as e:
	print(e)
else:
	print("you are connected!")

now = datetime.datetime.now()
yesterday = now - timedelta(4)
print(yesterday)
def create_names(fake):
    for x in range(1):
        name = fake.first_name()
        date = yesterday
        dateCreated = "2019-05-02"
        co2 = random.randrange(10, 100, 1)
        temp = random.randrange(3, 11, 1)
        room_id = random.randrange(1, 10, 1)

        result = db.sep4collection.insert_one(
            {
                'date': date,
                'temperature': temp,
                'co2': co2,
                'room_id': room_id,
                'date_created': dateCreated,
                'name': name
                }
            )

        print('id: ' + str(result.inserted_id) + ' name: ' + name)
        time.sleep(1)

if __name__ == '__main__':
    fake = Faker()
    create_names(fake)






#Creating the Dataframe of the corresponding table Date_Dim