a = [[1,2,3,4,5,],
     [6,7,8,9,10],
     [11,12,13,14,15]]

print (a)
j=0
sum=0
for j in range (3):
    for i in range (0, 5, 1):
        sum += a[j][i]
print (sum)
