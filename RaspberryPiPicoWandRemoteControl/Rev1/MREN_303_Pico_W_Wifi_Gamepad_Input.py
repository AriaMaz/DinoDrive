# MREN 303 Pico W Wifi Gamepad Input
# Written For MREN 303

from inputs import get_gamepad #IMPORTANT NOTE, ONLY WORKS WITH GAMEPAD X_D SWITCH SET TO X
import socket

UDP_IP = "192.168.50.65" #Change to Match IP Of Target Pico w (192.168.1.34)
UDP_PORT = 8888

MESSAGE = b"Hello, World!" #This b"Hello World!" encodes the Hello World! string to a series of bytes which can be sent over UDP

print("UDP target IP: %s" % UDP_IP)
print("UDP target port: %s" % UDP_PORT)
print("message: %s" % MESSAGE)

#The following line establishes a connection with the Pico W MicroController
sock = socket.socket(socket.AF_INET, # Internet
                    socket.SOCK_DGRAM) # UDP
sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))

def main():
    while 1:
        events = get_gamepad()
        for event in events:

            #BUTTONS
            #Recoding As Labelled On Controller
            #event.state 1 is button press, for button release use event.state 0
    
            if(event.code == "BTN_SOUTH" and event.state == 1):
                payload= "A1".format(event.state)
                payload = payload.encode("UTF-8")
                print(payload)
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "BTN_SOUTH" and event.state == 0):
                payload= "A0".format(event.state)
                payload = payload.encode("UTF-8")
                print(payload)
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            
            if(event.code == "BTN_EAST" and event.state == 1):
                payload= "B1".format(event.state)
                payload = payload.encode("UTF-8")
                print(payload)
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "BTN_EAST" and event.state == 0):
                payload= "B0".format(event.state)
                payload = payload.encode("UTF-8")
                print(payload)
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            
            if(event.code == "BTN_NORTH" and event.state == 1):
                payload= "Y1".format(event.state)
                payload = payload.encode("UTF-8")
                print(payload)
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "BTN_NORTH" and event.state == 0):
                payload= "Y0".format(event.state)
                payload = payload.encode("UTF-8")
                print(payload)
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            
            if(event.code == "BTN_WEST" and event.state == 1):
                payload= "X1".format(event.state)
                payload = payload.encode("UTF-8")
                print(payload)
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "BTN_WEST" and event.state == 0):
                payload= "X0".format(event.state)
                payload = payload.encode("UTF-8")
                print(payload)
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            
            if(event.code == "BTN_TL" and event.state == 1):
                payload= "LB1".format(event.state)
                payload = payload.encode("UTF-8")
                print(payload)
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "BTN_TL" and event.state == 0):
                payload= "LB0".format(event.state)
                payload = payload.encode("UTF-8")
                print(payload)
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            
            if(event.code == "BTN_TR" and event.state == 1):
                payload= "RB1".format(event.state)
                payload = payload.encode("UTF-8")
                print(payload)
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "BTN_TR" and event.state == 0):
                payload= "RB0".format(event.state)
                payload = payload.encode("UTF-8")
                print(payload)
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            
            if(event.code == "BTN_THUMBL" and event.state == 1):
                payload= "LS1".format(event.state)
                payload = payload.encode("UTF-8")
                print(payload)
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "BTN_THUMBL" and event.state == 0):
                payload= "LS0".format(event.state)
                payload = payload.encode("UTF-8")
                print(payload)
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            
            if(event.code == "BTN_THUMBR" and event.state == 1):
                payload= "RS1".format(event.state)
                payload = payload.encode("UTF-8")
                print(payload)
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "BTN_THUMBR" and event.state == 0):
                payload= "RS0".format(event.state)
                payload = payload.encode("UTF-8")
                print(payload)
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            
            if(event.code == "BTN_START" and event.state == 1):
                payload= "back1".format(event.state)
                payload = payload.encode("UTF-8")
                print(payload)
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "BTN_START" and event.state == 0):
                payload= "back0".format(event.state)
                payload = payload.encode("UTF-8")
                print(payload)
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            
            if(event.code == "BTN_SELECT" and event.state == 1):
                payload= "start1".format(event.state)
                payload = payload.encode("UTF-8")
                print(payload)
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "BTN_SELECT" and event.state == 0):
                payload= "start0".format(event.state)
                payload = payload.encode("UTF-8")
                print(payload)
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            
            #Mode Inverts the function of the Dpad and Left Stick

            #ABS
            #These inputs give a range of values and are affected by the mode select button, please be aware of this when troubleshooting
            if(event.code == "ABS_Z"):
                payload = "LT {}".format(event.state)
                payload = payload.encode("UTF-8")
                print(payload)
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            
            if(event.code == "ABS_RZ"):
                payload = "RT {}".format(event.state)
                payload = payload.encode("UTF-8")
                print(payload)
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            
            if(event.code == "ABS_HAT0X"):
                if event.state == 1:
                    payload = b"R-DPad1"
                    print(payload)
                    test = 1
                if event.state == 0 and test == 1:
                    payload = b"R-DPad0"
                    print(payload)

                if event.state == -1:
                    payload = b"L-DPad1"
                    print(payload)
                    test = 2
                if event.state == 0 and test == 2:
                    payload = b"L-DPad0"
                    print(payload)
            
            if(event.code == "ABS_HAT0Y"):
                if event.state == 1:
                    payload = b"D-DPad1"
                    print(payload)
                    test = 1
                if event.state == 0 and test == 1:
                    payload = b"D-DPad0"
                    print(payload)

                if event.state == -1:
                    payload = b"U-DPad1"
                    print(payload)
                    test = 2
                if event.state == 0 and test == 2:
                    payload = b"U-DPad0"
                    print(payload)

            if(event.code == "ABS_Y"):
                value = round(event.state/128) #Reducing Resolution
                if value > 255 : value = value -1 #Keep value between 255 and -255
                if value < -255 : value = value + 1
                payload = "LS-Y{}".format(value)
                payload = payload.encode("ascii")
                print(payload)
            if(event.code == "ABS_X"):
                value = round(event.state/128) #Reducing Resolution
                if value > 255 : value = value -1 #Keep value between 255 and -255
                if value < -255 : value = value + 1
                payload = "LS-X {}".format(value)
                payload = payload.encode("ascii")
                print(payload)

            if(event.code == "ABS_RY"):
                value = round(event.state/128) #Reducing Resolution
                if value > 255 : value = value -1 #Keep value between 255 and -255
                if value < -255 : value = value + 1
                payload = "RS-Y {}".format(value)
                payload = payload.encode("ascii")
                print(payload)
            if(event.code == "ABS_RX"):
                value = round(event.state/128) #Reducing Resolution
                if value > 255 : value = value -1 #Keep value between 255 and -255
                if value < -255 : value = value + 1
                payload = "RS-X {}".format(value)
                payload = payload.encode("ascii")
                print(payload)

if __name__ == "__main__":
    main()