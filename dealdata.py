# encoding=utf-8
import os
from os.path import join
import numpy as np
dest = "/Users/mac/Documents/3rd/sciencewriting/final/MST-master/170511/npy/"
dest2 = "/Users/mac/Documents/3rd/sciencewriting/final/MST-master/MR/"
# a = np.load("100_1_26.npy")
num = 0
for root, dirs, files in os.walk( dest ):
	for OneFileName in files :
		num+=1
		if OneFileName.find( '.npy' ) == -1 :
			continue
		OneFullFileName = join(root, OneFileName )
		a = np.load(OneFullFileName)
            # for line in open( OneFullFileName ):
            #     print( line, end = '' )
		name = OneFileName.split('.')
		l = dest2+name[0]+".txt"
		f=file(l,"w+")
		for i in a:
			# print a
			for j in i:
				# print j
				jj = str(j)
				j = jj.split('.')
				f.write(j[0]+' ')
			f.write('\n')
		print num

		f.close()
print num