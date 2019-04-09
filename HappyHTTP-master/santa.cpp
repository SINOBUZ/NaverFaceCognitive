#include "happyhttp.h"
#include <cstdio>
#include <cstring>

#ifdef WIN32
#include <winsock2.h>
#endif // WIN32

#pragma comment(lib, "ws2_32")

int count = 0;

void OnBegin(const happyhttp::Response* r, void* userdata)
{
	printf("BEGIN (%d %s)\n", r->getstatus(), r->getreason());
	count = 0;
}

void OnData(const happyhttp::Response* r, void* userdata, const unsigned char* data, int n)
{
	fwrite(data, 1, n, stdout);
	count += n;
}

void OnComplete(const happyhttp::Response* r, void* userdata)
{
	printf("COMPLETE (%d bytes)\n", count);
}

void Test3()
{
	puts("-----------------Test3------------------------");
	// POST example using lower-level interface

	const char* params = "answer=42&foo=bar";
	int l = strlen(params);

	happyhttp::Connection conn("openapi.naver.com/v1/vision/face", 443);
	conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

	conn.putrequest("POST", "/happyhttp/test.php");
	conn.putheader("Connection", "close");
	conn.putheader("Content-Length", l);
	conn.putheader("Content-type", "application/x-www-form-urlencoded");
	conn.putheader("Accept", "text/plain");
	conn.endheaders();
	conn.send((const unsigned char*)params, l);

	while (conn.outstanding())
		conn.pump();
}

int main(int argc, char* argv[])
{
#ifdef WIN32
	WSAData wsaData;
	int code = WSAStartup(MAKEWORD(1, 1), &wsaData);
	if (code != 0)
	{
		fprintf(stderr, "shite. %d\n", code);
		return 0;
	}
#endif //WIN32
	try
	{
		//Test1();
		//Test2();
		//Test3();

		Test3();
	}

	catch (happyhttp::Wobbly& e)
	{
		fprintf(stderr, "Exception:\n%s\n", e.what());
	}

#ifdef WIN32
	WSACleanup();
#endif // WIN32

	return 0;
}