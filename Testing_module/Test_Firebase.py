
import firebase_admin
from firebase_admin import credentials, db
import csv
import time

# Initialize Firebase with your credentials
cred = credentials.Certificate('csv.json')
firebase_admin.initialize_app(cred, {'databaseURL': 'https://csv-file-e3005-default-rtdb.europe-west1.firebasedatabase.app'})

# Reference to the root of your database
ref = db.reference('/')

# Path to your CSV file
csv_path = "random_data_8.csv"

# Read data from CSV file
def read_csv():
    with open(csv_path, 'r') as csv_file:
        csv_reader = csv.DictReader(csv_file)
        data = [row for row in csv_reader]
    return data

# Example data to be stored in the database
data_to_store = read_csv()

# Send each row of data to the database every second
for entry in data_to_store:
    # Push the data to the database
    new_entry_ref = ref.push(entry)
    print(f"Data written to: {new_entry_ref.path}")

    # Wait for 1 second before sending the next row of data
    time.sleep(3)

