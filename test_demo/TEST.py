import serial
import datetime
import time
import unittest
import sys
from threading import Timer

class TestUARTCommunication(unittest.TestCase):
    def test_uart_communication(self):
        try:
            # Open serial port for communication with the microcontroller
            ser = serial.Serial('COM10', baudrate=9600, timeout=1)

            while True:
                try:
                    # ser.write(b'B')

                    # Read data from the microcontroller
                    received_data = ser.read(1)
                    received_data=int.from_bytes(received_data,byteorder='big')

                    # Print received data to console
                    print("Received data:", received_data)

                    # Log the received data
                    self.log_received_data(received_data)

                except KeyboardInterrupt:
                    print("Terminating script.")
                    break
                except Exception as e:
                    print("Error:", e)

                # Wait for the specified periodicity
                time.sleep(self.periodicity)

            # Close the serial port
            ser.close()
        except serial.SerialException as e:
            print("Error: Could not open serial port:", e)

    def log_received_data(self, received_data):
        try:
            # Log the received data with timestamp to a file
            with open('received_data_log.txt', 'a') as f:
                timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                log_entry = f"[{timestamp}] Received data: {received_data}\n"
                f.write(log_entry)
                print(log_entry, end='')
        except Exception as e:
            print("Error:", e)

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: python script.py <periodicity_in_seconds>")
        sys.exit(1)

    try:
        # Get periodicity from command line argument
        periodicity = int(sys.argv[1])

        # Set the periodicity for the test case
        TestUARTCommunication.periodicity = periodicity

        # Run the unit test
        unittest.main(argv=sys.argv[:1])

    except ValueError:
        print("Periodicity must be an integer.")
        sys.exit(1)
