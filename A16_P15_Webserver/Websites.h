
//Converted with http://www.percederberg.net/tools/text_converter.html to C-String Text and saved as char

const char index[] PROGMEM = {
"<HTML><HEAD>\n<title>\nNanoESP Main Page\n</title>\n</HEAD>\n<BODY bgcolor=\"#FFFF99\" text=\"#000000\">\n<h1>NanoESP Main Page</h1>\n<HR><BR>\nWellcome to the NanoESP Main Page. <BR>\nHere you can choose some options: <BR>\n<BR>\n<a href=\"/pinout\">Pinlayout NanoESP</a><br>\n<a href=\"/lib\">Library Infos</a><br>\n<HR><BR>\n<img src=\"http://iot.fkainka.de/wp-content/uploads/2015/09/cropped-xBoard.png\">\n</body>\n</HTML>\0"
};

const char lib[] PROGMEM = {
"<HTML><HEAD>\n<title>\nNanoESP Lib\n</title>\n</HEAD>\n<BODY bgcolor=\"#FFFF99\" text=\"#000000\">\n<h1>NanoESP Library Infos</h1>\n<HR>\n<h3>Defines and functions</h3>\n\n<p>#define STATION 1<br>\n #define ACCESSPOINT 2<br>\n #define DUAL 3<br>\n #define TCP TCP<br>\n #define UDP UDP<br>\n NanoESP() ;<br>\n boolean init();<br>\n boolean sendCom(String command, char respond[]);<br>\n String sendCom(String command);<br>\n boolean setMultipleConnections();<br>\n boolean setTransferMode() ;<br>\n boolean reset();</p>\n \n <p>boolean configWifi(int modus, String ssid, String password);<br>\n boolean configWifiMode(int modus);<br>\n boolean configWifiStation(String ssid, String password);<br>\n boolean configWifiAP(String ssid, String password);<br>\n boolean configWifiAP(String ssid, String password, int channel, int crypt);<br>\n boolean disconnectWifi();<br>\n String getIp();</p>\n \n<p>boolean newConnection(int id, String type, String ip , int port);<br>\n boolean closeConnection(int id) ;<br>\n boolean startUdpServer(int id, String ip , int port, int recvport, int mode=0);<br>\n boolean endUdpServer(int id);<br>\n boolean startTcpServer(int port) ;<br>\n boolean endTcpServer();<br>\n boolean sendData(int id, String msg);<br>\n boolean sendDataClose(int id, String msg);<br>\n int getId();<br>\n boolean ping(String adress);</p>\n \n bool sendFromFlash(int client, const char *website, int len);<br>\n bool recvRequest(int &id, String &method, String &ressource, String &parameter);<br>\n bool sendStreamHeader(int connectionId);\t\t<br>\n String sendRequest(int id, String method, String address, String parameter);<br>\n String sendRequest(int id, String method, String address); \t<br>\n<br>\t\n\nvoid serialDebug();<br><br>\n\n<a href=\"/\">Main Page</a><br>\n<a href=\"/pinout\">Pinlayout NanoESP</a><br>\n<HR><BR>\n<img src=\"http://iot.fkainka.de/wp-content/uploads/2015/09/cropped-xBoard.png\">\n</body>\n</HTML>\n\0"
};

const char pinout[] PROGMEM = {
  "<HTML><HEAD>\n<title>\nNanoESP Pinout\n</title>\n</HEAD>\n<BODY bgcolor=\"#FFFF99\" text=\"#000000\">\n<h1>NanoESP Pinout</h1>\n<HR><BR>\n<img src=\"http://iot.fkainka.de/wp-content/uploads/2016/01/Pinout-Pretzel-Board.jpg\">\n<BR>\n<a href=\"/\">Main Page</a><br>\n<a href=\"/lib\">Library Infos</a><br>\n<HR><BR>\n<img src=\"http://iot.fkainka.de/wp-content/uploads/2015/09/cropped-xBoard.png\">\n</body>\n</HTML>\0"
};

const char error404[] PROGMEM = {
  "<HTML><HEAD>\n<title>\nError\n</title>\n</HEAD>\n<BODY bgcolor=\"#FFFF99\" text=\"#000000\">\n<h1>Error 404: File or Page not found</h1>\n<HR><BR>\n<a href=\"/\">Main Page</a><br>\n<a href=\"/lib\">Library Infos</a><br>\n<a href=\"/pinout\">NanoESP Pinout</a>\n<br>\n<br>\n<HR><BR>\n<img src=\"http://iot.fkainka.de/wp-content/uploads/2015/09/cropped-xBoard.png\">\n</body>\n</HTML>\0"
};


