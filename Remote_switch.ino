/*------------------------------------------------------------------------------------------------------------------------
 * 文件名称：Remote_switch.ino

 * 文件内容：

 * 文件版本：1.0.0

 * 文件作者：阿顿 (www.mattslab.top)

 * 开发环境：ESP 8266 & Arduino 1.8.19

 * 注    意：
------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------
                                                  加载头文件区
------------------------------------------------------------------------------------------------------------------------*/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
/*------------------------------------------------------------------------------------------------------------------------
                                                  变量初始化区
------------------------------------------------------------------------------------------------------------------------*/
//设置您的WiFi接入信息
const char* ssid = "";//WIFI名称
const char* password = "";//WIFI密码
//设置用来控制IO口
const char GPIO = 2;
//运行计时
long int RunTime = 0;
//自动重启时间阀，单位小时
const char AutoReboot_time = 1;
//html
const char* html_home_func = "<!DOCTYPE html><html>  <head>    <meta charset=""utf-8"" />    <title>        </title>   <script>            function off() {                var url = window.location.host;                window.location.replace('?operation=OFF');            }            function on() {                var url = window.location.host;                window.location.replace('?operation=ON');            }            function reboot() {                var url = window.location.host;                window.location.replace('?operation=ReBoot');            }       </script>  </head> <body>        <h1>网络远程开关机</h1>        <p>作者：阿顿</p>        <h4>--------控制台---------</h4>        <button onclick=""on()"" style=""width:150px;height:40px"">开机</button>        <p>&nbsp</p>        <button onclick=""off()"" style=""width:150px;height:40px"">关机</button>        <p>&nbsp</p>        <button onclick=""reboot()"" style=""width:150px;height:40px"">重启</button>        <h4>-------设备信息--------</h4>        <p>设备型号: ESP 8266</p>        <p>软件版本：1.0.1</p>  </body></html>";
const char* html_on_func = "<!DOCTYPE html><html>  <head>    <meta charset=""utf-8"" />    <title>        </title>   <script>            function run() {                var url = window.location.host;                window.location.replace('?operation=Home');            }       </script> </head> <body>        <h1>已完成开机命令</h1>        <button onclick=""run()"" style=""width:150px;height:40px"">返回首页</button> </body></html>";
const char* html_off_func = "<!DOCTYPE html><html>  <head>    <meta charset=""utf-8"" />    <title>        </title>   <script>            function run() {                var url = window.location.host;                window.location.replace('?operation=Home');            }       </script> </head> <body>        <h1>已完成关机命令</h1>        <button onclick=""run()"" style=""width:150px;height:40px"">返回首页</button> </body></html>";
const char* html_reboot_func = "<!DOCTYPE html><html>  <head>    <meta charset=""utf-8"" />    <title>        </title>   <script>            function run() {                var url = window.location.host;                window.location.replace('?operation=Home');            }       </script> </head> <body>        <h1>已完成重启命令</h1>        <button onclick=""run()"" style=""width:150px;height:40px"">返回首页</button> </body></html>";
/*------------------------------------------------------------------------------------------------------------------------
                                                  对象初始化区
------------------------------------------------------------------------------------------------------------------------*/
ESP8266WebServer server(80);//设置端口为80

/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：on_func

 * 函数功能：执行关机操作

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void on_func()
{
  digitalWrite(GPIO, LOW);
  delay(1000);
  digitalWrite(GPIO, HIGH);
  delay(1000);
  server.send(200, "text/html", html_on_func);
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：off_func

 * 函数功能：执行开机操作

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void off_func()
{
  digitalWrite(GPIO, LOW);
  delay(1000);
  digitalWrite(GPIO, HIGH);
  delay(1000);
  server.send(200, "text/html", html_off_func);
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：reboot_func

 * 函数功能：执行重启操作

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void reboot_func()
{
  digitalWrite(GPIO, LOW);
  delay(1000);
  digitalWrite(GPIO, HIGH);
  delay(1000);
  server.send(200, "text/html", html_reboot_func);
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：home_func

 * 函数功能：首页

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void home_func()
{
  server.send(200, "text/html", html_home_func);
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：homepage

 * 函数功能：HTTP响应处理函数

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void homepage() {
  String command;
  command = server.arg("operation");
  Serial.println(command);
  if(command == "ON")//
  {
    on_func();
  }
  else if(command == "OFF")
  {
    off_func();
  }
  else if(command == "ReBoot")
  {
    reboot_func();
  }
  else 
  {
    home_func();
  }
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：setup

 * 函数功能：初始化软硬件

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void setup(void) {
  //初始化串口
  Serial.begin(115200);
  Serial.println("ESP8266 已开启");
 
  //初始化网络
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("正在尝试连接到: ");
  Serial.print(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n已连接到WIFI");
  Serial.print("分配到的IP: ");
  Serial.println(WiFi.localIP());
 
  //初始化WebServer
  server.on("/", homepage);
  server.begin();
  Serial.println("HTTP服务 已开启");
  
  //初始化GPIO
  pinMode(GPIO,OUTPUT);
  digitalWrite(GPIO, HIGH);
}
 /*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：loop

 * 函数功能：循环运行

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void loop(void) {
  while(1)
  {
    //监听客户请求并处理
    server.handleClient();
    delay(1);
    //RunTime = RunTime + 1;//进行计时
    if(RunTime >= (AutoReboot_time * 1000 * 60 * 60))//超过指定时间进行重启
    {
      while(1);
    }
  }
}
