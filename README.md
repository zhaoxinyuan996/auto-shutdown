# auto-shutdown  


# 感谢来访， auto_shutdown plus 更多功能，使用c++/qt开发，今年内会开发完成（还没有学c++，目前还在学c），完成后会同步更新到吾爱论坛   

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
