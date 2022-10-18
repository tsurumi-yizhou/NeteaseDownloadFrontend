## 介绍
这是一个基于[网易云音乐api](https://github.com/Binaryify/NeteaseCloudMusicApi)后端实现的c++前端，将歌单信息处理为[aplayer](https://github.com/DIYgod/APlayer)能够识别的格式。

使用之前必须安装运行[网易云音乐api](https://github.com/Binaryify/NeteaseCloudMusicApi)，并登陆，默认运行在localhost:3000。

会调用wget进行下载，请事先安装并确保可用。

准备完成后，只需编译运行此文件。(clang++ main.cpp -std=c++2a) 共有三个参数。第一个参数为网易云音乐uid，第二个参数为运行地址（默认为localhost：3000），第三个地址为希望写入的文件名称。无法下载的歌曲id将写入log。

##  依赖
+ [sion http客户端](https://github.com/zanllp/sion)
+ [json 解析库](https://github.com/nlohmann/json)
