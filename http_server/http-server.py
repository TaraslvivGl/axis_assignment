# python2 http-server.py 8080
import SimpleHTTPServer
import BaseHTTPServer

class SputHTTPRequestHandler(SimpleHTTPServer.SimpleHTTPRequestHandler):
    def do_POST(self):
        print(self.headers)
        length = int(self.headers["Content-Length"])
        path = self.translate_path(self.path)
        with open(path + "/" + "reveiced_file", "wb") as dst:
            dst.write(self.rfile.read(length))
	self.send_response(201)

if __name__ == '__main__':
    SimpleHTTPServer.test(HandlerClass=SputHTTPRequestHandler)
