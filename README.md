# 新版本正在制作中
https://github.com/zhaoxinyuan996/auto-shutdown-py


# auto-shutdown  


# 感谢来访， auto_shutdown plus 更多功能，自定义时间设定重启/关机等，如果有新的需求，还请各位提出来，完成后会同步更新到吾爱论坛   

定时关机软件  

c语言，使用win32开发，体积小，自定义关机时间  



dos限制shutdown秒数最大值为315360000  
输入框限制最长8位数字  
非法字符判定为0  
输入判断：  
  if (0 < second && second < 315360000)  
  {  
    do something;  
  }  
