f = open('aplusb.in', 'r')
a, b = map(int, f.readline().split())
f.close()
summ = a + b
f = open('aplusb.out', 'w')
f.write(f'{summ}')
f.close()
