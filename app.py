import streamlit as st
import numpy as np
import pandas as pd
from tensorflow.keras.models import load_model
from sklearn.preprocessing import StandardScaler
from sklearn.preprocessing import LabelEncoder
from joblib import load
import serial
import matplotlib.pyplot as plt

# Load the pre-trained model
model = load_model(r"Y:\Self\College\S8\AI Nose\Combined Data\ann_model")

# Load the saved scaler from the training phase
scaler = StandardScaler()
scaler_path = (r"Y:\Self\College\S8\AI Nose\Combined Data\scaler.pkl")
scaler = load(scaler_path)

# Load the label encoder
label_encoder_path = r"Y:\Self\College\S8\AI Nose\Combined Data\label_encoder.pkl"
label_encoder = load(label_encoder_path)

# Set the serial port 
ser = serial.Serial('COM6', 115200)

st.title('Real-time Aroma Detection')

# Define the aroma labels
aroma_labels = ["Background", "Coffee", "Garlic", "Ginger", "Orange", "Tea"]

# Create a placeholder for the custom bar chart
bar_chart_placeholder = st.empty()

# Create a separate container for the predicted aroma
aroma_container = st.empty()

while True:
    arduino_data = ser.readline().decode('utf-8').strip().split(',')

    if arduino_data:
        sensor_values = [float(value) for value in arduino_data]
        sensor_df = pd.DataFrame([sensor_values], columns=['voc1', 'no2', 'eth', 'co'])  
        scaled_input = scaler.transform(sensor_df)

        # Make predictions
        predictions = model.predict(scaled_input)

        # Plot the bar chart using Matplotlib
        fig, ax = plt.subplots()
        ax.bar(aroma_labels, predictions[0])
        ax.set_ylabel('Probability')
        ax.set_xlabel('Aroma')
        ax.set_title('Predicted Aroma Probabilities')
        plt.xticks(rotation=45)  # Rotate x-axis labels for better readability
        
        # Update the custom bar chart in Streamlit
        bar_chart_placeholder.pyplot(fig)

        # Decode the predicted labels
        decoded_labels = label_encoder.inverse_transform(np.argmax(predictions, axis=1))
        
        # Clear the previous prediction and update with the new prediction
        aroma_container.empty()
        aroma_container.write("Predicted Aroma: {}".format(decoded_labels[0]))