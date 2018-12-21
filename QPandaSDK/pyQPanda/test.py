#!/usr/bin/env python
# coding=utf-8

from pyQPanda import *
api = QPandaAPI()
filename = "./test.txt" 
ret = api.loadFile(filename);
ret = api.setComputeUnit(1)
ret = api.run(1000);
ret = api.getResult();

print(ret) 
