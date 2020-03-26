# Python program to construct tree using inorder and 
# preorder traversals
import json,os

# A binary tree node 
class Node: 
	
	# Constructor to create a new node 
	def __init__(self, data): 
		self.data = data 
		self.left = None
		self.right = None

	def flatten(self):
		res = {}
		text = {}
		data = self.data.split()		
		text["data"] = float(data[0])
		text["type"] = "number"
		if data[1]!="N":
			text["type"] = "op"
			text["operator"] = data[1]
			children = []

			if self.right:
				children.append(self.right.flatten())
			if self.left:
				children.append(self.left.flatten())

			if len(children)>0:
				res["children"] = children
		res["text"] = text
		return res

	@classmethod
	def from_dictionary(cls, d):
		obj = cls(d["data"])

		if d.has_key("left") and d["left"] is not None:
			obj.left = cls.from_dictionary(d["left"])

		if d.has_key("right") and d["right"] is not None:
			obj.right = cls.from_dictionary(d["right"])

		return obj

def buildTree(inOrder, preOrder, inStrt, inEnd): 
	
	if (inStrt > inEnd): 
		return None

	# Pich current node from Preorder traversal using 
	# preIndex and increment preIndex 
	tNode = Node(preOrder[buildTree.preIndex]) 
	buildTree.preIndex += 1

	# If this node has no children then return 
	if inStrt == inEnd : 
		return tNode 

	# Else find the index of this node in Inorder traversal 
	inIndex = search(inOrder, inStrt, inEnd, tNode.data) 
	
	# Using index in Inorder Traversal, construct left 
	# and right subtrees 
	tNode.left = buildTree(inOrder, preOrder, inStrt, inIndex-1) 
	tNode.right = buildTree(inOrder, preOrder, inIndex + 1, inEnd) 

	return tNode 

# UTILITY FUNCTIONS 
# Function to find index of vaue in arr[start...end] 
# The function assumes that value is rpesent in inOrder[] 

def search(arr, start, end, value): 
	for i in range(start, end + 1): 
		if arr[i] == value: 
			return i 

def printInorder(node): 
    if node is None: 
        return
    # first recur on left child 
    printInorder(node.left) 
    # then print the data of node 
    print(str(node.data)+",",end="") 
    # now recur on right child 
    printInorder(node.right) 

try:		
	file = open("inorder", "r")
	inOrder = file.readline()[:-1].split(",")
	file.close()

	file = open("preorder", "r")
	preOrder = file.readline()[:-1].split(",")
	file.close()
except:
	print('{"err": "Failed: Server Error"}')
	exit(0)
	
# Static variable preIndex 
buildTree.preIndex = 0
root = buildTree(inOrder, preOrder, 0, len(inOrder)-1) 
print(json.dumps(root.flatten()))
exit(0)
