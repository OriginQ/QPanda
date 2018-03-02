#!/usr/bin/env python
# coding=utf-8

import QPandaAPI
api = QPandaAPI.QPandaAPI()
filename = "./test.txt"
iQCout = QPandaAPI.intp(); 
ret = api.loadFile(filename,iQCout);
ret = api.setComputeUnit(1)
ret = api.run(1000);
ret = api.getResult();

print(ret) 
print api.msResult
