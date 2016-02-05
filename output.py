#!/usr/bin/env python
from subprocess import call
from multiprocessing import Process

class sensor(object):
	def __init__(self):
		self.name ="monitor"
	def setproc(self,str):
		self.proc = str
	def setdev(self,str):
		self.device =str
	def setdevname(self,str):
		self.devName = str
	def setoutfile(self,str):
		self.devName = str
	def start(self):
		call([self.proc, self.device, self.devName])

def a():
	s2 = sensor()
	s2.setproc("/home/gngrbrd/dev/sensor/monitor")
	s2.setdev("/home/gngrbrd/dev/scratch/sensor1.dat")
	s2.setdevname("INPUT_1")
	s2.setoutfile("/home/gngrbrd/sensor/log/input.dat")
	s2.start()

if __name__ == '__main__':
    p2 = Process(target=a )
    p2.start()
    p2.join()

    