import codecs;

TYPE = "submit";

def loadUnicodeDigits():
	unicodeDigits = {}
	with open("UnicodeData.txt", "r") as unicodeDataFile:
		for line in unicodeDataFile:
			arr = line.split(";")
			if arr[2] == "Nd":
				unicodeDigits[int(arr[0], 16)] = int(arr[6]);
	return unicodeDigits;

def main():
	unicodeDigits = loadUnicodeDigits();
	
	with open(TYPE + "Output.txt", "w") as outFile:
		with codecs.open(TYPE + "Input.txt", "r", "utf-16") as inFile:
			lineCount = int(inFile.readline())
			
			for i in range(1, lineCount+1):
				result = "N/A";
				line = inFile.readline().strip();
				
				allOk = True;
				numStr = 0;
				for ch in line:
					decimalValue = unicodeDigits.get(ord(ch), -1)
					if decimalValue == -1:
						allOk = False;
						break;
					else:
						numStr = numStr*10 + decimalValue;
						
				if allOk:
					result = hex(numStr)[2:];
				
				print("Case #" + str(i) + ": " + result, file=outFile);
	


main();