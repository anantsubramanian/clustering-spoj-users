import re
import urllib

f = open('userdata.dat', 'a')

fromrank = 0
torank = 0

print "Enter starting rank (multiple of 100): ",
fromrank = int(raw_input().strip())

print "Enter ending rank (multiple of 100): ",
torank = int(raw_input().strip())

def getProblems(username):
	toreturn = []
	page = urllib.urlopen('http://www.spoj.com/users/' + username)
	for lines in page.readlines():
		extracted = re.findall('/status/[A-Z0-9_]+?,' + username, lines)
		for value in extracted:
			problem = re.search('[A-Z0-9_]+', value)
			toreturn.append(problem.group(0))
	return toreturn


def getuserlist(url):
	toreturn = []
	page = urllib.urlopen(url)
	for lines in page.readlines():
		result = re.findall('"/users/[a-zA-Z0-9_]+"', lines)
		for username in result:
			toreturn.append(username[8:-1])
	return toreturn

baseurl = "http://www.spoj.com/ranks/users/"
userlist = []
if fromrank == 0:
	userlist = getuserlist(baseurl)
	fromrank = 100

for i in range(fromrank, torank, 100):
	print "Got usernames upto rank " + str(i)
	userlist += getuserlist(baseurl + "start=" + str(i))

print "Got userlist!"
count = 0

for username in userlist:
	count += 1
	print str(count) + ". Started " + username
	p1 = getProblems(username)
	f.write(username + '\n')
	for problem in p1:
		f.write(problem + ' ')
	f.write('\n')
	print "Done " + username

f.close()
print "All done!"
