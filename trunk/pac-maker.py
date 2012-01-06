#!python
# By Genghis Yang. Python version 2.7.2
# Email: yangcheng2503@163.com
# Project HomePage: http://code.google.com/p/pac-maker/
# MyBlog: http://genghis-yang.tk/
# CopyRight 2011-2012 Genghis Yang. All Rights Reserved.
import urllib2
response = urllib2.urlopen('https://www.nic.edu.cn/RS/ipstat/internalip/')
the_page = response.read()

loc1 = the_page.find('netmask')
loc1 +=7
while False==the_page[loc1].isdigit():
    loc1 +=1
loc2 = the_page.find('</pre>')
addresses = the_page[loc1:loc2]
addrlist = addresses.split('\n')


f = file('cernet.pac', 'wb')
f.write('''// By Genghis Yang
// Email: yangcheng2503@163.com
// Project HomePage: http://code.google.com/p/pac-maker/
// MyBlog: http://genghis-yang.tk/
// CopyRight 2011-2012 Genghis Yang. All Rights Reserved.
function FindProxyForURL(url, host)
{
if( isPlainHostName(host) || !isResolvable(host) ) return "DIRECT";
rip=dnsResolve(host);
if( isInNet(rip,"127.0.0.0","255.0.0.0") ||
''')

import re
rule = re.compile(r'^\s*(?P<netnum>\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})\s*(?P<hostbits>\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})\s*(?P<netmark>\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})\s*')
for line in addrlist:
    matchlist = rule.search(line)
    if(len(line)==0):
        continue
    line4write = 'isInNet(rip,\"%s\",\"%s\" ||\n' % (matchlist.group('netnum'), matchlist.group('netmark'))
    f.write(line4write)
f.write('''(shExpMatch(host, "*qq.com")) ||
(shExpMatch(host, "*taobao.com")) )return "DIRECT";
else return "PROXY 127.0.0.1:8086; DIRECT";
}
''')
f.close()
