with open('userdata.dat', 'r') as f:
	with open('parsed_data.dat', 'w') as fwrite:
		curuser = ""
		numprobs = 0
		for line in f.readlines():
			line = line.strip()
			if line == "":
				continue
			if line.split().__len__() == 1:
				curuser = line
			else:
				line = line.split()
				numprobs = line.__len__()
				fwrite.write(str(curuser) + " " + str(numprobs) + "\n")
				for problem in line:
					fwrite.write(str(problem) + "\n")

fwrite.close()
f.close()
