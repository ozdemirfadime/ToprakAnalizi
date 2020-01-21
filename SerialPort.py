import time
import serial
import smtplib
import sys
TO = 'putyour@email.here'
GMAIL_USER = 'putyour@email.here'
GMAIL_PASS = 'putyourpasswordhere'

SUBJECT = 'Intrusion!!'
TEXT = 'Your PIR sensor detected movement'
  
ser = serial.Serial('COM3', 9600)
orig_stdout = sys.stdout
f = open('out.txt', 'w')
sys.stdout = f

for i in range(2):
    print 'i = ', i

sys.stdout = orig_stdout
f.close()

def send_email():
    print("Sending Email")
    smtpserver = smtplib.SMTP("smtp.gmail.com",587)
    smtpserver.ehlo()
    smtpserver.starttls()
    smtpserver.ehlo
    smtpserver.login(GMAIL_USER, GMAIL_PASS)
    header = 'To:' + TO + '\n' + 'From: ' + GMAIL_USER
    header = header + '\n' + 'Subject:' + SUBJECT + '\n'
    print header
    msg = header + '\n' + TEXT + ' \n\n'
    smtpserver.sendmail(GMAIL_USER, TO, msg)
    smtpserver.close()
    
while True:
    message = ser.readline()
    print(message)
    if message[0] == 'M' :
        send_email()
    time.sleep(0.5)
