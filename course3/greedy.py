jobs = []

file = open("jobs.txt","r")
data = file.readlines()
for line in data:
    job = line.split()
    weight = float(job[0])
    length = float(job[1])
    difference = weight - length
    ratio = weight / length
    jobs.append([weight, length, difference, ratio])

#print(jobs)

def compute():
    completionTime = 0
    weightedCompletionTime = 0
    for job in jobs:
        weight = job[0]
        length = job[1]
        completionTime += length
        weightedCompletionTime += (weight*completionTime)
    return weightedCompletionTime

index = 2
def criteria(a,b):
    if a[index] > b[index]:
        return -1
    elif a[index] < b[index]:
        return 1
    else:
        if a[0] > b[0]:
            return -1
        elif a[0] < b[0]:
            return 1
        else:
            if a[1]>b[1]:
                return -1
            else:
                return 1

jobs = sorted(jobs, cmp=criteria)
#print(jobs)
print('difference', compute()) # 69119377652.0

index = 3
jobs = sorted(jobs, cmp=criteria)
#print(jobs)
print('ratio', compute()) # 67311454237.0
