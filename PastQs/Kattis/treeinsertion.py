fact = [1]
for i in range(1, 1010):
    fact.append(fact[-1] * i)

def choose(n, k):
    return fact[n] // fact[k] // fact[n - k]

class BSTNode:
    def __init__(self, val, parent = None):
        self.val = val
        self.parent = parent
        self.left = None
        self.right = None
        self.left_cnt = 0
        self.right_cnt = 0
    
    def insert(self, val):
        if val < self.val:
            if self.left is None:
                self.left = BSTNode(val, self)
            else:
                self.left.insert(val)
            self.left_cnt += 1
        else:
            if self.right is None:
                self.right = BSTNode(val, self)
            else:
                self.right.insert(val)
            self.right_cnt += 1
            
    def eval(self):
        left = 1 if self.left is None else self.left.eval()
        right = 1 if self.right is None else self.right.eval()
        return choose(self.left_cnt + self.right_cnt, self.left_cnt) * left * right

class BST:    
    def __init__(self, vals):
        self.root = BSTNode(vals[0])
        for val in vals[1:]:
            self.root.insert(val)
            
    def eval(self):
        return self.root.eval()

while True:
    n = int(input())
    if n == 0:
        break
    vals = list(map(int, input().split()))
    bst = BST(vals)
    print(bst.eval())