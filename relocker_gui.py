# -*- coding: utf-8 -*-
"""
Created on Sun Aug 11 16:41:36 2019

@author: Graham
"""

# import sys
# import os
from pathlib import Path
from tkinter import scrolledtext
from tkinter import messagebox
from tkinter import ttk
from tkinter import PhotoImage
import tkinter as tk
import ctypes
import binascii
import struct
from thompsonlib import thompsonlib as TL
import numpy as np

# relocker imports
import platform
import serial   # conda install pyserial
import serial.tools.list_ports
import time
import re

import random

import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import ( FigureCanvasTkAgg, NavigationToolbar2Tk )
from matplotlib.backend_bases import key_press_handler #default Matplotlib key bindings.
#from matplotlib.figure import Figure


class App:
    def __init__(self, master=None):
        self.master = master
        
        self.last_time = time.localtime();
        self.ser = False
        
        self.thresh1 = 1675
        self.thresh2 = 2332
        self.num_pts = 28
        self.plttime = time.strftime("%#I:%M:%S %p, %B %d, %Y", time.localtime())
        self.pltdata = "07A407A2079907A2079C07A0079B0798079B079607910787078B07850778077D076B076F0759075B0741072A072B070E073806AA06E305B0096D07D907DA07D207DF07D607D507D807D507E207D407D707DB07DB07D807D907D807D207D607D907D607D707D007DB07D907D907D907D707E107D507DA07DA07D507DC07DA07D807DF07DB07DE07D607D507DC07DB07D707D407D907D407D807D607D707D607DF07D507DB07D907DC07D407D807D507D407DA07D607C307D807DC07DF07D907DC07DA07D907D907D907D407D507D907DE07DC07D807DB07D707D707DA07D507DA07D807DC07DD07DF07D907DC07E007D407DB07E307D107DE07D507D707DB07DD07DC07DD07D507DE07E207DA07DA07D607D407DA07DF07E007D907DE07D207DD07DD07D507DB07E007DF07DD07DF07DE07D707DE07DA07DC07D907DE07D807DC07E007E107DA07DD07E007DC07DB07DE07E007DE07E007E007D907E007DF07E307E107E007DE07DF07E107E107E107E007DF07E007E407E907E507E007E307E507E207E907EB07EA07EA07F007EF07F407F907F107F2080607FA08020800080308040822082208260842082D086C08C7090607DA06CC069806F3073807700775077B077B078B0787079507960796079B079E07A0079F07A607A107A307AC07AB07AA07A707AF07A707A607B107AC07AA07AA07B007A807AB07A707A407A8"

        master.title("Relocker GUI")
        master.iconbitmap('salamander.ico')
        appid = 'thompson.lab.relocker' # arbitrary string
        ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID(appid) # windows: change icon

        self.img_exit = PhotoImage(file='exit.png')
        self.img_settings = PhotoImage(file='settings.png')
        self.img_info = PhotoImage(file='info.png')
        self.img_reload = PhotoImage(file='reload.png')
        self.img_logo = PhotoImage(file='salamander.png')
        self.img_logo2 = PhotoImage(file='salamander2.png')
        
        
        self.menu = tk.Menu(self.master)
        self.master.config(menu=self.menu)
        self.menu1 = tk.Menu(self.menu, tearoff=0)
        self.menu2 = tk.Menu(self.menu, tearoff=0)
        self.menu3 = tk.Menu(self.menu, tearoff=0)
        self.menu4 = tk.Menu(self.menu, tearoff=0)
        self.menu1.add_command(label=" Properties", command=self.show_properties, image=self.img_settings, compound='left')
        self.menu1.add_separator()
        self.menu1.add_command(label=" Exit", command=self.master.destroy, accelerator="Ctrl+W", underline=1, image=self.img_exit, compound='left')
        self.master.bind_all("<Control-w>", self.master.destroy)
        self.var_reload_plot = tk.BooleanVar()
        self.menu2.add_checkbutton(label=" Reload plot automatically", onvalue=True, offvalue=False, variable=self.var_reload_plot)
        self.menu3.add_command(label=" Rescan COM ports", command=self.scan_serial_ports, image=self.img_reload, compound='left')
        self.menu4.add_command(label=" About", command=self.about, image=self.img_info, compound='left')
        self.menu.add_cascade(label="File", menu=self.menu1)
        self.menu.add_cascade(label="Settings", menu=self.menu2)
        self.menu.add_cascade(label="COM", menu=self.menu3)
        self.menu.add_cascade(label="Help", menu=self.menu4)
        
        
        self.ports_listbox = tk.Listbox(self.master, height=6, width=40)
        self.ports_listbox.grid(row=0, column=0, rowspan=6, padx=5, pady=5, sticky=tk.N+tk.W+tk.E+tk.S)
        
        def test():
            #print ("destroy graph")
            #self.graph.destroy()
            print ("destroy window!")
            #self.window.destroy()
           # print(self.window.state())
            #print(self.graph)
            print(self.window)
      
        self.button_connect = tk.Button(self.master, text="Connect COM", command=self.connect)
        self.button_disconnect = tk.Button(self.master, text="Disconnect COM", state='disabled', command=self.disconnect)
        #self.button_rescan = tk.Button(self.master, text="Rescan ports", command=self.scan_serial_ports)
        self.button_rescan = tk.Button(self.master, text="Rescan ports", command=test)
        
        self.button_connect.grid(row=0, column=1, rowspan=2, padx=5, pady=5, sticky=tk.W)
        self.button_disconnect.grid(row=2, column=1, rowspan=2, padx=5, pady=5, sticky=tk.W)
        self.button_rescan.grid(row=4, column=1, rowspan=2, padx=5, pady=5, sticky=tk.W)
      
        self.button_plot = tk.Button(self.master, text="Plot last error signal", state="normal", image=self.img_logo2, compound='top', command=self.create_plot_window)
        self.button_plot.grid(row=0, rowspan=6, column=2, padx=45, pady=10, sticky=tk.N + tk.E + tk.W + tk.S)
       
        tk.Grid.columnconfigure(self.master, 2, weight=1)
      
      # RECORD CALIBRATION
        self.label_lfout = tk.Label(self.master, text="Loop filter output range:", font="Helvetica 9 bold")
        self.label_lfout_v1_val = tk.StringVar()
        self.label_lfout_v1 = tk.Label(self.master, textvariable=self.label_lfout_v1_val)
        self.label_lfout_v2_val = tk.StringVar()
        self.label_lfout_v2 = tk.Label(self.master, textvariable=self.label_lfout_v2_val)
        self.label_lfout.grid(row=0, column=3, sticky=tk.E)
        self.label_lfout_v1.grid(row=0, column=4)
        self.label_lfout_v2.grid(row=0, column=5)
      
        self.label_lfout_v3_val = tk.StringVar()
        self.label_lfout_v3 = tk.Label(self.master, textvariable=self.label_lfout_v3_val)
        self.label_lfout_v4_val = tk.StringVar()
        self.label_lfout_v4 = tk.Label(self.master, textvariable=self.label_lfout_v4_val)
        self.label_lfout_v3.grid(row=1, column=4)
        self.label_lfout_v4.grid(row=1, column=5)
      
        self.label_errmon = tk.Label(self.master, text="Error monitor range:", font="Helvetica 9 bold")
        self.label_errmon_v1_val = tk.StringVar()
        self.label_errmon_v1 = tk.Label(self.master, textvariable=self.label_errmon_v1_val)
        self.label_errmon_v2_val = tk.StringVar()
        self.label_errmon_v2 = tk.Label(self.master, textvariable=self.label_errmon_v2_val)
        self.label_errmon.grid(row=2, column=3, sticky=tk.E)
        self.label_errmon_v1.grid(row=2, column=4)
        self.label_errmon_v2.grid(row=2, column=5)
      
        self.label_errmon_v3_val = tk.StringVar()
        self.label_errmon_v3 = tk.Label(self.master, textvariable=self.label_errmon_v3_val)
        self.label_errmon_v4_val = tk.StringVar()
        self.label_errmon_v4 = tk.Label(self.master, textvariable=self.label_errmon_v4_val)
        self.label_errmon_v3.grid(row=3, column=4)
        self.label_errmon_v4.grid(row=3, column=5)
      
        self.label_LFmode = tk.Label(self.master, text="Loop filter mode:", font="Helvetica 9 bold")
        self.label_LFmode_val = tk.StringVar()
        self.label_LFmode_ans = tk.Label(self.master, textvariable=self.label_LFmode_val)
        self.label_LFmode.grid(row=4, column=3, sticky=tk.E)
        self.label_LFmode_ans.grid(row=4, column=4, columnspan=2)
        self.clear_labels()
      
        self.spacer = tk.Label(self.master, text="")
        self.spacer.grid(row=5, column=3, columnspan=3)
      
        self.horizontal_sep = ttk.Separator(self.master, orient=tk.HORIZONTAL)
        self.horizontal_sep.grid(row=10, columnspan=6, sticky=tk.E + tk.W)
      
        
        # LOGGING
        self.log = scrolledtext.ScrolledText(self.master, state='disabled', height=30, width=110, font="Consolas 9", bg="#f6f6f6")
        self.log.grid(row=11, column=0, columnspan=6, padx=5, pady=5)
        self.log.tag_config('warning', foreground="#aa3300")
        self.log.tag_config('info', foreground="#33aa00")
      
              
        # BEGIN LOGGING PROGRAM
        self.p2("  Initializing...", "Relocker: Serial Communications Server")
        self.p2("   Python version", str(platform.python_version()))
        self.scan_serial_ports()

        
    def write_to_log(self, msg, format=''):
        msg = msg.rstrip()
        numlines = self.log.index('end - 1 line').split('.')[0]
        self.log['state'] = 'normal'
        if numlines == "100": # how many lines to keep!
            self.log.delete(1.0, 2.0)
        if self.log.index('end-1c')!='1.0':
            self.log.insert('end', '\n')
        if format == 'warn':
            self.log.insert('end', msg, format)
        else:
            self.log.insert('end', msg)
        self.log['state'] = 'disabled'
        self.log.see(tk.END)
      
    def p(self, string, endstr='', format=''):
       
        if (time.localtime() == self.last_time):
            printstr = "                   " + str(string)
        else:
            self.last_time = time.localtime()
            timestr = time.strftime("%m/%d %H:%M:%S %p", time.localtime()) + "  "
            timestr = (" " + timestr[1:] if timestr.startswith('0') else timestr).replace(" 0", "  ")
            printstr = timestr + str(string)
        self.write_to_log(printstr, format=format)
       
    def p2(self, string1, string2, endstr='', format='info'):
        print(string1 + "  " + str(string2), end=endstr)
        self.write_to_log(string1 + "  " + str(string2), format=format)
      
    def warn(self, string, endstr=''):
        timestr = time.strftime("%m/%d %H:%M:%S %p", time.localtime()) + "  "
        timestr = ("  " + timestr[1:] if timestr.startswith('0') else timestr).replace(" 0", "  ")
        print(timestr + str(string), end=endstr)
        self.write_to_log(timestr + str(string), format='warning')
      
    def scan_serial_ports(self):
         # list of all serial ports: [(port number, description, hardware address)]
        port_list = list(serial.tools.list_ports.comports())  
        ports = []
        for port_no, description, address in port_list:
            ports.append([port_no, description])
        self.ports_listbox.delete(0, tk.END)
    
        if(not ports):
            self.p("Could not find open COM ports!")
            self.p(" - Is the device connected to a USB port?")
            self.p(" - Is another program connected to this port?")
            self.p("Rescan serial ports when ready")
            self.button_connect.config(state="disabled")
            self.button_rescan.config(state="normal")
        else:
            counter = 0
            for (port, desc) in ports:
                self.p2("  Connected Ports", port + ": " + desc, format='')
                self.ports_listbox.insert(counter, port + ": " + desc)
                counter += 1
            self.p("Please select the relocker's COM port from the list above to continue.", format='info')

    def clear_labels(self):
        self.label_lfout_v1_val.set("-")
        self.label_lfout_v2_val.set("-")
        self.label_lfout_v3_val.set("-")
        self.label_lfout_v4_val.set("-")
        self.label_errmon_v1_val.set("-")
        self.label_errmon_v2_val.set("-")
        self.label_errmon_v3_val.set("-")
        self.label_errmon_v4_val.set("-")
        self.label_LFmode_val.set("Unknown")
  
      
    def read_serial(self):
    
        if self.ser:
          # print("Reading serial...")
          if (self.ser.in_waiting):
              line = self.ser.readline()   # read a '\n' terminated line
              if line:
                try:
                  line = line.decode('UTF-8')
                except:
                  pass
                log_message = True
                if ('Fail' in line) or ('Warning' in line):
                  self.warn(line, format='warning') # fail, warning, etc.
                elif 'SKYNET' in line:
                  self.p2("", "")
                  self.p2("Relocker rebooted", line, format='info') # fail, warning, etc.
                  self.clear_labels()
                elif 'Compiled' in line:
                  self.p2("     Compile date", line, format='info') # fail, warning, etc.
                else:
                  if 'LF avg' in line:
                    parsed_line = re.match(".*LF avg.*\[(.*), (.*)].*\[(.*), (.*)]", line)
                    if parsed_line:
                      self.label_lfout_v1_val.set(parsed_line.group(3))
                      self.label_lfout_v2_val.set(parsed_line.group(4))
                      self.label_lfout_v3_val.set(parsed_line.group(1))
                      self.label_lfout_v4_val.set(parsed_line.group(2))
                      self.label_lfout_v1.config(state='normal')
                      self.label_lfout_v2.config(state='normal')
                      log_message = False
                  elif 'Err mon' in line:
                    parsed_line = re.match(".*Err mon.*\[(.*), (.*)].*\[(.*), (.*)]", line)
                    if parsed_line:
                      self.label_errmon_v1_val.set(parsed_line.group(3))
                      self.label_errmon_v2_val.set(parsed_line.group(4))
                      self.label_errmon_v3_val.set(parsed_line.group(1))
                      self.label_errmon_v4_val.set(parsed_line.group(2))
                      self.label_errmon_v1.config(state='normal')
                      self.label_errmon_v2.config(state='normal')
                      log_message = False
                  elif 'Running in' in line:
                    parsed_line = re.match(".*Running in '(.*)'.*", line)
                    if parsed_line:
                      self.label_LFmode_val.set(parsed_line.group(1))
                      log_message = False
                  elif 'data[' in line:
                    parsed_line = re.match("data\[(\d*),(\d*),(\d*)]:(\w+)", line)
                    if parsed_line:
                      self.num_pts = parsed_line.group(1)
                      self.thresh1 = parsed_line.group(2)
                      self.thresh2 = parsed_line.group(3)
                      self.pltdata = parsed_line.group(4)
                      self.plttime = time.strftime("%m/%d %H:%M:%S %p", time.localtime())
                      print("Stored new error monitor trace.")
                      print(parsed_line.groups())
                      log_message = False
                      if (self.var_reload_plot.get() and hasattr(self, "graph")):
                          self.graph.update_graph(self.pltdata, self.plttime, self.thresh1, self.thresh2, self.num_pts)


                  if log_message:
                    self.p(line, endstr='')    # normal message
                    
          self.master.after(0, self.read_serial)
        
  
    def about(self):
        messagebox.showinfo("About Me", "Relocker GUI programmed with tkinter (Python)\n\nCreated mainly to see calibration data during logging.\n\nThompson lab, Aug. 8, 2019") 
    
    def show_properties(self):
        fp = Path(__file__).absolute()
        dp = Path().absolute()
        messagebox.showinfo("GUI Properties", "File path:\n" + str(fp) +"\n\nDirectory:\n" + str(dp)) 
  
    def connect(self):
        item = re.match("(.*):(.*)", self.ports_listbox.get(tk.ACTIVE))
        if item:
            com_port_input = item.group(1)
            try:
                self.ser = serial.Serial(str(com_port_input), 115200, timeout=2) # open serial port
                self.clear_labels()
                self.ports_listbox.config(state="disabled")
                self.button_connect.config(state="disabled")
                self.button_disconnect.config(state="normal")
                self.button_rescan.config(state='disabled')
                self.p("Connected to " + com_port_input + ". Now listening for serial messages.")
                self.master.after(0, self.read_serial)
            except serial.serialutil.SerialException:
                self.warn("Could not open port '" + str(com_port_input) + "'")
                self.ser = False
        else:
            self.warn("Invalid port selection!")
            self.ser = False
    
    def disconnect(self):
        if self.ser:
            self.ser.close()
        self.ser = False
        self.ports_listbox.config(state='normal')
        self.button_connect.config(state='normal')
        self.button_rescan.config(state='normal')
        self.button_disconnect.config(state='disabled')
        self.label_errmon_v1.config(state='disabled')
        self.label_errmon_v2.config(state='disabled')
        self.label_lfout_v1.config(state='disabled')
        self.label_lfout_v2.config(state='disabled')
        self.p("Connection to serial port has been closed.")
        self.scan_serial_ports()

    def create_plot_window(self):
        self.window = tk.Toplevel(master = self.master)
        self.window.wm_title("Error monitor history")
        self.window.iconbitmap('snail.ico')
        self.graph = Graph(self.window, self.pltdata, self.plttime, self.thresh1, self.thresh2, self.num_pts)
        self.update_plot_window()
        
    def update_plot_window(self):
        self.graph.update_graph(self.pltdata, self.plttime, self.thresh1, self.thresh2, self.num_pts)
        if (self.var_reload_plot.get()):
            self.master.after(1000, self.update_plot_window)

class Graph():
    def __init__(self, master, pltdata, plttime, thresh1, thresh2, num_pts):
        self.master = master
        self.plot_err_mon(pltdata, plttime, thresh1, thresh2, num_pts)
      
    def __del__(self):
        self.master.destroy()
        
    def quit(self):
        self.master.destroy()
        
    def plot_err_mon(self, pltdata, plttime, thresh1, thresh2, num_pts):
        stop_counter = int(num_pts)
        data_bin = binascii.unhexlify(pltdata)
        int_values = struct.iter_unpack(">H", data_bin)
        vals = np.trim_zeros([x[0] for x in int_values])
      #  print(vals)
        vals = vals[stop_counter+1:] + vals[0:stop_counter+1]
        w1 = TL.Wave(vals, name="Error monitor V [arb]")
        t1 = TL.Trace(w1, ls='-', marker=None)
        l1 = TL.Line(int(thresh1), color="orange")
        l2 = TL.Line(int(thresh2), color="orange")
        self.plot_object, self.axes_object = TL.Plot([l1, l2, t1], title="Relocker error monitor trace\n" + plttime, ylabel="Error monitor [arb]",
                              xlabel="Last " + str(len(w1)) + " points", fc="#f0f0f0", fs=(5.5, 3.5), show=False)
        
        self.canvas = FigureCanvasTkAgg(self.plot_object.gcf(), master=self.master)  # A tk.DrawingArea.
        self.canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)
    
        self.toolbar = NavigationToolbar2Tk(self.canvas, self.master)
        self.toolbar.update()
        self.canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)
        
        self.img_exit = PhotoImage(file='exit.png')
        self.button_close = ttk.Button(self.master, text="Close plot", image=self.img_exit, compound="right", command=self.quit)
        self.button_close.pack()  
        self.canvas.draw()
        
        def on_key_press(event):
          print("you pressed {}".format(event.key))
          key_press_handler(event, self.canvas, self.toolbar)
          
        self.canvas.mpl_connect("key_press_event", on_key_press)

    def update_graph(self, pltdata, plttime, thresh1, thresh2, num_pts):
        stop_counter = int(num_pts)
        data_bin = binascii.unhexlify(pltdata)
        int_values = struct.iter_unpack(">H", data_bin)
        vals = np.trim_zeros([x[0] for x in int_values])
        vals = vals[stop_counter+1:] + vals[0:stop_counter+1]
        w1 = TL.Wave(vals, name="Error monitor V [arb]")
        t1 = TL.Trace(w1, ls='-', marker=None)
        l1 = TL.Line(int(thresh1), color="orange")
        l2 = TL.Line(int(thresh2), color="orange")
        
        xmin, xmax = self.plot_object.xlim()
        for c in self.axes_object.get_lines():
            c.remove()
            
        self.plot_object.plot((0, len(w1)), (random.randint(1700, 2200), random.randint(1700, 2200)))
        self.plot_object.title("Relocker error monitor trace\n" + plttime)
        self.plot_object.xlabel("Last " + str(random.randint(0, 10) + len(w1)) + " points")
        self.plot_object.plot(w1)
        self.canvas.draw()

        
#    def close_windows(self):
#        self.master.destroy()
        
root = tk.Tk(className="Relocker GUI")
gui = App(root)
root.mainloop()


