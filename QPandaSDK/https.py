
import requests
import json

def requestHttps(url,content):
    if not url:
        return 
    if not content:
        return
    headers={"Content-type" : "application/x-www-form-urlencoded",
	         "Accept" : "text/plain"}

    req =requests.post(url,content,headers)
    return (json.dumps(req.json()),10)
