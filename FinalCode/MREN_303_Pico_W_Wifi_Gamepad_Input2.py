from inputs import get_gamepad #IMPORTANT NOTE, ONLY WORKS WITH GAMEPAD X_D SWITCH SET TO X
import socket
import time

UDP_IP = "192.168.50.74" #Change to Match IP Of Target Pico w this is for MREN303
#UDP_IP = "192.168.2.219" #Change to Match IP Of Target Pico w this is for MREN303
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
            print("code:" , event.code, "state:" ,event.state)

            #BUTTONS
            #Recoding As Labelled On Controller
            #event.state 1 is button press, for button release use event.state 0
            if(event.code == "BTN_SOUTH" and event.state == 1):
                payload= b"A1"
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "BTN_SOUTH" and event.state == 0):
                payload= b"A0"
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            
            if(event.code == "BTN_EAST" and event.state == 1):
                payload= b"B1"
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "BTN_EAST" and event.state == 0):
                payload= b"B0"
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            
            if(event.code == "BTN_NORTH" and event.state == 1):
                payload= b"Y1"
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "BTN_NORTH" and event.state == 0):
                payload= b"Y0"
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            
            if(event.code == "BTN_WEST" and event.state == 1):
                payload= b"X1"
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "BTN_WEST" and event.state == 0):
                payload= b"X0"
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            
            if(event.code == "BTN_TL" and event.state == 1):
                payload= b"LB1"
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "BTN_TL" and event.state == 0):
                payload=
                7b"LB0"
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "BTN_TR" and event.state == 1):
                payload= b"RB1"
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "BTN_TR" and event.state == 0):
                payload= b"RB0"
                sock.sendto(payload, (UDP_IP, UDP_PORT));

            if(event.code == "BTN_THUMBL" and event.state == 1):
                payload= b"LS1"
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "BTN_THUMBL" and event.state == 0):
                payload= b"LS0"
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "BTN_THUMBR" and event.state == 1):
                payload= b"RS1"
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "BTN_THUMBR" and event.state == 0):
                payload= b"RS0"
                sock.sendto(payload, (UDP_IP, UDP_PORT));

            if(event.code == "BTN_START" and event.state == 1):
                payload= b"Back1"
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "BTN_START" and event.state == 0):
                payload= b"Back0"
                sock.sendto(payload, (UDP_IP, UDP_PORT));

            if(event.code == "BTN_SELECT" and event.state == 1):
                payload= b"Strt1"
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "BTN_SELECT" and event.state == 0):
                payload= b"Strt0"
                sock.sendto(payload, (UDP_IP, UDP_PORT));

            #ABS
            #These inputs give a range of values and are affected by the mode select button, please be aware of this when troubleshooting
            if(event.code == "ABS_Z"):
                payload = "L Trigger Value {}".format(event.state)
                payload = payload.encode("UTF-8")
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "ABS_RZ"):
                payload = "R Trigger Value {}".format(event.state)
                payload = payload.encode("UTF-8")
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            
            if(event.code == "ABS_HAT0X"):
                if event.state == 1:
                    payload = b"Rdp1"
                    if event.state == 0:
                        payload = b"Rdp0"
                if event.state == -1:
                    payload = b"Ldp1"
                    if event.state == 0:
                        payload = b"Ldp0"
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "ABS_HAT0Y"):
                if event.state == 1:
                    payload = b"Ddp1"
                    if event.state == 0:
                        payload = b"Ddp0"
                if event.state == -1:
                    payload = b"Udp1"
                    if event.state == 0:
                        payload = b"Udp0"
                sock.sendto(payload, (UDP_IP, UDP_PORT));

            if(event.code == "ABS_Y"):
                value = round(event.state/128) #Reducing Resolution
                if value > 255 : value = value -1 #Keep value between 255 and -255
                if value < -255 : value = value + 1
                payload = "L Stick Y Value {}".format(value)
                payload = payload.encode("ascii")
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "ABS_X"):
                value = round(event.state/128) #Reducing Resolution
                if value > 255 : value = value -1 #Keep value between 255 and -255
                if value < -255 : value = value + 1
                payload = "L Stick X Value {}".format(value)
                payload = payload.encode("ascii")
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            
            if(event.code == "ABS_RY"):
                value = round(event.state/128) #Reducing Resolution
                if value > 255 : value = value -1 #Keep value between 255 and -255
                if value < -255 : value = value + 1
                payload = "R Stick Y Value {}".format(value)
                payload = payload.encode("ascii")
                sock.sendto(payload, (UDP_IP, UDP_PORT));
            if(event.code == "ABS_RX"):
                value = round(event.state/128) #Reducing Resolution
                if value > 255 : value = value -1 #Keep value between 255 and -255
                if value < -255 : value = value + 1
                payload = "R Stick X Value {}".format(value)
                payload = payload.encode("ascii")
                sock.sendto(payload, (UDP_IP, UDP_PORT));

if __name__ == "__main__":
    main()