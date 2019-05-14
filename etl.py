import pymongo
from pymongo import MongoClient
import pandas as pd
import pyodbc
import sqlalchemy
import numpy as np
import time

client = pymongo.MongoClient("mongodb+srv://admin:admin@sep4y-8ayle.gcp.mongodb.net/test?retryWrites=true")
db = client.sep4database
df = pd.DataFrame(list(db.sep4collection.find()))
df.head()

#Checking the server status to the mongoDB
try:
	db.command("serverStatus")
except Exception as e:
	print(e)
else:
	print("you are connected!")
    
    
def convertToFarenheit(x):
    x = x * 1.8 + 32
    return float(x)


#Creating the Dataframe of the corresponding table Date_Dim
    
dfDate = pd.DataFrame(df['date'])
dfDate.insert(0, 'Dim_ID', range(880, 880 + len(df)))

#Adding different columns to the Date_Dim df for easier analysis
dfDate['date'] = pd.DatetimeIndex(df['date']).date
dfDate['year'] = pd.DatetimeIndex(df['date']).year
dfDate['quarter'] = pd.DatetimeIndex(df['date']).quarter
dfDate['month'] = pd.DatetimeIndex(df['date']).month
dfDate['week'] = pd.DatetimeIndex(df['date']).week
dfDate['day'] = pd.DatetimeIndex(df['date']).day
dfDate['dayOfWeek'] = pd.DatetimeIndex(df['date']).dayofweek +1
dfDate.head()

#Creating the Dataframe of the corresponding table Sensors_Dim
dfSensors = pd.DataFrame()
dfSensors.insert(0, 'Sensors_ID', range(0, 0 + len(df)))
dfSensors['Sensors_ID'] = dfSensors['Sensors_ID'].astype(np.integer)



#Creating the Dataframe of the corresponding table Room_Dim
dfRoom = pd.DataFrame([df.room_id, df.date_created]).transpose()
dfRoom['name'] = df['name'].astype(str)
dfRoom['date_created'] = pd.to_datetime(dfRoom['date_created'])


#Creating the Dataframe of the corresponding table Time_Dim
dfTime = pd.DataFrame()
dfTime.insert(0, 'Time_ID', range(200, 200 + len(df)))

#Adding different columns to the Date_Dim df for easier analysis
dfTime['time'] = pd.DatetimeIndex(df['date']).time
dfTime['hour'] = pd.DatetimeIndex(df['date']).hour
dfTime['minute'] = pd.DatetimeIndex(df['date']).minute
dfTime['second'] = pd.DatetimeIndex(df['date']).second


#Creating the Dataframe of the corresponding table Fact
def fact():
    dfFact = pd.DataFrame([dfDate.Dim_ID, dfRoom.room_id, dfSensors.Sensors_ID ,dfTime.Time_ID, df.temperature, df.co2] ).transpose()
    dfFact = dfFact.rename(columns={'temperature':'temp_c'})

    #Converting from Celsius to Farenheit and putting it to different column
    dfFact['temp_f'] = dfFact['temp_c']
    dfFact['temp_f'] = dfFact['temp_f'].apply(convertToFarenheit)
    dfFact.insert(0, 'Fact_ID', range(100, 100 + len(df)))
    dfFact.sort_values(by=['Fact_ID'], ascending = True)

#Connecting to the SQL server
server = 'sep4db.database.windows.net' 
database = 'sep4db' 
username = 'theadmin' 
password = 'Password123' 
cnxn = pyodbc.connect('DRIVER={ODBC Driver 17 for SQL Server};SERVER='+server+';DATABASE='+database+';UID='+username+';PWD='+ password)
cursor = cnxn.cursor()

cursor.execute("SELECT @@version;") 
row = cursor.fetchone() 
while row: 
    print(row[0]) 
    row = cursor.fetchone()
    

  
def truncate():
    cursor.execute("DELETE FROM Facts DBCC CHECKIDENT ('sep4db.dbo.Facts',RESEED, 0)")
    cnxn.commit()
    cursor.execute("DELETE FROM Sensor_Dim DBCC CHECKIDENT ('sep4db.dbo.Sensor_Dim',RESEED, 0)")
    cnxn.commit()
    cursor.execute("DELETE FROM Room_Dim DBCC CHECKIDENT ('sep4db.dbo.Room_Dim',RESEED, 0)")
    cnxn.commit()
    cursor.execute("DELETE FROM Time_Dim DBCC CHECKIDENT ('sep4db.dbo.Time_Dim',RESEED, 0)")
    cnxn.commit()
    cursor.execute("DELETE FROM Date_Dim DBCC CHECKIDENT ('sep4db.dbo.Date_Dim',RESEED, 0)")
    cnxn.commit()
    return True
    


def populate():
    
    for index,row in dfDate.iterrows():
        cursor.execute("INSERT INTO dbo.Date_Dim([Dim_ID],[Date] ,[Year],[Quarter],[Month], [Week], [Day], [DayOfWeek]) values (?, ?, ?, ?, ?, ?, ?, ?)",
                                               row['Dim_ID'],
                                               row['date'],
                                               row['year'],
                                               row['quarter'],
                                               row['month'],
                                               row['week'],
                                               row['day'],
                                               row['dayOfWeek']) 
        cnxn.commit()
    for index,row in dfTime.iterrows():
       cursor.execute("INSERT INTO dbo.Time_Dim([Dim_ID], [Time], [Hour], [Minute], [Second]) values (?, ?, ?, ?, ?)",
                                               row['Time_ID'],
                                               row['time'],
                                               row['hour'],
                                               row['minute'],
                                               row['second'])
       cnxn.commit()
 
       
    for index,row in dfFact.iterrows():
       cursor.execute("INSERT INTO dbo.Sensor_Dim([Sensors_ID]) values (?)",
                                               row['Sensors_ID']) 
       cnxn.commit()
       
    for index,row in dfRoom.iterrows():
       cursor.execute("INSERT IGNORE INTO dbo.Room_Dim([Room_ID], [Name], [DataCreated]) values (?, ?, ?)",
                                               row['room_id'],
                                               row['name'],
                                               row['date_created'])
       cnxn.commit()
        
    for index,row in dfFact.iterrows():
        cursor.execute("INSERT INTO dbo.Facts([Fact_ID],[Date_ID] ,[Time_ID],[Room_ID],[Sensor_ID], [Temp_c], [Temp_f], [CO2]) values (?, ?, ?, ?, ?, ?, ?, ?)",
                                               row['Fact_ID'],
                                               row['Dim_ID'],
                                               row['Time_ID'],
                                               row['room_id'],
                                               row['Sensors_ID'],
                                               row['temp_c'],
                                               row['temp_f'],
                                               row['co2'])
        cnxn.commit()
    return True


if truncate():
    populate()
client.close()


