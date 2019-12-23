# _ 10 9 8 7 6 5 4 3 2 1
import os, sys

def stepcount(left):
	global step_count
	if left < 0:
		return 0
	if left == 0:
		return 1
	return stepcount(left - 1) + stepcount(left - 2)
	
	
def main():
	n = stepcount(11)
	print(n)
	
if __name__ == "__main__":
	main()