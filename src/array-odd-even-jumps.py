#!/bin/python3

def oddEvenJumps(A):
    N = len(A)

    def make(B):
        ans = [None] * N
        stack = []  # invariant: stack is decreasing
        for i in B:
            while stack and i > stack[-1]:
                ans[stack.pop()] = i
            stack.append(i)
        return ans

    B = sorted(range(N), key = lambda i: A[i])
    print(B)
    oddnext = make(B)
    print(oddnext)
    B.sort(key = lambda i: -A[i])
    print(B)
    make(B)
    print(evennext)

    odd = [False] * N
    even = [False] * N
    odd[N-1] = even[N-1] = True

    for i in range(N-2, -1, -1):
        if oddnext[i] is not None:
            odd[i] = even[oddnext[i]]
        if evennext[i] is not None:
            even[i] = odd[evennext[i]]

    return sum(odd)

arrays = [[10,13,12,14,15],
          [2,3,1,1,4],
          [15,1,3,4,2],
          [5,1,3,4,2],
          [2,96,18,12,21,80,93,2,42,10,25,22,64,35,18,50,3,10,98,19]]

for array in arrays:
    print("Array: ", array)
    print("Answer:", oddEvenJumps(array))
