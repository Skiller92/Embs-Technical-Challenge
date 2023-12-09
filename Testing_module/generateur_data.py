import csv
import random
from datetime import datetime

def generate_random_data(num_rows):
    data = []
    start_time = datetime.now()

    for i in range(num_rows):
        data_acquisition_time = i
        heart_rate = random.randint(60, 100)
        blood_pressure = random.randint(90, 120)
        glucose_level = random.randint(80, 120)
        temperature = int(random.uniform(10, 25))  # Representing cold temperature
        humidity = random.randint(70, 90)  # Representing high humidity
        air_quality = int(random.uniform(30, 70))  # Representing moderate air quality

        row = [data_acquisition_time, heart_rate, blood_pressure, glucose_level, temperature, humidity, air_quality]
        data.append(row)

    return data

def save_to_csv(data, filename='random_data_8.csv'):
    with open(filename, 'w', newline='') as csvfile:
        csv_writer = csv.writer(csvfile)
        csv_writer.writerow(['data_acquisition_time', 'heart_rate', 'blood_pressure', 'glucose_level', 'temperature', 'humidity', 'air_quality'])
        csv_writer.writerows(data)

if __name__ == "__main__":
    num_rows = 100
    random_data = generate_random_data(num_rows)
    save_to_csv(random_data)
