import unittest
import serial

class TestLedControl(unittest.TestCase):
    SERIAL_PORT = 'COM10'  # Example COM port, change as needed
    BAUD_RATE = 9600

    def setUp(self):
        self.ser = serial.Serial(self.SERIAL_PORT, self.BAUD_RATE, timeout=1)

    def tearDown(self):
        self.ser.close()

    def test_led_control(self):
        # Send RPC command to set LED state
        def set_led_state(state):
            self.ser.write(b'LED_STATE ' + bytes([state]) + b'\n')
            response = self.ser.readline().strip()
            return response == b'LED_OK'

        # Simulate switch press and verify LED behavior
        switch_state = 1  # Example switch state, change as needed
        self.assertTrue(set_led_state(switch_state), "LED not turned on")

if __name__ == '__main__':
    unittest.main()
