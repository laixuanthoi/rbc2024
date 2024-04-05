import serial 
import time


class Uart:
    def __init__(self, port="/dev/ttyS0", baudrate=115200):
        self.port = port
        self.baudrate = baudrate
        try:
            self.ser = serial.Serial(self.port, baudrate=self.baudrate, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=1)
        except Exception as e:
            print(e)
    
    def get(self):
        try:
            return True, int.from_bytes(self.ser.read())
        except Exception as e:
            print(e)
            return False, None

    def put(self, data):
        buffer = bytearray([int(data[0]), int(data[1]), int(data[2]), 1, 1, 1, 1, 13])
        try:
            self.ser.write(buffer)
        except Exception as e:
            # print(e)
            self.ser.close()
            self.ser = None
            self.ser = serial.Serial(self.port, baudrate=self.baudrate, parity=serial.PARITY_NONE, stopbits = serial.STOPBITS_ONE, bytesize = serial.EIGHTBITS, timeout = 1)
    

    

# uart = Uart()

# # i = 0
# while 1:
#     print(uart.get())
#     time.sleep(0.01)
    
    
    
    
