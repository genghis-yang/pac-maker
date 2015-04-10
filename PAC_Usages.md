从本项目所得之PAC文件的使用主要分为两步，详见后文。
  1. 修改下载的pac文件，把其中最末一行的127.0.0.1:8086换成你自己找的代理。
  1. 将修改后的pac文件加载进系统或软件中。

# 修改PAC文件中的代理服务器 #

本项目下载的PAC文件中，默认使用的代理服务器为：127.0.0.1:8086  在使用此PAC之前需要将它改成你自己找到的代理服务器。建议使用UltraEdit或EditPlus等文本编辑软件打开下载的PAC，对最末一行中的127.0.0.1:8086进行修改。推荐使用[Wallproxy](http://code.google.com/p/wallproxy-plugins/)、[Goagent](http://code.google.com/p/goagent/)等基于GAE的代理。

![http://pic.dbank.com/p0007qq8bv.png](http://pic.dbank.com/p0007qq8bv.png)
### **切记**修改后以ANSI编码保存，不可保存成Unicode形式。 ###

---


# PAC文件加载方法 #

PAC文件可以加载到系统中，或者加载到软件配置里。系统或软件会自动调用PAC，自动实现代理配置。配置详见:
  * 对于Windows系统，直接在“Internet选项”中，“连接”标签，“局域网设置”按钮，选中“使用自动配置脚本”，下面的地址栏填写PAC文件的URL。
![http://pic.dbank.com/p0oqbazz9q.png](http://pic.dbank.com/p0oqbazz9q.png)
  * 对于Linux系统（以ubuntu10.04为例），在“系统设置”里面打开“网络代理首选项”，在“自动代理配置”中填入PAC的URL。
![http://pic.dbank.com/p0q1v8s1p6.png](http://pic.dbank.com/p0q1v8s1p6.png)
  * 对于Firefox浏览器，“首选项”中“高级选项卡”，“网络”标签，“设置”按钮，在“自动代理配置URL”中填入你的PAC。
![http://pic.dbank.com/p0daboajk6.png](http://pic.dbank.com/p0daboajk6.png)

### 注意：填写PAC时需填写成URL形式。若下载的PAC放置在D盘根目录，则需写成“[file://d:/cernet.pac”。](file://d:/cernet.pac”。) ###