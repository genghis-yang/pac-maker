# 项目简介 #
A proxy auto-config (PAC) file defines how web browsers and other user agents can automatically choose the appropriate proxy server (access method) for fetching a given URL. This project is designed for creating pac file automatically.My project is mainly focused on providing a pac for chinese education network users who cannot access foreign sites. It also can be used for other purposes. The version 1.1 may be more usefully for people who are not chinese education network users.

PAC文件可以为用户自动选择代理服务器。此项目旨在为教育网用户自动生成pac脚本文件。

**教育网**用户在访问外国网站时需要连接代理，在访问教育网内网站时不需要代理，往往需要不断挂载和取消代理，十分麻烦。利用pac可实现自动选择，毋须手动切换。

本项目旨在：通过输入CERNET公布的教育网可访问地址，自动生成pac文件，使教育网用户免除频繁切换代理的麻烦。

**本项目同时根据每月教育网可访问地址变动，更新PAC文件，[点此下载](http://code.google.com/p/pac-maker/downloads/detail?name=cernet_20120101.pac)，将pac文件最后一行中的“127.0.0.1:8086”改成你自己找的代理服务器即可。**(代理服务器推荐使用[Goagent](http://code.google.com/p/goagent/)、[Wallproxy](http://code.google.com/p/wallproxy-plugins/)等基于GAE的代理，教育网用户也可以使用[小虾](http://xiaoxia.org/)提供的 scut.tk:1998 )

**PAC文件使用方法详见[Wiki](https://code.google.com/p/pac-maker/wiki/PAC_Usages)**

查询教育网可访问IP请转到https://www.nic.edu.cn/

_第一次玩项目托管，代码很水，欢迎批评建议。_

---

# 使用方法 #
**Version 2.0** 源代码采用Python2构建，如需运行源代码需要安装有Python运行时库，**建议Windows用户下载使用已编译好的exe文件**[pac-maker.rar](http://code.google.com/p/pac-maker/downloads/detail?name=pac-maker.rar&can=2&q=)。运行后生成名为cernet.pac的文件。此cernet.pac即可按照[Wiki](https://code.google.com/p/pac-maker/wiki/PAC_Usages)中所述使用，实现代理自动切换。
  * Windows用户可从Python官网下载[Download Python](http://python.org/getit/)
  * Linux发行版基本都已包含Python运行时库，毋须下载。

**Version 1.x** 代码采用C++构建，使用方法见[WikiUsage1.x](https://code.google.com/p/pac-maker/wiki/Usage_Ver1)


---

# 更新历史 #
|Reversion（对应svn版本号）|Details（详细信息）|
|:--------------------------------|:------------------------|
|[r8](https://code.google.com/p/pac-maker/source/detail?r=8)|Version 2.0: Python2.7.2构建;无图形前端;可自动联网获取教育网可访问列表;不可自定义代理地址;[Issue1](https://code.google.com/p/pac-maker/issues/detail?id=1) Fixed|
|[r2](https://code.google.com/p/pac-maker/source/detail?r=2)|Version 1.1beta: VS 2010 C++构建;命令行程序;需要输入可访问地址列表文件;可自定义代理地址|


---

# 之后版本拟解决的问题： #
  1. ~~自动联网获取CERNET发布的教育网可访问地址~~
  1. 图形前端
  1. ~~其他操作系统兼容性~~
  1. 自由选择是否包含各ICP/ISP和境外数据库的IP段