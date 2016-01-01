/*************************************************************************
*
* Copyright (c) 2015 by LSA All Rights Reserved
*
* FILENAME:  main.cpp
*
* PURPOSE :  HTTP 服务器程序, 向客户端提供请求的文件内容.
*
* AUTHOR  :  李书昂
*
**************************************************************************/
#ifndef SOCKET_H
#define SOCKET_H
/*************************************************************************
*
* Copyright (c) 2015 by Lishuang All Rights Reserved
*
* FILENAME:  main.cpp
*
* PURPOSE :  HTTP 服务器程序, 向客户端提供请求的文件内容.
*
* AUTHOR  :  李书昂
*
**************************************************************************/
#include <iostream>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <string>
#include <fstream>
#include "DoHtml.h"
using namespace std;


#pragma comment(lib, "ws2_32.lib")  /* WinSock使用的库函数 */

/* 定义常量 */
#define HTTP_DEF_PORT        80     /* 连接的缺省端口 */
#define HTTP_BUF_SIZE      1024     /* 缓冲区的大小 */
#define HTTP_FILENAME_LEN   256     /* 文件名长度 */
/* 定义文件类型对应的 Content-Type */
struct doc_type
{
	char *suffix; /* 文件后缀 */
	char *type;   /* Content-Type */
};

struct doc_type file_type[] =
{
	{ "html", "text/html" },
	{ "png", "image/png" },
	{ "jpg", "image/jpg" },
	{ "cpp", "text/plain" },
	{ "css", "text/css" },
	{ "js", "text/javascript" },
	{ "txt", "text/plain;charset=gb2312" },
	{ NULL, NULL }
};

char *http_res_hdr_tmpl = "HTTP/1.1 200 OK\r\nServer: lishuang's Server <0.1>\r\n"
"Accept-Ranges: bytes\r\nContent-Length: %d\r\nConnection: close\r\n"
"Content-Type: %s\r\n\r\n";
void Get_response(fstream &outfile, Html &html, string &str);

/**************************************************************************
*
* 函数功能: 根据文件后缀查找对应的 Content-Type.
*
* 参数说明: [IN] suffix, 文件名后缀;
*
* 返 回 值: 成功返回文件对应的 Content-Type, 失败返回 NULL.
*
**************************************************************************/
char *http_get_type_by_suffix(const char *suffix)
{
	struct doc_type *type;

	for (type = file_type; type->suffix; type++)
	{
		if (strcmp(type->suffix, suffix) == 0)
			return type->type;
	}

	return NULL;
}

/**************************************************************************
*
* 函数功能: 解析请求行, 得到文件名及其后缀. 请求行格式:
*           [GET http://www.baidu.com:8080/index.html HTTP/1.1]
*
* 参数说明: [IN]  buf, 字符串指针数组;
*           [IN]  buflen, buf 的长度;
*           [OUT] file_name, 文件名;
*           [OUT] suffix, 文件名后缀;
*
* 返 回 值: void.
*
**************************************************************************/
void http_parse_request_cmd(char *buf, int buflen, char *file_name, char *suffix)
{
	int length = 0;
	char *begin, *end, *bias;

	/* 查找 URL 的开始位置 */
	begin = strchr(buf, ' ');
	if (!begin)
	{
		file_name = NULL;
		suffix = NULL;
		return;
	}
	begin += 1;

	/* 查找 URL 的结束位置 */
	end = strchr(begin, ' ');
	*end = 0;

	bias = strrchr(begin, '/');
	length = end - bias;

	/* 找到文件名的开始位置 */
	if ((*bias == '/') || (*bias == '\\'))
	{
		bias++;
		length--;
	}

	/* 得到文件名 */
	if (length > 0)
	{
		memcpy(file_name, bias, length);
		file_name[length] = 0;

		begin = strchr(file_name, '.');
		if (begin)
			strcpy(suffix, begin + 1);
	}
}


/**************************************************************************
*
* 函数功能: 向客户端发送 HTTP 响应.
*
* 参数说明: [IN]  buf, 字符串指针数组;
*           [IN]  buf_len, buf 的长度;
*
* 返 回 值: 成功返回非0, 失败返回0.
*
**************************************************************************/
int http_send_response(SOCKET soc, char *buf, int buf_len,Html &html)
{
	int read_len, file_len, hdr_len, send_len;
	char *type;
	char read_buf[HTTP_BUF_SIZE];
	char http_header[HTTP_BUF_SIZE];
	char file_name[HTTP_FILENAME_LEN] = "index.html", suffix[16] = "html";
	FILE *res_file;

	/* 得到文件名和后缀 */
	http_parse_request_cmd(buf, buf_len, file_name, suffix);
	string str = buf;
	if (!str.size())
	{
		return 0;
	}
	if (str.find('?') != str.npos)
	{
		str = str.substr(str.find('?') + 1, str.length() - str.find('?'));
		strcpy(file_name, "out.txt");
		fstream outFile(file_name,ios::out);
		strcpy(suffix, "txt");
		Get_response(outFile, html, str);
		outFile.close();
	}
	res_file = fopen(file_name, "rb+"); /* 用二进制格式打开文件 */
	if (res_file == NULL)
	{
		printf("[Web] The file [%s] is not existed\n", file_name);
		return 0;
	}

	fseek(res_file, 0, SEEK_END);
	file_len = ftell(res_file);
	fseek(res_file, 0, SEEK_SET);

	type = http_get_type_by_suffix(suffix); /* 文件对应的 Content-Type */
	if (type == NULL)
	{

		printf("[Web] There is not the related content type\n");
		return 0;
	}

	/* 构造 HTTP 首部，并发送 */
	hdr_len = sprintf(http_header, http_res_hdr_tmpl, file_len, type);
	send_len = send(soc, http_header, hdr_len, 0);
	//send_len=1;
	if (send_len == SOCKET_ERROR)
	{
		fclose(res_file);
		printf("[Web] Fail to send, error = %d\n", WSAGetLastError());
		return 0;
	}

	do /* 发送文件, HTTP 的消息体 */
	{
		read_len = fread(read_buf, sizeof(char), HTTP_BUF_SIZE, res_file);

		if (read_len > 0)
		{
			send_len = send(soc, read_buf, read_len, 0);
			file_len -= read_len;
		}
	} while ((read_len > 0) && (file_len > 0));

	fclose(res_file);

	return 1;
}


int ServeOn(Html &html)
{
	WSADATA wsa_data;
	SOCKET  srv_soc = 0, acpt_soc;  /* socket 句柄 */
	struct sockaddr_in serv_addr;   /* 服务器地址  */
	struct sockaddr_in from_addr;   /* 客户端地址  */
	char recv_buf[HTTP_BUF_SIZE];
	unsigned short port = HTTP_DEF_PORT;
	int from_len = sizeof(from_addr);
	int result = 0, recv_len;

	WSAStartup(MAKEWORD(2, 0), &wsa_data); /* 初始化 WinSock 资源 */

	srv_soc = socket(AF_INET, SOCK_STREAM, 0); /* 创建 socket */
	if (srv_soc == INVALID_SOCKET)
	{
		printf("[Web] socket() Fails, error = %d\n", WSAGetLastError());
		return -1;
	}

	/* 服务器地址 */
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	result = bind(srv_soc, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	if (result == SOCKET_ERROR) /* 绑定失败 */
	{
		closesocket(srv_soc);
		printf("[Web] Fail to bind, error = %d\n", WSAGetLastError());
		return -1;
	}

	result = listen(srv_soc, SOMAXCONN);
	printf("[Web] The server is running ... ...\n");
	system("explorer.exe http://localhost");
	while (1)
	{
		acpt_soc = accept(srv_soc, (struct sockaddr *) &from_addr, &from_len);
		if (acpt_soc == INVALID_SOCKET) /* 接受失败 */
		{
			printf("[Web] Fail to accept, error = %d\n", WSAGetLastError());
			break;
		}

		printf("[Web] Accepted address:[%s], port:[%d]\n",
			inet_ntoa(from_addr.sin_addr), ntohs(from_addr.sin_port));

		recv_len = recv(acpt_soc, recv_buf, HTTP_BUF_SIZE, 0);
		if (recv_len == SOCKET_ERROR) /* 接收失败 */
		{
			closesocket(acpt_soc);
			printf("[Web] Fail to recv, error = %d\n", WSAGetLastError());
			break;
		}

		recv_buf[recv_len] = 0;

		/* 向客户端发送响应数据 */
		result = http_send_response(acpt_soc, recv_buf, recv_len,html);
		closesocket(acpt_soc);
	}

	closesocket(srv_soc);
	WSACleanup();
	printf("[Web] The server is stopped.\n");

	return 0;
}

void Get_response(fstream &outfile, Html &html,string &str)
{
	string _choice = str.substr(str.find('@') + 1, str.length() - str.find('@'));
	string inputWords = str.substr(0, str.find('@'));	
	string _instr, tempstr;
	fstream resultFile; 
	int ID, times,flag = 0;
	int _count = 0;
	unsigned int j,i;
	for (i = 0; i < inputWords.length(); i++)
	{
		if (inputWords[i] == '%')
		{
			int a, b;
			if (inputWords[i + 1] >= 'A')
			{
				a = inputWords[i + 1] - 'A' + 10;
			}
			else
			{
				a = inputWords[i + 1] - '0';
			}
			if (inputWords[i + 2] >= 'A')
			{
				b = inputWords[i + 2] - 'A' + 10;
			}
			else
			{
				b = inputWords[i + 2] - '0';
			}
			inputWords.erase(i, 1);
			inputWords.erase(i, 1);
			inputWords[i] = a * 16 + b;
		}
	}
	switch (atoi(_choice.c_str()))
	{
	case 0:
		resultFile.open("result1.txt",ios::out);
		outfile << "<table border=\"0\" cellspacing=\"0\" cellpadding=\"0\" class=\"dataTable\"><thead><tr><th class=\"dataTableHeader\">序号</th><th class=\"dataTableHeader\">关键词出现次数</th><th class=\"dataTableHeader\">歌名</th><th class=\"dataTableHeader\">专辑</th><th class=\"dataTableHeader\">歌手</th><th class=\"dataTableHeader\">时间</th></tr></thead>";
		html.getsearchResult(resultFile, inputWords);
		resultFile.close();
		resultFile.open("result1.txt");	
		outfile << "<tbody>";
		getline(resultFile, str);
		j = 0;
		while (j != str.length())
		{
			if (str[j] >= '0' && str[j] <= '9')
			{
				_instr += str[j];
			}
			else if (str[j] == ',')
			{
				ID = atoi(_instr.c_str()) - 1;
				_instr = "";
			}
			else if (str[j] == ')')
			{
				times = atoi(_instr.c_str());
				flag = 1;
				_instr = "";
			}
			if (flag == 1)
			{
				_count++;
				if (_count % 2 == 0)
				{
					outfile << "<tr class=\"even_row\">";
				}
				else
				{
					outfile << "<tr class=\"odd_row\">";
				}
				outfile << "<td style=\"white-space: nowrap\">" << ID + 1 << "</td><td style=\"white-space: nowrap\">" << times << "</td><td style=\"white-space: nowrap\">" << html.m_song[ID].m_title << "</td><td style=\"white-space: nowrap\">" << html.m_song[ID].m_album << "</td><td style=\"white-space: nowrap\">" << html.m_song[ID].m_singer << "</td><td style=\"white-space: nowrap\">" << html.m_song[ID].m_publishDate << "</td></tr>";
				flag = 0;
			}
			j++;
		}
		outfile << "</tbody>";
		outfile << "</table>";
		resultFile.close();
		break;
	case 1:
		resultFile.open("result2.txt",ios::out);
		outfile << "<table  border=\"0\" cellspacing=\"0\" cellpadding=\"0\" class=\"dataTable\"><thead><tr><th class=\"dataTableHeader\">序号</th><th class=\"dataTableHeader\">歌名</th><th class=\"dataTableHeader\">专辑</th><th class=\"dataTableHeader\">歌手</th><th class=\"dataTableHeader\">时间</th></tr></thead>";
		html.getRecommendList(resultFile, inputWords);
		resultFile.close();
		resultFile.open("result2.txt");
		j = 0,i = 1;
		outfile << "<tbody>";
		getline(resultFile,str);
		while (j != str.length())
		{
			if (str[j] >= '0' && str[j] <= '9')
			{
				_instr += str[j];
			}
			else if (str[j] == ','&& str[j + 1] != '(')
			{
				ID = atoi(_instr.c_str()) - 1;
				_count++;
				if (_count % 2 == 0)
				{
					outfile << "<tr class=\"even_row\">";
				}
				else
				{
					outfile << "<tr class=\"odd_row\">";
				}
				outfile << "<td style=\"white-space: nowrap\">" << i << "</td><td style=\"white-space: nowrap\">" << html.m_song[ID].m_title << "</td><td style=\"white-space: nowrap\">" << html.m_song[ID].m_album << "</td><td style=\"white-space: nowrap\">" << html.m_song[ID].m_singer << "</td><td style=\"white-space: nowrap\">" << html.m_song[ID].m_publishDate << "</td></tr>";
				_instr = "";
				i++;
				if (i == 11)
					break;
			}
			j++;
		}
		outfile << "</tbody>";
		outfile << "</table>";
		break;
	default:
		break;
	}
}
#endif // !SOCKET_H