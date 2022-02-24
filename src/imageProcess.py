# imageProcess.py

# -*- coding:utf-8 -*-

import sys
print('第一个参数:%s' % sys.argv[0])
if sys.argv[1].startswith('-'):
    c1 = sys.argv[1][1:]
    print(c1)
