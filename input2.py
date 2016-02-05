#!/usr/bin/env python
from subprocess import call
from multiprocessing import Process

class sensor(object):
	def __init__(self):
		self.name ="sensor"
	def setproc(self,str):
		self.proc = str
	def setdev(self,str):
		self.device =str
	def setdevname(self,str):
		self.devName = str
	def setoutfile(self,str):
		self.outFile = str
	def setoutfilename(self,str):
		self.outFileName = str
	def start(self):
		call([self.proc, self.device, self.devName, self.outFile, self.outFileName])

def b():
	s1 = sensor()
	s1.setproc("/home/gngrbrd/dev/scratch/sensor")
	s1.setdev("/dev/urandom")
	s1.setdevname("INPUT_2")
	s1.setoutfile("/home/gngrbrd/dev/scratch/sensor2.dat")
	s1.setoutfilename("OUTPUT_2")
	s1.start()

def a():
	s2 = sensor()
	s2.setproc("/home/gngrbrd/dev/scratch/sensor")
	s2.setdev("/dev/urandom")
	s2.setdevname("INPUT_1")
	s2.setoutfile("/home/gngrbrd/dev/scratch/sensor1.dat")
	s2.setoutfilename("OUTPUT_1")
	s2.start()

if __name__ == '__main__':
    p = Process(target=b )
    p2 = Process(target=a )
    p.start()
    p2.start()
    p.join()

    