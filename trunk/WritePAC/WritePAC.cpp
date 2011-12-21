//////////////////////////////////////////////////////////////
//by Genghis Yang
//site: http://code.google.com/p/pac-creater/
//blog: http://genghis-yang.tk/
//Email: mailto://yangcheng2503@163.com
//�����ܣ�	�Զ�����pac�����ļ�����Ҫ�ɷ���IP�б���
//�汾�ţ�1.1beta
//������ʷ��	1.������1.0�����ɵ�Unicode�����ļ��޷�ʹ�ã���Ϊ���ANSI�����ļ���
//			2.�����Զ�������ַ�Ĺ���
//�����У� writepac inputfile [-o outputfile] [-p proxyaddress]
//		eg. writepac cernet.txt -o autoproxy.pac 127.0.0.1:8086
//IP�б��ļ������ʽ����ַ  �������ݣ����磺�������룩  ��������
//		eg. 122.204.0.0              0.3.255.255    255.252.0.0
//		�����������ո���Ʊ��
//////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <windows.h>

#define MAX_PATH 260
#define MAX_LINE_LENGTH 1024

int execute_a_line(FILE *input, FILE *output);
void AllTrim( char *str );

int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR input_file_full_path[MAX_PATH], output_file_full_path[MAX_PATH], proxy_address[MAX_PATH];
	if(1==argc)
	{
		_tprintf_s(_T("Usage: %s inputFile [-o output] [-p proxyaddress]\n -o output: Specify output instance filename. -o must be lowercase.\n -p proxyaddress: Specify Proxy Server's address and port"), argv[0]);
		return -1;
	}
	else
	{
		TCHAR command_line_parameter[MAX_PATH];
		_tcscpy_s(command_line_parameter, _T(""));
		for(int command_line_parameter_number = 1; command_line_parameter_number<argc; command_line_parameter_number++)		//�������в�����һ����
		{
			_tcscat_s(command_line_parameter, argv[command_line_parameter_number]);
			_tcscat_s(command_line_parameter, _T(" "));
		}
		TCHAR* optional_parameter;
		TCHAR* address_parameter;
		if( (optional_parameter = _tcsstr(command_line_parameter, _T(" -o ") )) ==NULL)		//���δ�ҵ�-o����
		{
			_tprintf(_T("Qutput will be named as \"auto.pac\"\n"));
			_tcscpy_s(output_file_full_path, _T("auto.pac"));
			if( (address_parameter = _tcsstr(command_line_parameter, _T(" -p ") )) ==NULL)
			{
				_tprintf(_T("Proxy Server will be set as \"scut.tk:1998\"\n"));
				_tcscpy_s(input_file_full_path, command_line_parameter);
				_tcscpy_s(proxy_address, _T("scut.tk:1998"));
			}
			else
			{
				_tcsncpy_s(input_file_full_path, command_line_parameter, address_parameter-command_line_parameter);
				_tcscpy_s(proxy_address, (address_parameter+_tcslen(_T(" -p "))) );
			}
		}
		else		//�ҵ�-o����
		{
			_tcsncpy_s(input_file_full_path, command_line_parameter, optional_parameter-command_line_parameter);	//���������ļ��ַ���
			if( (address_parameter = _tcsstr(command_line_parameter, _T(" -p ") )) ==NULL)		//���δ�ҵ�-p����
			{
				_tprintf(_T("Proxy Server will be set as \"scut.tk:1998\"\n"));
				_tcscpy_s(output_file_full_path, (optional_parameter+_tcslen(_T(" -o "))) );
				_tcscpy_s(proxy_address, _T("scut.tk:1998"));
			}
			else
			{
				_tcsncpy_s(output_file_full_path, optional_parameter+_tcslen(_T(" -o ")), address_parameter-optional_parameter-_tcslen(_T(" -o ")));
				_tcscpy_s(proxy_address, address_parameter+_tcslen(_T(" -p ")) );
			}
		}
	}

	FILE *input_file, *output_file;
	if(_tfopen_s(&input_file, input_file_full_path, _T("a+")))
	{
		_tprintf(_T("error!"));
		return -1;
	}
	char output_file_full_path_ansi[MAX_PATH];
	WideCharToMultiByte(CP_ACP, 0, output_file_full_path, -1, output_file_full_path_ansi, MAX_PATH, 0, 0);
	if(fopen_s(&output_file, output_file_full_path_ansi, "w+b"))
	{
		_tprintf(_T("error!"));
		return -1;
	}

	char output_head[MAX_LINE_LENGTH];
	sprintf_s(output_head, "// by yangcheng2503@163.com\nfunction FindProxyForURL(url, host)\n{\nif( isPlainHostName(host) || dnsDomainIs(host,\".cn\") || !isResolvable(host) ) return \"DIRECT\";\nrip=dnsResolve(host);\nif( isInNet(rip,\"127.0.0.0\",\"255.0.0.0\") ||\n");
	if(strlen(output_head) != fwrite(output_head, sizeof(char), strlen(output_head), output_file))
	{
		_tprintf(_T("Write head error!"));
		return -1;
	}
	while(1 != execute_a_line(input_file, output_file));

	char output_tail_ansi[MAX_LINE_LENGTH];
	char proxy_address_ansi[MAX_PATH];
	WideCharToMultiByte(CP_ACP, 0, proxy_address, -1, proxy_address_ansi, MAX_PATH, 0, 0);
	AllTrim(proxy_address_ansi);
	sprintf_s(output_tail_ansi, "(shExpMatch(host, \"*qq.com\")) ||\n(shExpMatch(host, \"*taobao.com\")) )return \"DIRECT\";\nelse return \"PROXY %s; DIRECT\";\n}\n", proxy_address_ansi);
	if(strlen(output_tail_ansi) != fwrite(output_tail_ansi, sizeof(char), strlen(output_tail_ansi), output_file))
	{
		_tprintf(_T("Write head error!"));
		return -1;
	}
	fclose(input_file);
	fclose(output_file);
	return 0;
}

int execute_a_line(FILE *input, FILE *output)
{
	TCHAR line[MAX_LINE_LENGTH];
	TCHAR ip_address[16];
	TCHAR net_mask[16];
	if(_fgetts(line,MAX_LINE_LENGTH,input) == NULL)
		return 1;
	unsigned int pos;
	pos = _tcscspn(line, _T("0123456789"));
	for(int i=0;(line[pos]>=_T('0') && line[pos]<=_T('9') )|| line[pos]==_T('.');i++,pos++)
	{
		ip_address[i]=line[pos];
		ip_address[i+1]=NULL;
	}
	////////������
	TCHAR *right_search = line+_tcslen(line)-1;
	while( (*right_search<_T('0') || *right_search>_T('9'))&& right_search>line)
	{
		right_search--;
	}
	TCHAR *right_end = right_search;
	while(*right_search>=_T('0') && *right_search<=_T('9') || *right_search==_T('.'))
	{
		right_search--;
	}
	right_search++;
	for(int k=0;k<16;k++) //net_mask����
	{
		net_mask[k]=NULL;
	}
	for(int j=0;*right_search>=_T('0') && *right_search<=_T('9')||*right_search==_T('.');j++)
	{
		net_mask[j]=*right_search++;
	}
	char newline[MAX_LINE_LENGTH];
	char ip_address_ansi[16],net_mask_ansi[16];
	WideCharToMultiByte(CP_ACP, 0, ip_address, -1, ip_address_ansi, 16, 0, 0);
	WideCharToMultiByte(CP_ACP, 0, net_mask, -1, net_mask_ansi, 16, 0, 0);
	AllTrim(ip_address_ansi);AllTrim(net_mask_ansi);
	sprintf_s(newline, "isInNet(rip,\"%s\",\"%s\") ||\n", ip_address_ansi, net_mask_ansi);
	if( strlen(newline) != fwrite(newline, sizeof(char), strlen(newline), output) )
	{
		_tprintf(_T("Write error!"));
		exit(0);
	}
	return 0;
}

void AllTrim( char *str )
{
    char *head, *tail;
    if ( str == NULL )
        return;
    for( head = str; *head == ' ' || *head == '\t'; head ++ );
    for( tail = str + strlen(str) - 1; (*tail == ' ' || *tail == '\t' ) && tail >= head; tail -- );
    while( head <= tail )
         *str ++ = *head ++;
    *str = 0;
}