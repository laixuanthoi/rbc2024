import time
import cv2
from picamera2 import Picamera2, Preview
from uart import Uart
from detection.ball_detect import Ball_Detect
from threading import Thread

IMAGE_WIDTH = 320
IMAGE_HEIGHT = 320

def mapRange(value, inMin, inMax, outMin, outMax):
    return outMin + (((value - inMin) / (inMax - inMin)) * (outMax - outMin))

picam2 = Picamera2()
preview_config = picam2.create_preview_configuration(main={"size": (2000, 2000)})
picam2.configure(preview_config)
# picam2.start_preview()
picam2.start()
time.sleep(1)

ball_detect = Ball_Detect(show_debug=True)
uart = Uart()

san_xanh = True
isStop = False

center_ball = [0,0]
def read_uart_thread():
    global san_xanh
    while not isStop:
        time.sleep(0.1)
        receive = uart.get()
        print("receive...", receive)
        # if (receive == 0):
        #     san_xanh = False
        # elif (receive == 1):
        #     san_xanh = True
        
        
def send_uart_thread():
    while not isStop:
        time.sleep(0.1)
        if (center_ball[0] > 0 and center_ball[0] < 320) and (center_ball[1] > 0 and center_ball[1] < 320):
            print(center_ball)
            data = [mapRange(center_ball[0], 0, 320, 1, 254), mapRange(center_ball[1], 0, 320, 1, 254), 255]
            print(f"send...: ", data)
            uart.put(data)
        
    
if __name__ == "__main__":
    read_thread = Thread(target=read_uart_thread,)
    send_thread = Thread(target=send_uart_thread,)
    read_thread.start()
    send_thread.start()
    try:
        while True:
            if san_xanh == 1:
                ball_detect.detect_xanh = True
            elif san_xanh == 0:
                ball_detect.detect_xanh = False
            bgr = picam2.capture_array()
            bgr = cv2.resize(bgr, (IMAGE_WIDTH, IMAGE_HEIGHT))
            bgr = bgr[:270,:]
            rgb = cv2.cvtColor(bgr, cv2.COLOR_BGR2RGB)
            ball_detect.detect_image(rgb)
            center_ball = ball_detect.center_ball
            # print(center_ball, center_ball[0] -ball_detect.image_width//2, center_ball[1]-ball_detect.image_height//2)
            if cv2.waitKey(1) == ord('q'):
                break
    except Exception as e:
        print(e)
        pass
    finally:
        isStop = True
        read_thread.join()
        send_thread.join()
        cv2.destroyAllWindows()
        picam2.close()
