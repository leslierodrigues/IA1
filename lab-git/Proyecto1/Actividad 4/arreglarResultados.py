i = 0
j = 0

with open("15puzzle_korf.txt","r") as f:
	with open("nuevosRespdb.txt","w+") as new:
		with open("resultados_15puzzle_a_star_pdb.txt","r") as g:
			a = f.readlines()
			b = g.readlines()
			i = 0
			j = 0
			while (i < len(a)):
				currA = " " + a[i].replace("\n"," ")
				print(b[j].split(","))
				currB = b[j].split(",")[3].replace("\""," ")
				if (currA == currB):
					new.write(b[j])
					i += 1
					j += 1
				else:
					new.write("A*, gap, pancake28,\"" + currA + "\", na, __, na, na, na\n")
					i += 1