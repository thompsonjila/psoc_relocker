# -*- coding: utf-8 -*-
"""
Relocker - Serial Communications Server
Graham Greve / Started Sep. 10, 2018
"""

import colorama # colors for logging
import platform
import serial
import serial.tools.list_ports
import sys
import time


class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

last_time = time.localtime();
    
def p(string, endstr='\n'):
  global last_time
 # timestr = time.strftime("[%b %d %H:%M:%S %p]", time.localtime()) + " "
  if (time.localtime() == last_time):
    print(bcolors.OKGREEN + "                  " + bcolors.ENDC + str(string), end=endstr)
  else:
    last_time = time.localtime()
    timestr = time.strftime("%m/%d %H:%M:%S %p", time.localtime()) + " "
    timestr = (" " + timestr[1:] if timestr.startswith('0') else timestr).replace(" 0", " ")
    print(bcolors.OKGREEN + timestr + bcolors.ENDC + str(string), end=endstr)
   
def p2(string1, string2, endstr='\n'):
  print(bcolors.WARNING + "" + string1 + " " + bcolors.ENDC + str(string2), end=endstr)
  
def warn(string, endstr='\n'):
  timestr = time.strftime("%m/%d %H:%M:%S %p", time.localtime()) + " "
  timestr = (" " + timestr[1:] if timestr.startswith('0') else timestr).replace(" 0", " ")
  print(bcolors.FAIL + timestr + bcolors.ENDC + str(string), end=endstr)
  
  
  

def serial_ports():
  # produce a list of all serial ports. The list contains a tuple with the port number, 
  # description and hardware address
  ports = list(serial.tools.list_ports.comports())  
  port_list = []
  for port_no, description, address in ports:
    port_list.append([port_no, description])
  return port_list
    




if __name__ == '__main__':
 #   print(serial_ports())
  colorama.init()
  p2("  Initializing...", "Relocker: Serial Communications Server")
  p2("   Python version", str(platform.python_version()))
  ports = serial_ports()
  
  if(not ports):
    p("Could not find open COM ports!")
    p(" - Is the device connected to a USB port?")
    p(" - Is another program connected to this port?")
    sys.exit("")
  else:
    for (port, desc) in serial_ports():
      p2("  Connected Ports", port + ": " + desc)
    while(1):
      p("Choose a COM port # or type 'q' to quit")
      com_port_input = input("COM")
      if (com_port_input.lower() == 'q'):
        p("Goodbye")
        sys.exit("")        
      else:
        try:
          com_port_input = int(com_port_input)
          try:
            ser = serial.Serial('COM' + str(com_port_input), 115200, timeout=2) # open serial port
            break
          except serial.serialutil.SerialException:
            warn("Could not open port 'COM" + str(com_port_input) + "'")
        except ValueError:
          p("Invalid entry: " + str(com_port_input))
  
  while(1):
    line = ser.readline()   # read a '\n' terminated line
    if line:
      try:
        line = line.decode('UTF-8')
      except:
        continue
    
      if ('Fail' in line) or ('Warning' in line):
        warn(line, endstr='') # fail, warning, etc.
      elif 'SKYNET' in line:
        print("")
        p2("Relocker rebooted", line, endstr='') # fail, warning, etc.
      elif 'Compiled' in line:
        p2("     Compile date", line, endstr='') # fail, warning, etc.
      else:
        p(line, endstr='')    # normal message
    
  time.sleep(1)