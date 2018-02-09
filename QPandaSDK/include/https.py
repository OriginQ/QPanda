
import requests
import json
def requestHttps(url,content):
    if not url.strip():
        return
    if not content.strip():
        return
    head = {"accpet":"*/*",
            "connection":"Keep-Alive",
            "user-agent":"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1;SV1)",
            "Content-Type":"application/json",
			"maxPostSize":"0"}
    req =requests.post(url,content,head)
    return json.dumps( req.json())


