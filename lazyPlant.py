import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel, QLineEdit, QPushButton, QVBoxLayout, QHBoxLayout, QWidget
from PyQt5.QtGui import QPixmap
import bluetooth
import serial
import time

def send_data(data):
    target_address = 'XX:XX:XX:XX:XX:XX'  # Replace with your device's MAC address
    port = 1  # RFCOMM port number

    try:
        # Connect to the Bluetooth device
        socket = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
        socket.connect((target_address, port))

        # Configure serial communication
        ser = serial.Serial(socket.fileno(), baudrate=9600, timeout=1)

        # Send data
        ser.write(data.encode())

        # Close serial connection
        ser.close()

        print("Data sent successfully.")
    except Exception as e:
        print("Error:", e)

def receive_data():
    target_address = 'XX:XX:XX:XX:XX:XX'  # Replace with your device's MAC address
    port = 1  # RFCOMM port number

    try:
        # Connect to the Bluetooth device
        socket = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
        socket.connect((target_address, port))

        # Configure serial communication
        ser = serial.Serial(socket.fileno(), baudrate=9600, timeout=1)

        # Receive data
        received_data = ser.readline().decode().strip()

        # Close serial connection
        ser.close()

        print("Received data:", received_data)
        return received_data
    except Exception as e:
        print("Error:", e)
        return None

# Example usage
data_to_send = "Hello, Bluetooth!"
send_data(data_to_send)

time.sleep(1)  # Wait for data to be sent and received

received_data = receive_data()
if received_data:
    print("Received data:", received_data)



class PlantCareApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('Lazy Plant')
        self.setGeometry(100, 100, 500, 550)  # x position, y position, width, height
        self.initUI()

    def initUI(self):
        # Main layout
        main_layout = QVBoxLayout()

        # Plant image placeholder and text
        self.plant_image_label = QLabel(self)
        self.plant_image_label.setPixmap(QPixmap("path/to/plant_image.jpg"))  # Placeholder image
        self.plant_image_label.setFixedSize(200, 200)  # Width, height
        self.plant_image_label.setStyleSheet("background-color: lightgreen; border: 1px solid green;")

        self.plant_info_label = QLabel("Plant Information Here")
        self.plant_info_label.setStyleSheet("background-color: white; border: 1px solid black; padding: 10px;")
        
        # Creating a horizontal layout for image and text
        image_text_layout = QHBoxLayout()
        image_text_layout.addWidget(self.plant_image_label)
        image_text_layout.addWidget(self.plant_info_label)
        
        # Input field
        self.command_input = QLineEdit(self)
        self.command_input.setPlaceholderText("Enter command")
        self.command_input.setStyleSheet("border: 1px solid gray; padding: 5px;")

        # Buttons with styles
        self.water_button = QPushButton("Water", self)
        self.add_button = QPushButton("Add Plant", self)
        self.settings_button = QPushButton("Settings", self)
        self.info_button = QPushButton("Info", self)
        buttons = [self.water_button, self.add_button, self.settings_button, self.info_button]

        for button in buttons:
            button.setStyleSheet("background-color: lightblue; border: none; padding: 10px;")

        # Creating a horizontal layout for buttons
        buttons_layout = QHBoxLayout()
        for button in buttons:
            buttons_layout.addWidget(button)
        
        # Adding widgets to the main layout
        main_layout.addLayout(image_text_layout)
        main_layout.addWidget(self.command_input)
        main_layout.addLayout(buttons_layout)

        # Central widget
        central_widget = QWidget()
        central_widget.setLayout(main_layout)
        self.setCentralWidget(central_widget)


# Running the application
def main():
    app = QApplication(sys.argv)
    ex = PlantCareApp()
    ex.show()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()
