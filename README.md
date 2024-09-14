# SteelMeasure
（1）这是一个运行在本地的钢板尺寸测量软件，呈现形式为.sln


（2）操作步骤：

——完全下载源文件.zip，解压缩后的文件不要放在压缩包里，可以放在你平时存项目的文件夹下

——把文件 MFCApplication1Dlg.cpp 143行的文件路径修改为你机器上 calibrate_para_hot 对应的路径

——参考https://www.bilibili.com/video/BV1i54y1m7tw/?spm_id_from=333.337.search-card.all.click&vd_source=845c9e7999b88ce23ae4be98af703d84，对此解决方案重新配置opencv

——通过vs运行.sln


（3）主要的代码编写从 MFCApplication1Dlg.cpp 的208行开始，如果你想理解逻辑，请从这里开始，对应的.h文件可供参考

（4）calibrate_para_hot是标定文件，steelimg_partial是钢板图片集

（5）其他事项见设计报告，如有问题或意见，欢迎Q2387303146

版本：vs2022    opencv4.8.0
