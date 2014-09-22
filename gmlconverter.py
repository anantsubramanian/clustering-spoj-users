idmap = {}
curid = 0

edges = []

with open('clustered_data.dat', 'r') as f:
	with open('plot_graph.gml', 'w') as fwrite:
		fwrite.write('graph\n[\n\t')
		for line in f.readlines():
			line = line.strip()
			if line.split().__len__() != 1:
				[user1, user2, sim] = line.split()
				if not (user1 in idmap):
					fwrite.write('node\n\t[\n\t ')
					fwrite.write('id ' + str(curid) + '\n\t ')
					fwrite.write('label "' + user1 + '"\n\t]\n\t')
					idmap[user1] = curid
					curid += 1
				if not (user2 in idmap):
					fwrite.write('node\n\t[\n\t ')
					fwrite.write('id ' + str(curid) + '\n\t ')
					fwrite.write('label "' + user2 + '"\n\t]\n\t')
					idmap[user2] = curid
					curid += 1
				user1id = idmap[user1]
				user2id = idmap[user2]
				edges.append([user1id, user2id, sim])
			else:
				fwrite.write('node\n\t[\n\t ')
				fwrite.write('id ' + str(curid) + '\n\t ')
				fwrite.write('label "' + line + '"\n\t]\n\t')
				idmap[line] = curid
				curid += 1
		for edge in edges:
			fwrite.write('edge\n\t[\n\t ')
			fwrite.write('source ' + str(edge[0]) + '\n\t ')
			fwrite.write('target ' + str(edge[1]) + '\n\t ')
			fwrite.write('label "' + str(edge[2]) + '"\n\t]\n\t')
		fwrite.write(']')

fwrite.close()
f.close()
