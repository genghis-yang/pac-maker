# 使用方法： #
> Usage: writepac inputFile [-o output] [-p proxyaddress]
  * _-o output_: Specify output instance filename. -o must be lowercase. If not set, it will be 'auto.pac'  指定输出文件名。默认为auto.pac

  * _-p proxyaddress_: Specify Proxy Server's address and port.If not set, it will be 'scut.tk:1998'  指定代理服务器地址及端口。默认为scut.tk:1998

**eg.** writepac input.txt -o out.pac -p 127.0.0.1:8081

---

The input file should consist of all accessible ip addresses.

输入文件应包含所有可访问IP。
# Input file must be formated as follow: #
# 输入文件格式： #
```
   144.214.0.0 255.255.0.0         
   147.8.0.0  anything  255.255.0.0         
   152.101.0.0 任何字串 255.255.0.0         
   152.104.0.0  ......    255.255.0.0         
   158.132.0.0   xxxxxxx    255.255.0.0         
```

Each line must be consisted of a network-number as a begining, a netmask as an end.

每一行必须以网络号开头，以子网掩码结尾。